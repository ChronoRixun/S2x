import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import java.io.PrintWriter;
public class Slice2Region extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();
  try(PrintWriter out=new PrintWriter(args[0],"UTF-8")) {
   for(int j=1;j<args.length;j++) {
    Address a=currentProgram.getImageBase().add(Long.parseLong(args[j],16));
    out.println("REGION "+a);
    InstructionIterator it=currentProgram.getListing().getInstructions(a.subtract(256),true);
    while(it.hasNext()) {Instruction in=it.next();if(in.getAddress().compareTo(a.add(512))>0)break;out.println(in.getAddress()+" "+in);}
   }
  }
 }
}
