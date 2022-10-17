import java.util.ArrayList;
import java.util.List;

public class StrongBox<E> {
  private static final ArrayList<Integer> MAX_COUNT = new ArrayList<Integer>(List.of(1024, 10000, 30000, 1000000));

  private E data;
  private int getCount = 0;

  public static enum KeyType {
    PADLOCK, BUTTON, DIAL, FINGER;
  }

  public KeyType keyType;

  StrongBox(KeyType keyType) {
    this.keyType = keyType;
  }

  public void put(E d) {
    this.data = d;
  }

  public E get() {
    this.getCount++;
    if (this.getCount < MAX_COUNT.get(this.keyType.ordinal())) {
      return null;
    }
    return this.data;
  }
}