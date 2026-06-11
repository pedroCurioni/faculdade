import java.net.Socket;

public class ServidorCotacaoMoedas extends ServidorBase {
    private final int porta = 8080;

    public ServidorCotacaoMoedas() {
        super(5);
    }

    public static void main(String[] args) {
        new ServidorCotacaoMoedas().iniciar();
    }

    @Override
    protected int getPorta() {
        return porta;
    }

    @Override
    protected RequisicaoBase criarRequisicao(Socket socket) {
        return new RequisicaoCotacaoMoedas(socket);
    }
}
