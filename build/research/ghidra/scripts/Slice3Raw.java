import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.regex.*;
public class Slice3Raw extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0],"UTF-8")) {
   for(MemoryBlock b:currentProgram.getMemory().getBlocks()) {
    if(!b.isInitialized()||b.getSize()>100000000) continue;
    byte[] bytes=new byte[(int)b.getSize()]; b.getBytes(b.getStart(),bytes);
    String all=new String(bytes,StandardCharsets.ISO_8859_1);
    Matcher m=Pattern.compile("[ -~]{5,}").matcher(all);
    while(m.find()) { String s=m.group(); String l=s.toLowerCase();
     if(!(l.contains("getskus")||l.contains("storefront")||l.contains("launchitems")||l.contains("claim_mail")||l.contains("payroll")||l.contains("redeem")||l.contains("getskudetails")||l.contains("mailmessage")))continue;
     Address a=b.getStart().add(m.start()); out.println("STRING "+Long.toHexString(a.subtract(currentProgram.getImageBase()))+" "+s);
     for(Reference r:getReferencesTo(a)) {Function f=getFunctionContaining(r.getFromAddress());out.println(" ref "+Long.toHexString(r.getFromAddress().subtract(currentProgram.getImageBase()))+" fn="+(f==null?"none":Long.toHexString(f.getEntryPoint().subtract(currentProgram.getImageBase()))));}
    }
   }
   for(int i=1;i<getScriptArgs().length;i++) { Address a=currentProgram.getImageBase().add(Long.parseLong(getScriptArgs()[i],16)); out.println("POINTERS "+getScriptArgs()[i]);for(int j=0;j<64;j+=8)out.println(" +"+j+" "+Long.toHexString(getLong(a.add(j))-currentProgram.getImageBase().getOffset())); }
  }
 }
}
