import java.util.*;

public class ThreeBooks {
  public static void main(String args[]) {
    // 練習問題に合わせてDate型を使ったが、現在は非推奨なので普通は使わない LocalDateTimeとかを使う
    final ArrayList<Book> bookList = new ArrayList<Book>(List.of(
        new Book("Java入門", new Date(2011, 10, 7), "スッキリわかる"),
        new Book("Python入門", new Date(2019, 6, 11), "カレーが食べたくなる"),
        new Book("C言語入門", new Date(2018, 6, 21), "ポインタも自由自在")));

    bookList.sort(new TitleComparator());

    for (Book b : bookList) {
      System.out.println(b.getTitle());
    }
  }
}
