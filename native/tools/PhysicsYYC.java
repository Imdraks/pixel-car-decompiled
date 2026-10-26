import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.nio.file.Files;
import java.nio.file.Path;

/** Read-only, bounded targeted decompilation of the Unbound vehicle functions. */
public class PhysicsYYC extends GhidraScript {
 public void run() throws Exception {
  Path out=Path.of(getScriptArgs()[0]);Files.createDirectories(out);
  DecompInterface dec=new DecompInterface();
  if(!dec.openProgram(currentProgram))throw new Exception("Decompiler could not open program");
  String[] labels={"car_create","car_begin_step","car_physics_step","car_debug_dump"};
  String[] expected={"gml_Object_ob_car_Create_0","gml_Object_ob_car_Step_1","gml_Object_ob_car_Step_0","gml_Script_kdbg_car_dump"};
  long[] offsets={0x005a0ff0L,0x005b0070L,0x005b1590L,0x00549620L};
  boolean large=getScriptArgs().length>1&&getScriptArgs()[1].equals("main-large");
  if(large){
   labels=new String[]{"car_physics_step"};expected=new String[]{"gml_Object_ob_car_Step_0"};offsets=new long[]{0x005b1590L};
   DecompileOptions options=new DecompileOptions();options.setMaxInstructions(500000);options.setMaxPayloadMBytes(100);dec.setOptions(options);
  }
  StringBuilder report=new StringBuilder("No whole-program analysis; symbol names checked against mapped file offsets.\n");
  try {
   for(int i=0;i<labels.length;i++){
    Address at=currentProgram.getMemory().locateAddressesForFileOffset(offsets[i]).get(0);
    Function f=getFunctionAt(at);
    if(f==null||!f.getName().contains(expected[i]))throw new Exception("Wrong target at "+at);
    disassemble(at);CreateFunctionCmd.fixupFunctionBody(currentProgram,f,monitor);
    DecompileResults r=dec.decompileFunction(f,150,monitor);
    String row=labels[i]+" file_offset="+Long.toHexString(offsets[i])+" mapped="+at+" symbol="+f.getName()+" completed="+r.decompileCompleted()+" error="+r.getErrorMessage()+"\n";
    println(row);report.append(row);Files.writeString(out.resolve("coverage.txt"),report.toString());
    if(r.getDecompiledFunction()!=null)Files.writeString(out.resolve(labels[i]+".c"),r.getDecompiledFunction().getC());
   }
  }finally{dec.dispose();Files.writeString(out.resolve("coverage.txt"),report.toString());}
 }
}
