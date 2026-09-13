import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;
public class Slice5Strings extends GhidraScript {
 public void run() throws Exception {
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0],"UTF-8")) {
   DataIterator it=currentProgram.getListing().getDefinedData(true);
   while(it.hasNext()) {
    Data d=it.next(); Object v=d.getValue(); if(!(v instanceof String)) continue;
    String s=((String)v); String l=s.toLowerCase();
    if(!(l.matches(".*(store|market|vendor|quartermaster|sku|entitle|inventory|purchase|catalog|currency|balance|ready|fetched|payroll).* ".trim()))) continue;
    out.println("STRING "+Long.toHexString(d.getAddress().subtract(currentProgram.getImageBase()))+" "+s);
    for(Reference r:getReferencesTo(d.getAddress())) { Function f=getFunctionContaining(r.getFromAddress()); if(f==null) { try { out.println(" pair+8="+Long.toHexString(getLong(r.getFromAddress().add(8))-currentProgram.getImageBase().getOffset())); } catch(Exception e) {} } out.println(" ref "+Long.toHexString(r.getFromAddress().subtract(currentProgram.getImageBase()))+" fn="+(f==null?"none":Long.toHexString(f.getEntryPoint().subtract(currentProgram.getImageBase())))); }
   }
  }
 }
}
