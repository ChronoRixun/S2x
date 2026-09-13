// Headless helper: for every reference to each target image offset, print the referencing
// instruction, its containing function, and the scalar immediates loaded by the (up to 24)
// instructions that fall through into it (register setups of the call arguments), so a
// Demonware task id passed as an argument can be matched to its SDK/game issuer.
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript CallersImm.java <outfile> <hexoff> [<hexoff> ...]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.lang.OperandType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;

public class CallersImm extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		Address base = currentProgram.getImageBase();
		try (PrintWriter out = new PrintWriter(args[0], "UTF-8")) {
			for (int i = 1; i < args.length; i++) {
				Address target = base.add(Long.parseLong(args[i].replace("0x", ""), 16));
				out.println("TARGET " + args[i]);
				for (Reference r : getReferencesTo(target)) {
					Address from = r.getFromAddress();
					Instruction in = getInstructionAt(from);
					Function f = getFunctionContaining(from);
					StringBuilder sb = new StringBuilder();
					sb.append(Long.toHexString(from.subtract(base)).toUpperCase());
					sb.append(" ").append(in == null ? r.getReferenceType().toString() : in.toString());
					sb.append(" fn=").append(f == null ? "none" : Long.toHexString(f.getEntryPoint().subtract(base)).toUpperCase());
					sb.append(" imms=[");
					Instruction cur = in;
					int count = 0;
					while (cur != null && count++ < 24) {
						Instruction prev = getInstructionBefore(cur.getAddress());
						if (prev == null || prev.getFallThrough() == null || !prev.getFallThrough().equals(cur.getAddress())) break;
						cur = prev;
						for (int op = 0; op < cur.getNumOperands(); op++) {
							if ((cur.getOperandType(op) & OperandType.SCALAR) == 0) continue;
							Scalar s = cur.getScalar(op);
							if (s == null) continue;
							sb.append(Long.toHexString(cur.getAddress().subtract(base)).toUpperCase()).append(":")
								.append(cur.getMnemonicString()).append(" ").append(cur.getDefaultOperandRepresentation(0))
								.append("=").append(Long.toHexString(s.getUnsignedValue())).append("; ");
							break;
						}
					}
					sb.append("]");
					out.println(sb.toString());
				}
			}
		}
		println("done");
	}
}
