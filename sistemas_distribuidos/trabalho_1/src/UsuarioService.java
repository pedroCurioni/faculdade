import io.github.cdimascio.dotenv.Dotenv;

import java.sql.*;

public class UsuarioService {
    private final String postgres_url;
    private final String postgres_user;
    private final String postgres_password;

    public UsuarioService() {
        Dotenv dotenv = Dotenv.load();

        this.postgres_url = dotenv.get("POSTGRES_URL");
        this.postgres_user = dotenv.get("POSTGRES_USER");
        this.postgres_password = dotenv.get("POSTGRES_PASSWORD");

        criarTabelaUsuariosSeNaoExistir();
    }

    private Connection conectar() throws SQLException {
        return DriverManager.getConnection(this.postgres_url, this.postgres_user, this.postgres_password);
    }

    private void criarTabelaUsuariosSeNaoExistir() {
        String sql = "CREATE TABLE IF NOT EXISTS usuarios ("
                + "id SERIAL PRIMARY KEY, "
                + "username VARCHAR(100) UNIQUE NOT NULL, "
                + "senha VARCHAR(100) NOT NULL, "
                + "perfil INTEGER CHECK (perfil IN (1, 2)) NOT NULL"
                + ")";

        try (Connection conn = conectar(); Statement stmt = conn.createStatement()) {
            stmt.execute(sql);
        } catch (SQLException e) {
            System.err.println("Erro ao garantir tabela usuarios: " + e.getMessage());
        }
    }

    public void cadastrarUsuario(Usuario usuario) throws SQLException {
        String sql = "INSERT INTO usuarios (username, senha, perfil) VALUES (?, ?, ?)";
        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, usuario.getUsername());
            stmt.setString(2, usuario.getSenha());
            stmt.setInt(3, usuario.getPerfil());
            stmt.executeUpdate();
            System.out.println("Usuário cadastrado com sucesso!");
        }
    }

    public boolean editarNomeUsuario(String usernameAtual, String novoUsername) throws SQLException {
        String sql = "UPDATE usuarios SET username = ? WHERE username = ?";
        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, novoUsername);
            stmt.setString(2, usernameAtual);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Nome de usuário atualizado com sucesso!");
                return true;
            } else {
                System.out.println("Usuário não encontrado.");
                return false;
            }
        }
    }

    public boolean alterarSenha(String username, String novaSenha) throws SQLException {
        String sql = "UPDATE usuarios SET senha = ? WHERE username = ?";
        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, novaSenha);
            stmt.setString(2, username);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Senha atualizada com sucesso!");
                return true;
            } else {
                System.out.println("Usuário não encontrado.");
                return false;
            }
        }
    }

    public boolean alterarPerfil(String username, int novoPerfil) throws SQLException {
        String sql = "UPDATE usuarios SET perfil = ? WHERE username = ?";
        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, novoPerfil);
            stmt.setString(2, username);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Perfil atualizado com sucesso!");
                return true;
            } else {
                System.out.println("Usuário não encontrado.");
                return false;
            }
        }
    }

    public boolean excluirUsuario(String username) throws SQLException {
        String sql = "DELETE FROM usuarios WHERE username = ?";
        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            int rows = stmt.executeUpdate();
            if (rows > 0) {
                System.out.println("Usuário excluído com sucesso!");
                return true;
            } else {
                System.out.println("Usuário não encontrado.");
                return false;
            }
        }
    }

    public int fazerLogin(String username, String senhaInput) throws SQLException {
        String sql = "SELECT senha, perfil FROM usuarios WHERE username = ?";

        try (Connection conn = conectar(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    String senhaBanco = rs.getString("senha");
                    int perfil = rs.getInt("perfil");

                    if (senhaBanco.equals(senhaInput)) {
                        return perfil;
                    } else {
                        return -1;
                    }
                }
            }
        }
        return -1;
    }

}
