public class Main {
  public static void main(String args[]) {
    new Thread(new CountUpThread()).start();
    new Thread(new CountUpThread()).start();
    new Thread(new CountUpThread()).start();
  }
}
