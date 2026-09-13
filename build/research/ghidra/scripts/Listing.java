// Headless helper: print <count> instructions starting at an image offset (disassembling on
// demand), each with its flow/data reference targets, plus the references INTO the start
// address. Used where the decompiler gives up (Arxan-relocated blocks).
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript Listing.java <outfile> <hexoff> <count> [<hexoff> <count> ...]
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;

public class Listing extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		Address base = currentProgram.getImageBase();
		try (PrintWriter out = new PrintWriter(args[0], "UTF-8")) {
			for (int i = 1; i + 1 < args.length; i += 2) {
				Address at = base.add(Long.parseLong(args[i].replace("0x", ""), 16));
				int count = Integer.parseInt(args[i + 1]);
				out.println("LISTING " + args[i]);
				for (Reference r : getReferencesTo(at)) {
					out.println("  <- " + Long.toHexString(r.getFromAddress().subtract(base)).toUpperCase() + " " + r.getReferenceType());
				}
				Instruction in = getInstructionAt(at);
				if (in == null) {
					new DisassembleCommand(at, null, true).applyTo(currentProgram, monitor);
					in = getInstructionAt(at);
				}
				for (int k = 0; k < count && in != null; k++) {
					StringBuilder sb = new StringBuilder();
					sb.append("  ").append(Long.toHexString(in.getAddress().subtract(base)).toUpperCase()).append("  ").append(in.toString());
					for (Reference r : in.getReferencesFrom()) {
						long rel = r.getToAddress().getOffset() - base.getOffset();
						sb.append("  -> ").append(Long.toHexString(rel).toUpperCase()).append("(").append(r.getReferenceType()).append(")");
					}
					out.println(sb.toString());
					Address next = in.getFallThrough();
					if (next == null) {
						Address[] flows = in.getFlows();
						if (flows.length == 1 && in.getMnemonicString().startsWith("JMP")) next = flows[0];
					}
					if (next == null) break;
					in = getInstructionAt(next);
					if (in == null) {
						new DisassembleCommand(next, null, true).applyTo(currentProgram, monitor);
						in = getInstructionAt(next);
					}
				}
			}
		}
		println("done");
	}
}
