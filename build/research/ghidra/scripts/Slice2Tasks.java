import ghidra.app.script.GhidraScript;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.listing.*;
import java.io.PrintWriter;
public class Slice2Tasks extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0],"UTF-8")) {
   InstructionIterator it=currentProgram.getListing().getInstructions(true);
   while(it.hasNext()) {
    Instruction in=it.next();
    if(!in.getMnemonicString().equals("MOV")) continue;
    for(int op=0;op<in.getNumOperands();op++) for(Object o:in.getOpObjects(op)) if(o instanceof Scalar) {
     long v=((Scalar)o).getUnsignedValue();
     if(v!=242 && v!=111) continue;
     Function f=getFunctionContaining(in.getAddress());
     if(f!=null) out.println(v+" "+in.getAddress()+" "+Long.toHexString(f.getEntryPoint().subtract(currentProgram.getImageBase()))+" "+in);
    }
   }
  }
 }
}
