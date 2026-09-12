import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;
import java.util.*;
public class Slice3Ancestors extends GhidraScript {
 public void run() throws Exception {String[] args=getScriptArgs();try(PrintWriter out=new PrintWriter(args[0],"UTF-8")){Address base=currentProgram.getImageBase();ArrayDeque<Address> q=new ArrayDeque<>();Set<Address> seen=new HashSet<>();q.add(base.add(Long.parseLong(args[1],16)));while(!q.isEmpty()&&seen.size()<500){Address a=q.remove();if(!seen.add(a))continue;out.println("BLOCK "+Long.toHexString(a.subtract(base)));for(Reference r:getReferencesTo(a)){Instruction in=getInstructionAt(r.getFromAddress());Function f=getFunctionContaining(r.getFromAddress());out.println(" ref "+Long.toHexString(r.getFromAddress().subtract(base))+" "+in+" fn="+(f==null?"none":Long.toHexString(f.getEntryPoint().subtract(base))));if(in!=null&&r.getReferenceType().isJump()){Instruction start=in;for(int j=0;j<40;j++){Instruction prev=getInstructionBefore(start.getAddress());if(prev==null||prev.getFallThrough()==null||!prev.getFallThrough().equals(start.getAddress()))break;start=prev;}q.add(start.getAddress());}}}}}
}
