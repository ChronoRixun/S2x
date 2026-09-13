// Headless helper: print <count> consecutive 8-byte pointers starting at an image offset
// (e.g. a vtable) as image offsets, plus the containing function of each target.
//
// analyzeHeadless <projdir> <proj> -process s2_mp64_ship_unpacked.exe -noanalysis \
//     -scriptPath <this dir> -postScript DumpPtrs.java <outfile> <hexoff> <count> [<hexoff> <count> ...]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.PrintWriter;

public class DumpPtrs extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		Address base = currentProgram.getImageBase();
		try (PrintWriter out = new PrintWriter(args[0], "UTF-8")) {
			for (int i = 1; i + 1 < args.length; i += 2) {
				long offset = Long.parseLong(args[i].replace("0x", ""), 16);
				int count = Integer.parseInt(args[i + 1]);
				out.println("TABLE " + args[i]);
				for (int k = 0; k < count; k++) {
					Address at = base.add(offset + 8L * k);
					long value = currentProgram.getMemory().getLong(at);
					long rel = value - base.getOffset();
					String fn = "";
					try {
						Function f = getFunctionContaining(base.add(rel));
						if (f != null) fn = " fn=" + Long.toHexString(f.getEntryPoint().subtract(base)).toUpperCase();
					} catch (Exception e) { fn = " (not an address)"; }
					out.println("  [" + k + "] " + Long.toHexString(rel).toUpperCase() + fn);
				}
			}
		}
		println("done");
	}
}
