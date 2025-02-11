package model;

import dto.PagamentoDto;
import enums.ETipoPagamento;
import exception.PagamentoException;

import java.io.Serializable;
import java.util.Date;

public class Pagamento implements Serializable {
    private static final long serialVersionUID = 1167913784242792062L;
    private final ETipoPagamento tipo;
    private final Date data;
    private final double valor;

    public Pagamento(ETipoPagamento tipo, Date data, double valor) throws PagamentoException {
        this.tipo = tipo;
        this.data = data;

        if (valor < 0) {
            throw new PagamentoException("Valor deve ser maior que 0");
        }

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

    public PagamentoDto toDto() {
        return new PagamentoDto(this.tipo, this.data, this.valor);
    }

}
