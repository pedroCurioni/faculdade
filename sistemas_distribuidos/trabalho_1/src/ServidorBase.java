import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public abstract class ServidorBase {
    private final ExecutorService threadPool;

    protected ServidorBase(int quantidadeThreads) {
        this.threadPool = Executors.newFixedThreadPool(quantidadeThreads);
    }

    protected abstract int getPorta();

    protected abstract RequisicaoBase criarRequisicao(Socket socket);

    public void iniciar() {
        try (ServerSocket serverSocket = new ServerSocket(getPorta())) {
            System.out.println("Servidor iniciado na porta " + getPorta());

            while (true) {
                Socket currentSocket = serverSocket.accept();
                threadPool.execute(criarRequisicao(currentSocket));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        } finally {
            threadPool.shutdown();
        }
    }
}

