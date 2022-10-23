import java.util.Locale;

public class MemoryEater {
  public static void main(String args[]) {
    long[] array = new long[1280000];

    var loc = Locale.getDefault();
    var locLang = loc.getLanguage();
    if (locLang.equals("ja")) {
      System.out.println("メモリを消費しています");
    } else {
      System.out.println("eating memory...");
    }

  }
}
