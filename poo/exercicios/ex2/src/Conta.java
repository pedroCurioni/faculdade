import java.util.ArrayList;
import java.util.Date;

public class Conta {
    private int numero;
    private final Date dataAbertura;
    private Cliente titular;
    private ArrayList<Transacao> credito;
    private ArrayList<Transacao> debito;

    public Conta(int num, Date currentDdate) {
        this.numero = num;
        this.dataAbertura = currentDdate;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public Date getDataAbertura() {
        return dataAbertura;
    }

    public Cliente getTitular() {
        return titular;
    }

    public void setTitular(Cliente titular) {
        this.titular = titular;
    }

    public void depositar(double valor) {
        Date dataAtual = new Date();
        Transacao novaTransacao = new Transacao(dataAtual, valor);
        this.credito.add(novaTransacao);
    }

    public void sacar(double valor) {
        if (this.getSaldo() > valor) {
            System.out.println("Valor desejado maior que o saldo disponível!");
            return;
        }

        Date dataAtual = new Date();
        Transacao novaTransacao = new Transacao(dataAtual, valor);
        this.debito.add(novaTransacao);
    }

    public double getTotalCredito() {
        double total = 0;
        for (Transacao transacao : this.credito) {
            total += transacao.getValor();
        }
        return total;
    }

    public double getTotalDebito() {
        double total = 0;
        for (Transacao transacao : this.debito) {
            total += transacao.getValor();
        }
        return total;
    }

    public double getSaldo() {
        return this.getTotalCredito() - this.getTotalDebito();
    }
}
