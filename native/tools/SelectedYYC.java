import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.nio.file.Files;
import java.nio.file.Path;

/** Targeted static fallback, without whole-program auto-analysis. */
public class SelectedYYC extends GhidraScript {
  public void run() throws Exception {
    Path out=Path.of(getScriptArgs()[0]); Files.createDirectories(out);
    DecompInterface decompiler=new DecompInterface();
    if(!decompiler.openProgram(currentProgram)) throw new Exception("Decompiler open failed");
    StringBuilder summary=new StringBuilder("No whole-program auto-analysis. ELF symbol/function boundaries used.\n");
    try {
      String[] names={"ease_linear","car_end_step","car_variables"};
      String[] expected={"gml_Script_ease_linear","gml_Object_ob_car_Step_2","gml_Script_scr_car_var"};
      long[] fileOffsets={0x004d3af0L,0x005afe90L,0x00496c50L};
      for(int i=0;i<names.length;i++) {
        Address address=currentProgram.getMemory().locateAddressesForFileOffset(fileOffsets[i]).get(0);
        Function f=getFunctionAt(address);
        if(f==null || !f.getName().contains(expected[i]))
          throw new Exception("Target symbol mismatch at mapped file offset: "+address);
        disassemble(address);
        if(f==null) f=createFunction(address,null);
        if(f==null) throw new Exception("Cannot create function at "+address);
        CreateFunctionCmd.fixupFunctionBody(currentProgram,f,monitor);
        DecompileResults result=decompiler.decompileFunction(f,60,monitor);
        String row=names[i]+" address="+address+" name="+f.getName()+" completed="+result.decompileCompleted()+" error="+result.getErrorMessage()+"\n";
        summary.append(row);println(row);
        if(result.getDecompiledFunction()!=null)
          Files.writeString(out.resolve(names[i]+".c"),result.getDecompiledFunction().getC());
      }
    } finally { decompiler.dispose(); Files.writeString(out.resolve("coverage.txt"),summary.toString()); }
  }
}
