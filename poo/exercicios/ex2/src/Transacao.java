import java.util.Date;

public class Transacao {
    private Date data;
    private double valor;

    public Transacao(Date dataAtual, double valor) {
        this.data = dataAtual;
        this.valor = valor;
    }

    public Date getData() {
        return data;
    }

    public double getValor() {
        return valor;
    }

    public void setValor(double valor) {
        this.valor = valor;
    }
}
