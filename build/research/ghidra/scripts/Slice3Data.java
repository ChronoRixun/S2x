import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import java.io.PrintWriter;
public class Slice3Data extends GhidraScript {
 public void run() throws Exception {String[] args=getScriptArgs();try(PrintWriter out=new PrintWriter(args[0],"UTF-8")){for(int i=1;i<args.length;i++){Address a=currentProgram.getImageBase().add(Long.parseLong(args[i],16));out.println("DATA "+args[i]);for(int j=0;j<128;j+=8){long v=getLong(a.add(j));out.println(" +"+j+" ptr="+Long.toHexString(v-currentProgram.getImageBase().getOffset())+" raw="+Long.toHexString(v));}}}}
}
