package dto;

import exception.ItemException;
import model.Item;

public class ItemDto {
    private final long codigo;
    private final String descricao;
    private final double preco;

    public ItemDto(long codigo, String descricao, double preco) {
        this.codigo = codigo;
        this.descricao = descricao;
        this.preco = preco;
    }

    public long getCodigo() {
        return codigo;
    }

    public String getDescricao() {
        return descricao;
    }

    public double getPreco() {
        return preco;
    }

    public Item toDomain() throws ItemException {
        return new Item(this.codigo, this.descricao, this.preco);
    }

    @Override
    public String toString() {
        return "Código: " + codigo + "\n" +
                "Descrição: " + descricao + "\n" +
                "Preço: " + preco + "\n";
    }
}
