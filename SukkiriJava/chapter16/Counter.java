import java.util.concurrent.atomic.*;

public class Counter {
  private AtomicLong count = new AtomicLong(0);

  public void add(long i) {
    System.out.println("足し算します");
    this.count.getAndAdd(i);
  }

  public void mul(long i) {
    System.out.println("掛け算します");
    this.count.getAndUpdate(x -> x * i);
  }
}
