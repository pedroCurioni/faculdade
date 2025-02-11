package dto;

import enums.ETipoPagamento;
import exception.PagamentoException;
import model.Pagamento;

import java.util.Date;

public class PagamentoDto {
    private final ETipoPagamento tipo;
    private final Date data;
    private final double valor;

    public PagamentoDto(ETipoPagamento tipo, Date data, double valor) {
        this.tipo = tipo;
        this.data = data;
        this.valor = valor;
    }

    public ETipoPagamento getTipo() {
        return tipo;
    }

    public Date getData() {
        return data;
    }

    public double getValor() {
        return valor;
    }

    public Pagamento toDomain() throws PagamentoException {
        return new Pagamento(this.tipo, this.data, this.valor);
    }

    @Override
    public String toString() {
        return "Tipo: " + tipo + "\n" +
                "Data: " + data + "\n" +
                "Valor: " + valor + "\n";
    }
}
