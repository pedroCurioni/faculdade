package model;

import dto.ItemDto;
import exception.ItemException;

import java.io.Serializable;

public class Item implements Serializable {
    private static final long serialVersionUID = -6616683975198871159L;
    private final long codigo;
    private final String descricao;
    private double preco;

    public Item(long codigo, String descricao, double preco) throws ItemException {
        super();

        if (codigo <= 0) {
            throw new ItemException("O código do produto deve ser maior que zero.");
        }

        if (descricao == null || descricao.isEmpty()) {
            throw new ItemException("A descrição do produto deve ser preenchida.");
        }

        this.codigo = codigo;
        this.descricao = descricao;
        this.setPreco(preco);
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) throws ItemException {
        if (preco <= 0) {
            throw new ItemException("O preço do produto deve ser maior que 0");
        }

        this.preco = preco;
    }

    public long getCodigo() {
        return codigo;
    }

    public String getDescricao() {
        return descricao;
    }

    public StringBuilder listar() {
        StringBuilder sb = new StringBuilder();

        sb.append("\nCodigo: ").append(codigo);
        sb.append("\nDescrição: ").append(descricao);
        sb.append("\tPreço: ").append(preco);

        return sb;
    }

    public ItemDto toDto() {
        return new ItemDto(this.codigo, this.descricao, this.preco);
    }

}
