import java.util.*;

public class Book implements Cloneable, Comparable<Book> {
  private String title;
  private Date publishDate;
  private String comment;

  public String getTitle() {
    return this.title;
  }

  Book(String title, Date publishDate, String comment) {
    this.title = title;
    this.publishDate = publishDate;
    this.comment = comment;
  }

  // equalsメソッドは一般契約に従うように実装する必要があることに注意
  @Override
  public boolean equals(Object o) {
    // 反射性
    if (o == this)
      return true;

    // oがnullのときinstanceofがfalseを返す
    if (!(o instanceof Book))
      return false;

    Book b = (Book) o;
    return this.title.equals(b.title) && this.publishDate.compareTo(b.publishDate) == 0;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.title, this.publishDate, this.comment);
  }

  @Override
  public int compareTo(Book b) {
    return this.publishDate.compareTo(b.publishDate);
  }

  @Override
  public Book clone() {
    return new Book(this.comment, (Date) this.publishDate.clone(), this.title);
  }
}