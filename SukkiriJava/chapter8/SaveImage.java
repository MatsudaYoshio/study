import java.io.*;
import java.net.*;

public class SaveImage {
  public static void main(String args[]) throws IOException {
    URL url = new URL("https://dokojava.jp/favicon.ico");
    URLConnection conn = url.openConnection();
    InputStream in = conn.getInputStream();
    File file = new File("./dj.ico");
    try (
        FileOutputStream fos = new FileOutputStream(file, false);) {
      int data;
      while ((data = in.read()) != -1) {
        fos.write(data);
      }
      fos.flush();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}