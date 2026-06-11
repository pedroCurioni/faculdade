import java.util.Map;

public record HttpRequestInfo(String path, Map<String, String> queryParams) {
}

