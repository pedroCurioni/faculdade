import java.io.PrintWriter;
import java.net.Socket;
import java.util.Map;

public class RequisicaoUsuario extends RequisicaoBase {
    private final UsuarioService usuarioService;

    public RequisicaoUsuario(Socket socket) {
        super(socket);
        this.usuarioService = new UsuarioService();
    }

    @Override
    protected void processar(HttpRequestInfo request, PrintWriter out) {
        try {
            String path = request.path();
            Map<String, String> params = request.queryParams();
            if ("/usuarios".equals(path)) {
                String username = params.get("username");
                String senha = params.get("senha");
                int perfil = Integer.parseInt(params.get("perfil"));

                usuarioService.cadastrarUsuario(new Usuario(username, senha, perfil));
                responderJson(out, 201, "Created", "{\"mensagem\": \"Usuário cadastrado com sucesso!\"}");
                return;
            }
            if ("/login".equals(path)) {
                String username = params.get("username");
                String senha = params.get("senha");

                int perfil = usuarioService.fazerLogin(username, senha);

                if (perfil != -1) {
                    responderJson(out, 200, "OK", "{\"mensagem\": \"Login aprovado\", \"perfil\": " + perfil + "}");
                } else {
                    responderJson(out, 401, "Unauthorized", "{\"erro\": \"Usuário ou senha incorretos\"}");
                }
                return;
            }
            if ("/usuarios/username".equals(path)) {
                String usernameAtual = params.get("usernameAtual");
                String novoUsername = params.get("novoUsername");

                if (usuarioService.editarNomeUsuario(usernameAtual, novoUsername)) {
                    responderJson(out, 200, "OK", "{\"mensagem\": \"Nome de usuário atualizado com sucesso!\"}");
                } else {
                    responderJson(out, 404, "Not Found", "{\"erro\": \"Usuário não encontrado\"}");
                }
                return;
            }
            if ("/usuarios/senha".equals(path)) {
                String username = params.get("username");
                String novaSenha = params.get("novaSenha");

                if (usuarioService.alterarSenha(username, novaSenha)) {
                    responderJson(out, 200, "OK", "{\"mensagem\": \"Senha atualizada com sucesso!\"}");
                } else {
                    responderJson(out, 404, "Not Found", "{\"erro\": \"Usuário não encontrado\"}");
                }
                return;
            }
            if ("/usuarios/perfil".equals(path)) {
                String username = params.get("username");
                int novoPerfil = Integer.parseInt(params.get("novoPerfil"));

                if (usuarioService.alterarPerfil(username, novoPerfil)) {
                    responderJson(out, 200, "OK", "{\"mensagem\": \"Perfil atualizado com sucesso!\"}");
                } else {
                    responderJson(out, 404, "Not Found", "{\"erro\": \"Usuário não encontrado\"}");
                }
                return;
            }
            if ("/usuarios/delete".equals(path)) {
                String username = params.get("username");
                if (username == null || username.isEmpty()) {
                    responderJson(out, 400, "Bad Request", "{\"erro\": \"O parâmetro 'username' é obrigatório\"}");
                    return;
                }

                if (usuarioService.excluirUsuario(username)) {
                    responderJson(out, 200, "OK", "{\"mensagem\": \"Usuário excluído com sucesso!\"}");
                } else {
                    responderJson(out, 404, "Not Found", "{\"erro\": \"Usuário não encontrado\"}");
                }
                return;
            }

            responderJson(out, 404, "Not Found", "{\"erro\": \"Rota não encontrada\"}");

        } catch (IllegalArgumentException e) {
            responderJson(out, 400, "Bad Request", "{\"erro\": \"" + e.getMessage() + "\"}");
        } catch (java.sql.SQLException e) {
            responderJson(out, 500, "Internal Server Error", "{\"erro\": \"Erro de banco de dados: " + e.getMessage() + "\"}");
        } catch (Exception e) {
            responderJson(out, 500, "Internal Server Error", "{\"erro\": \"Erro ao processar a requisição: " + e.getMessage() + "\"}");
        }
    }


}
