// Headless helper: list every instruction in a range whose scalar operand equals a value,
// together with the containing function, so a Demonware task id can be traced to its issuer.
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript FindTaskImm.java <outfile> <hexvalue> <hexlo> <hexhi>
//
// Ranges are S2x image offsets (address - image base).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.lang.OperandType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.scalar.Scalar;
import java.io.PrintWriter;

public class FindTaskImm extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 4) {
			println("usage: FindTaskImm <outfile> <hexvalue> <hexlo> <hexhi>");
			return;
		}
		long value = Long.parseLong(args[1].replace("0x", ""), 16);
		Address base = currentProgram.getImageBase();
		Address lo = base.add(Long.parseLong(args[2].replace("0x", ""), 16));
		Address hi = base.add(Long.parseLong(args[3].replace("0x", ""), 16));
		AddressSet set = new AddressSet(lo, hi);
		try (PrintWriter out = new PrintWriter(args[0], "UTF-8")) {
			out.println("value=" + Long.toHexString(value) + " range=" + args[2] + ".." + args[3]);
			InstructionIterator instructions = currentProgram.getListing().getInstructions(set, true);
			while (instructions.hasNext() && !monitor.isCancelled()) {
				Instruction instruction = instructions.next();
				for (int op = 0; op < instruction.getNumOperands(); op++) {
					if ((instruction.getOperandType(op) & OperandType.SCALAR) == 0) continue;
					Scalar scalar = instruction.getScalar(op);
					if (scalar == null || scalar.getUnsignedValue() != value) continue;
					Function function = getFunctionContaining(instruction.getAddress());
					out.println(Long.toHexString(instruction.getAddress().subtract(base)).toUpperCase()
						+ "  " + instruction.toString()
						+ "  function=" + (function == null ? "none"
							: Long.toHexString(function.getEntryPoint().subtract(base)).toUpperCase()));
					break;
				}
			}
		}
		println("done");
	}
}
