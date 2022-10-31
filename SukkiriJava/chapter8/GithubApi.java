import java.net.*;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import com.fasterxml.jackson.databind.ObjectMapper;

public class GithubApi {
  private static final String API_TOKEN = "****";

  public static void main(String args[]) throws Exception {
    var request = HttpRequest.newBuilder()
        .uri(URI.create("https://api.github.com/users/miyabilink"))
        .header("Accept", "application/vnd.github+json")
        .header("Authorization", API_TOKEN)
        .GET()
        .build();

    var client = HttpClient.newHttpClient();
    var response = client.send(request, HttpResponse.BodyHandlers.ofString());
    ObjectMapper mapper = new ObjectMapper();
    JsonNode root = mapper.readTree(response.body());
    System.out.println(root.get("blog").textValue());
  }
}
