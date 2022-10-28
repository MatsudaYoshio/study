import java.io.*;
import java.util.*;

public class Misokatsu {
  public static void main(String args[]) throws IOException {
    // FileReaderでの読み取り
    Reader fr = new FileReader("./pref.properties");
    Properties p = new Properties();
    p.load(fr);
    System.out.printf("%s:%s\n", p.getProperty("aichi.capital"), p.getProperty("aichi.food"));

    // ResourceBundleでの読み取り
    ResourceBundle rb = ResourceBundle.getBundle("pref");
    System.out.printf("%s:%s\n", rb.getString("aichi.capital"), rb.getString("aichi.food"));
  }
}