import java.io.*;

public class Serialization {
  public static void main(String args[]) {
    Employee employee = new Employee("田中太郎", 41);
    Department department = new Department("総務部", employee);
    try (
        FileOutputStream fos = new FileOutputStream("company.dat");
        ObjectOutputStream oos = new ObjectOutputStream(fos);) {
      oos.writeObject(department);
      oos.flush();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
