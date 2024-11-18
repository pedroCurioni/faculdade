import java.util.ArrayList;
import java.util.Date;

public class Agencia {
    private int numero;
    private long telefone;
    private Gerente gerente;
    private ArrayList<Conta> contas;

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public long getTelefone() {
        return telefone;
    }

    public void setTelefone(long telefone) {
        this.telefone = telefone;
    }

    public Gerente getGerente() {
        return gerente;
    }

    public void setGerente(Gerente gerente) {
        this.gerente = gerente;
    }

    public Conta abrirConta(int num, Cliente titular) {
        Date currentDdate  = new Date();
        return new Conta(num, currentDdate);
    }
}
