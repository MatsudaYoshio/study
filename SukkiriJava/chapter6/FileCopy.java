import java.io.*;

public class FileCopy {
  public static void main(String args[]) throws Exception {
    String srcFile = args[0];
    String targetFile = args[1];

    FileInputStream fis = new FileInputStream(srcFile);
    FileOutputStream fos = new FileOutputStream(targetFile);

    int data;
    while ((data = fis.read()) != -1) {
      fos.write(data);
    }
    fos.flush();
    fos.close();
    fis.close();
  }
}