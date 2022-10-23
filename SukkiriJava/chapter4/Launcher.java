import java.lang.Runtime;

public class Launcher {
  private static void showUsedMemory() {
    var freeMemory = Runtime.getRuntime().freeMemory();
    var totalMemory = Runtime.getRuntime().totalMemory();
    var usedMemory = totalMemory - freeMemory;
    System.out.println(usedMemory / 1024 / 1024 + "[MB]");
  }

  private static void showMethodList(Class<?> clazz) {
    System.out.println("show method list: ");
    for (var m : clazz.getDeclaredMethods()) {
      System.out.println(m.getName());
    }
  }

  private static void bootNewProcess(Class<?> clazz) throws Exception {
    var pb = new ProcessBuilder("java", clazz.getName());
    var process = pb.start();
    process.waitFor();
  }

  public static void main(String args[]) {
    showUsedMemory();

    var fqcn = args[0];
    var bootMark = args[1];

    try {
      Class<?> clazz = Class.forName(fqcn);
      showMethodList(clazz);

      if (bootMark.equals("E")) {
        bootNewProcess(clazz);
      } else if (bootMark.equals("I")) {
        var m = clazz.getMethod("main", String[].class);
        m.invoke(null, (Object) args);
      } else {
        throw new IllegalArgumentException();
      }
    } catch (Exception e) {
      System.out.println(e.getMessage());
      e.printStackTrace();
      System.exit(1);
    }

    System.exit(0);
  }
}