import java.util.*;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;
import org.apache.commons.lang3.builder.CompareToBuilder;

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
    return EqualsBuilder.reflectionEquals(this, o);
  }

  @Override
  public int hashCode() {
    return HashCodeBuilder.reflectionHashCode(this);
  }

  @Override
  public int compareTo(Book b) {
    return CompareToBuilder.reflectionCompare(this, b, "comment", "title");
  }

  @Override
  public Book clone() {
    return new Book(this.comment, (Date) this.publishDate.clone(), this.title);
  }
}