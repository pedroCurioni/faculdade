import java.net.Socket;

public class ServidorUsuario extends ServidorBase {
    private final int porta = 8081;

    public ServidorUsuario() {
        super(5);
    }

    public static void main(String[] args) {
        new ServidorUsuario().iniciar();
    }

    @Override
    protected int getPorta() {
        return porta;
    }

    @Override
    protected RequisicaoBase criarRequisicao(Socket socket) {
        return new RequisicaoUsuario(socket);
    }
}


