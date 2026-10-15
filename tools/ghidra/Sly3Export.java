// Export independently discovered function boundaries for review.
// @category Sly3
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class Sly3Export extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File destination = new File(args[0]);
        destination.getParentFile().mkdirs();
        int count = 0;
        try (PrintWriter output = new PrintWriter(destination, StandardCharsets.UTF_8)) {
            output.println("Name,Start,End,Size,BodyBytes");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext() && !monitor.isCancelled()) {
                Function f = functions.next();
                long start = f.getEntryPoint().getOffset();
                long end = f.getBody().getMaxAddress().getOffset() + 1;
                String name = f.getName().replace("\"", "\"\"");
                output.printf("\"%s\",0x%08X,0x%08X,%d,%d%n", name, start, end, end - start, f.getBody().getNumAddresses());
                count++;
            }
        }
        println("Exported " + count + " Ghidra functions to " + destination);
    }
}
