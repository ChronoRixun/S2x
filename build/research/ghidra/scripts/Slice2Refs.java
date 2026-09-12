import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.listing.Function;
import java.io.PrintWriter;
public class Slice2Refs extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();
  try(PrintWriter out=new PrintWriter(args[0],"UTF-8")) {
   for(int i=1;i<args.length;i++) {
    Address a=currentProgram.getImageBase().add(Long.parseLong(args[i],16));
    out.println("TARGET "+args[i]);
    for(Reference r:getReferencesTo(a)) {
     Function f=getFunctionContaining(r.getFromAddress());
     out.println(r.getFromAddress()+" function="+(f==null?"none":f.getEntryPoint().subtract(currentProgram.getImageBase())));
    }
   }
  }
 }
}
