// Headless helper: within an image-offset range, print every CALL/JMP whose operand text names
// one of the given absolute targets (image offsets), with the containing function and the two
// preceding instructions. Works when the target lies outside initialised memory (Arxan region)
// and therefore carries no reference.
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript FindCalls.java <outfile> <hexlo> <hexhi> <hexoff>...
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class FindCalls extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		Address base = currentProgram.getImageBase();
		Address lo = base.add(Long.parseLong(args[1].replace("0x", ""), 16));
		Address hi = base.add(Long.parseLong(args[2].replace("0x", ""), 16));
		List<String> targets = new ArrayList<>();
		for (int i = 3; i < args.length; i++)
			targets.add(Long.toHexString(base.getOffset() + Long.parseLong(args[i].replace("0x", ""), 16)));
		try (PrintWriter out = new PrintWriter(args[0], "UTF-8")) {
			InstructionIterator it = currentProgram.getListing().getInstructions(new AddressSet(lo, hi), true);
			while (it.hasNext() && !monitor.isCancelled()) {
				Instruction in = it.next();
				String m = in.getMnemonicString();
				if (!m.startsWith("CALL") && !m.startsWith("JMP")) continue;
				String text = in.toString().toLowerCase();
				String hit = null;
				for (String t : targets) if (text.contains(t)) { hit = t; break; }
				if (hit == null) continue;
				Function f = getFunctionContaining(in.getAddress());
				Instruction p1 = getInstructionBefore(in.getAddress());
				Instruction p2 = p1 == null ? null : getInstructionBefore(p1.getAddress());
				out.println(Long.toHexString(in.getAddress().subtract(base)).toUpperCase() + " " + in.toString()
					+ " fn=" + (f == null ? "none" : Long.toHexString(f.getEntryPoint().subtract(base)).toUpperCase())
					+ " | " + (p2 == null ? "" : p2.toString()) + " | " + (p1 == null ? "" : p1.toString()));
			}
		}
		println("done");
	}
}
