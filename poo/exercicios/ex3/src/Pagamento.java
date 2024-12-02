import java.util.Date;

public class Pagamento {
    private EPagamento tipo;
    private Date data;
    private double valor;

    public Pagamento(EPagamento tipo, Date data, double valor) {
        this.tipo = tipo;
        this.data = data;
        this.valor = valor;
    }
}
