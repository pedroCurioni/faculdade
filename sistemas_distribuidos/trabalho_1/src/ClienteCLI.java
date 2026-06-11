import java.net.URI;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ClienteCLI {

    private static final String SERVER_USUARIOS = "http://localhost:8081";
    private static final String SERVER_COTACAO = "http://localhost:8080";

    private static final HttpClient httpClient = HttpClient.newHttpClient();
    private static final Scanner scanner = new Scanner(System.in);

    private static String loggedUser = null;
    private static int loggedPerfil = -1;

    public static void main(String[] args) {
        System.out.println("==================================");
        System.out.println("    BEM VINDO AO SISTEMA CLI      ");
        System.out.println("==================================");

        while (true) {
            if (loggedUser == null) {
                menuDeslogado();
            } else {
                menuLogado();
            }
        }
    }

    private static void menuDeslogado() {
        System.out.println("\n============== MENU ==============");
        System.out.println("  1. Fazer Login");
        System.out.println("  2. Cadastrar Novo Usuário");
        System.out.println("  3. Sair");
        System.out.println("==================================");
        System.out.print("Escolha uma opção: ");

        String opcao = scanner.nextLine();

        switch (opcao) {
            case "1":
                fazerLogin();
                break;
            case "2":
                cadastrarUsuario();
                break;
            case "3":
                System.out.println("Saindo...");
                System.exit(0);
                break;
            default:
                printError("Opção inválida!");
        }
    }

    private static void menuLogado() {
        System.out.println("\n=========== ÁREA LOGADA ==========");
        System.out.println(" Usuário: " + loggedUser + " | Perfil: " + loggedPerfil);
        System.out.println("----------------------------------");
        System.out.println("  1 - Editar nome de usuário");
        System.out.println("  2 - Alterar senha");
        System.out.println("  3 - Alterar perfil");
        System.out.println("  4 - Excluir usuário");
        System.out.println("  5 - Receber cotação atual do dólar");
        System.out.println("  6 - Sair");
        System.out.println("==================================");
        System.out.print("Escolha uma opção: ");

        String opcao = scanner.nextLine();

        switch (opcao) {
            case "1":
                atualizarNomeUsuario();
                break;
            case "2":
                atualizarSenha();
                break;
            case "3":
                alterarPerfil();
                break;
            case "4":
                excluirUsuario();
                break;
            case "5":
                verCotacoes();
                break;
            case "6":
                System.out.println("Deslogando...");
                loggedUser = null;
                loggedPerfil = -1;
                break;
            default:
                optionInvalid();
        }
    }

    private static void optionInvalid() {
        printError("Opção inválida ou sem permissão!");
        pause();
    }

    private static void pause() {
        System.out.println("\nPressione Enter para continuar...");
        scanner.nextLine();
    }

    private static void printSuccess(String msg) {
        System.out.println("\n  SUCESSO: " + msg);
    }

    private static void printError(String msg) {
        System.out.println("\n  ERRO: " + msg);
    }

    private static void fazerLogin() {
        System.out.println("\n--- LOGIN ---");
        System.out.print("Usuário: ");
        String user = scanner.nextLine();
        System.out.print("Senha: ");
        String pass = scanner.nextLine();

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(SERVER_USUARIOS + "/login?username=" + encode(user) + "&senha=" + encode(pass))).GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                loggedUser = user;
                String body = response.body();
                loggedPerfil = Integer.parseInt(extrairValorJson(body, "perfil"));
                printSuccess(extrairMensagem(body) + " (Perfil: " + loggedPerfil + ")");
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void verCotacoes() {
        System.out.println("\nBuscando cotações...");
        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(SERVER_COTACAO + "/cotacao?perfil=" + loggedPerfil)).GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                System.out.println("\n  --- COTAÇÕES ATUAIS ---");
                String cotacoes = response.body().replaceAll("[\"{}]", "");
                cotacoes = cotacoes.replaceFirst("^data\\s*:\\s*", "").replaceAll(":", " -> ");
                for (String linha : cotacoes.split(",")) {
                    System.out.println("    " + linha.trim());
                }
                System.out.println("  -----------------------");
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void atualizarNomeUsuario() {
        System.out.println("\n--- ATUALIZAR USERNAME ---");
        System.out.print("Novo Nome de Usuário: ");
        String novoUser = scanner.nextLine();

        try {
            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(
                    SERVER_USUARIOS + "/usuarios/username?usernameAtual=" + encode(loggedUser) + "&novoUsername=" + encode(novoUser)))
                    .GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                printSuccess(extrairMensagem(response.body()));
                loggedUser = novoUser;
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void atualizarSenha() {
        System.out.println("\n--- ATUALIZAR SENHA ---");
        System.out.print("Nova Senha: ");
        String novaSenha = scanner.nextLine();

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(
                            SERVER_USUARIOS + "/usuarios/senha?username=" + encode(loggedUser) + "&novaSenha=" + encode(novaSenha)))
                    .GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                printSuccess(extrairMensagem(response.body()));
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void cadastrarUsuario() {
        System.out.println("\n--- CADASTRAR USUÁRIO ---");
        System.out.print("Username do novo usuário: ");
        String user = scanner.nextLine();
        System.out.print("Senha: ");
        String pass = scanner.nextLine();
        System.out.print("Perfil (1, 2): ");
        String perfil = scanner.nextLine();

        if (!(perfil.equals("1") || perfil.equals("2"))) {
            printError("Perfil inválido! Use 1 ou 2.");
            pause();
            return;
        }

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(
                            SERVER_USUARIOS + "/usuarios?username=" + encode(user) + "&senha=" + encode(pass) + "&perfil=" + encode(perfil)))
                    .GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 201) {
                printSuccess(extrairMensagem(response.body()));
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void alterarPerfil() {
        System.out.println("\n--- ALTERAR PERFIL ---");
        System.out.print("Novo Perfil (1, 2): ");
        String novoPerfil = scanner.nextLine();

        if (!(novoPerfil.equals("1") || novoPerfil.equals("2"))) {
            printError("Perfil inválido! Use 1 ou 2.");
            pause();
            return;
        }

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(
                            SERVER_USUARIOS + "/usuarios/perfil?username=" + encode(loggedUser) + "&novoPerfil=" + encode(novoPerfil)))
                    .GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                printSuccess(extrairMensagem(response.body()));
                loggedPerfil = Integer.parseInt(novoPerfil);
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static void excluirUsuario() {
        System.out.println("\n--- EXCLUIR USUÁRIO ---");
        System.out.println("Você está prestes a excluir a sua conta.");

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create(SERVER_USUARIOS + "/usuarios/delete?username=" + encode(loggedUser))).GET().build();

            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

            if (response.statusCode() == 200) {
                printSuccess(extrairMensagem(response.body()));
                loggedUser = null;
                loggedPerfil = -1;
                System.out.println("  [i] Sua conta foi excluída e você foi deslogado.");
            } else {
                printError(extrairErro(response.body()));
            }
        } catch (Exception e) {
            printError("Falha de conexão: " + e.getMessage());
        }
        pause();
    }

    private static String extrairValorJson(String json, String chave) {
        if (json == null || json.isEmpty())
            return null;
        String padrao = "\"" + chave + "\"\\s*:\\s*\"?([^\"},]+)\"?";
        Pattern pattern = Pattern.compile(padrao);
        Matcher matcher = pattern.matcher(json);
        if (matcher.find()) {
            return matcher.group(1).trim();
        }
        return "0";
    }

    private static String extrairErro(String json) {
        if (json == null || json.isEmpty())
            return "Erro desconhecido";
        String padrao = "\"erro\"\\s*:\\s*\"?([^\"},]+)\"?";
        Pattern pattern = Pattern.compile(padrao);
        Matcher matcher = pattern.matcher(json);
        if (matcher.find()) {
            return matcher.group(1).trim();
        }
        return json;
    }

    private static String extrairMensagem(String json) {
        if (json == null || json.isEmpty())
            return "Operação realizada com sucesso";
        String padrao = "\"mensagem\"\\s*:\\s*\"?([^\",}]+)\"?";
        Pattern pattern = Pattern.compile(padrao);
        Matcher matcher = pattern.matcher(json);
        if (matcher.find()) {
            return matcher.group(1).trim();
        }
        return "Operação realizada com sucesso";
    }

    private static String encode(String value) {
        if (value == null) return "";
        return URLEncoder.encode(value, StandardCharsets.UTF_8);
    }
}
