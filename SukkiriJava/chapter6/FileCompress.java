import java.io.*;
import java.util.zip.GZIPOutputStream;

public class FileCompress {
  public static void main(String args[]) {
    if (args.length != 2) {
      System.out.println("please input 2 arguments.");
      return;
    }
    String srcFile = args[0];
    String targetFile = args[1];

    try (FileInputStream fis = new FileInputStream(srcFile);
        BufferedInputStream bis = new BufferedInputStream(fis);
        FileOutputStream fos = new FileOutputStream(targetFile + ".zip");
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        GZIPOutputStream gzipStream = new GZIPOutputStream(bos);) {
      int line;
      while ((line = bis.read()) != -1) {
        gzipStream.write(line);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
