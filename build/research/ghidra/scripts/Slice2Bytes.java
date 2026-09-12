import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.PrintWriter;
public class Slice2Bytes extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();
  try(PrintWriter out=new PrintWriter(args[0],"UTF-8")) {
   for(int j=1;j<args.length;j++) {
    String h=args[j];byte[] bytes=new byte[h.length()/2];for(int k=0;k<bytes.length;k++)bytes[k]=(byte)Integer.parseInt(h.substring(2*k,2*k+2),16);
    Address a=currentProgram.getMinAddress(); int count=0;
    while(a!=null && count++<100) {
     a=currentProgram.getMemory().findBytes(a,currentProgram.getMaxAddress(),bytes,null,true,monitor);
     if(a==null)break;
     Function f=getFunctionContaining(a);
     out.println(h+" "+Long.toHexString(a.subtract(currentProgram.getImageBase()))+" function="+(f==null?"none":Long.toHexString(f.getEntryPoint().subtract(currentProgram.getImageBase()))));a=a.add(1);
    }
   }
  }
 }
}
