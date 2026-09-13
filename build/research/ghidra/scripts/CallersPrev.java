// Headless helper: for every reference to each target image offset, print the containing
// function and the two instructions preceding the call verbatim (to see which struct field a
// reader helper such as bdByteBuffer::readUInt32 is loading into).
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript CallersPrev.java <outfile> <hexoff> [<hexoff> ...]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;

public class CallersPrev extends GhidraScript {
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
					Function f = getFunctionContaining(from);
					Instruction in = getInstructionAt(from);
					StringBuilder sb = new StringBuilder();
					sb.append(Long.toHexString(from.subtract(base)).toUpperCase());
					sb.append(" fn=").append(f == null ? "none" : Long.toHexString(f.getEntryPoint().subtract(base)).toUpperCase());
					Instruction p1 = in == null ? null : getInstructionBefore(from);
					Instruction p2 = p1 == null ? null : getInstructionBefore(p1.getAddress());
					sb.append(" | ").append(p2 == null ? "" : p2.toString()).append(" | ").append(p1 == null ? "" : p1.toString());
					out.println(sb.toString());
				}
			}
		}
		println("done");
	}
}
