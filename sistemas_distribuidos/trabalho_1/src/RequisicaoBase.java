import java.io.*;
import java.net.Socket;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.LinkedHashMap;
import java.util.Map;

public abstract class RequisicaoBase implements Runnable {
    private final Socket socket;

    protected RequisicaoBase(Socket socket) {
        this.socket = socket;
    }

    protected abstract void processar(HttpRequestInfo request, PrintWriter out) throws Exception;

    @Override
    public final void run() {
        BufferedReader in = null;
        PrintWriter out = null;

        try {
            in = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
            out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true);

            HttpRequestInfo request = lerRequisicao(in);
            if (request == null) {
                responderJson(out, 400, "Bad Request", "{\"erro\": \"Requisição inválida\"}");
                return;
            }

            processar(request, out);
        } catch (Exception e) {
            if (out != null) {
                responderJson(out, 500, "Internal Server Error",
                        "{\"erro\": \"" + (e.getMessage() == null ? "Erro interno" : e.getMessage()) + "\"}");
            }
        }
    }

    protected void responderJson(PrintWriter out, int statusCode, String statusText, String body) {
        responder(out, statusCode, statusText, "application/json; charset=UTF-8", body);
    }

    protected void responder(PrintWriter out, int statusCode, String statusText, String contentType, String body) {
        String resposta = body == null ? "" : body;
        byte[] bytes = resposta.getBytes(StandardCharsets.UTF_8);
        out.print("HTTP/1.1 " + statusCode + " " + statusText + "\r\n");
        out.print("Content-Type: " + contentType + "\r\n");
        out.print("Content-Length: " + bytes.length + "\r\n");
        out.print("Connection: close\r\n\r\n");
        out.print(resposta);
        out.flush();
    }

    protected Map<String, String> extrairQueryParams(String requestTarget) {
        Map<String, String> params = new LinkedHashMap<>();
        int indiceQuery = requestTarget.indexOf('?');
        if (indiceQuery < 0 || indiceQuery == requestTarget.length() - 1) {
            return params;
        }

        String query = requestTarget.substring(indiceQuery + 1);
        String[] pares = query.split("&");
        for (String par : pares) {
            if (par.isBlank()) {
                continue;
            }
            String[] chaveValor = par.split("=", 2);
            String chave = urlDecode(chaveValor[0]);
            String valor = chaveValor.length == 2 ? urlDecode(chaveValor[1]) : "";
            params.put(chave, valor);
        }

        return params;
    }

    private HttpRequestInfo lerRequisicao(BufferedReader in) throws IOException {
        String requestLine = in.readLine();
        if (requestLine == null || requestLine.isBlank()) {
            return null;
        }

        String[] requestParts = requestLine.split(" ", 3);
        if (requestParts.length < 2) {
            return null;
        }

        String target = requestParts[1].trim();
        String path = target.split("\\?", 2)[0];

        String line;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
        }

        return new HttpRequestInfo(path, extrairQueryParams(target));
    }

    private String urlDecode(String value) {
        return URLDecoder.decode(value, StandardCharsets.UTF_8);
    }

}
