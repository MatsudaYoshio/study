import java.util.ArrayList;
import java.util.function.*;
import java.util.List;

public class Main {
  private static final ArrayList<String> NAMES = new ArrayList<String>(
      List.of("菅原琢磨", "大江岳人", "湊祐介", "浅香あゆみ"));

  public static void main(String args[]) {
    // IntPredicate Func1 = FuncList::isOdd;

    // FuncList funcList = new FuncList();
    // BiFunction<Integer, String, String> Func2 = funcList::passCheck;

    // ラムダ式
    IntPredicate Func1 = x -> x % 2 == 1;
    BiFunction<Integer, String, String> Func2 = (Integer point, String name) -> {
      return name + "さんは" + (point > 65 ? "合格" : "不合格");
    };

    System.out.println(Func1.test(10));
    System.out.println(Func2.apply(66, "花果"));

    // 練習3-4
    NAMES
        .stream()
        .filter(n -> n.length() < 4)
        .map(n -> n + "さん")
        .forEach(n -> System.out.println(n));
  }
}
