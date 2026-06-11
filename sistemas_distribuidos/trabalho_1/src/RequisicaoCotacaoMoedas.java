import io.github.cdimascio.dotenv.Dotenv;

import java.io.PrintWriter;
import java.net.Socket;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Map;

public class RequisicaoCotacaoMoedas extends RequisicaoBase {

    private static final String BASE_URL = "https://api.freecurrencyapi.com/v1/latest";
    private final String apiKey;
    private final HttpClient httpClient;

    public RequisicaoCotacaoMoedas(Socket socket) {
        super(socket);
        Dotenv dotenv = Dotenv.load();
        this.apiKey = dotenv.get("FREECURRENCY_API_KEY");

        this.httpClient = HttpClient.newHttpClient();
    }

    private String buscarNaApi(String currencies) {
        try {
            String url = String.format("%s?apikey=%s&currencies=%s", BASE_URL, this.apiKey, currencies);

            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(url)).GET().build();
            HttpResponse<String> response = this.httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                return response.body();
            }

            throw new RuntimeException(
                    "Erro na API de Cotação. Código HTTP: " + response.statusCode() + " - " + response.body());
        } catch (Exception e) {
            throw new RuntimeException("Erro ao se comunicar com o servidor de cotação: " + e.getMessage(), e);
        }
    }

    @Override
    protected void processar(HttpRequestInfo request, PrintWriter out) {
        if (this.apiKey == null || this.apiKey.isBlank()) {
            throw new IllegalStateException("API Key não encontrada no arquivo .env");
        }

        if (!"/cotacao".equals(request.path())) {
            responderJson(out, 404, "Not Found", "{\"erro\": \"Endpoint não encontrado\"}");
            return;
        }

        Map<String, String> params = request.queryParams();
        String tipoPerfil = params.get("perfil");

        String moedas = "1".equals(tipoPerfil) ? "EUR,CAD,BRL,CNY,INR" : "BRL";
        String resposta = this.buscarNaApi(moedas);

        responderJson(out, 200, "OK", resposta);
    }
}
