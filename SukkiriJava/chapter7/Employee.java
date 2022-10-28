import java.io.*;

public class Employee implements Serializable {
  private static final long serialVersionUID = 43895620L;
  private String name;
  private int age;

  Employee(String name, int age) {
    this.name = name;
    this.age = age;
  }
}