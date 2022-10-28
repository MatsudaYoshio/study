import java.io.*;

public class Department implements Serializable {
  private static final long serialVersionUID = 29387L;
  private String name;
  private Employee leader;

  Department(String name, Employee leader) {
    this.name = name;
    this.leader = leader;
  }
}
