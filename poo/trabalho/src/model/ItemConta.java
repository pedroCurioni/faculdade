package model;

import dto.ItemContaDto;

import java.io.Serializable;
import java.util.Date;

public class ItemConta implements Serializable {
    private static final long serialVersionUID = 2176207967460925086L;
    private final Date dataHora;
    private final double preco;
    private final int qtde;

    private final Item item;

    public ItemConta(Date dataHora, int qtde, Item item) {
        super();
        this.dataHora = dataHora;
        this.preco = item.getPreco();
        this.qtde = qtde;
        this.item = item;
    }

    public Date getDataHora() {
        return dataHora;
    }

    public double getPreco() {
        return preco;
    }

    public int getQtde() {
        return qtde;
    }

    public Item getItem() {
        return item;
    }

    public double getTotal() {
        return getPreco() * getQtde();
    }

    public StringBuilder listar() {
        StringBuilder sb = new StringBuilder();

        sb.append("Data de compra: ").append(dataHora);
        sb.append("\nPreco do item no pedido:").append(preco);
        sb.append("\nQuantidade: ").append(qtde);

        sb.append(item.listar());

        return sb;

    }

    public ItemContaDto toDto() {
        return new ItemContaDto(this.dataHora, this.preco, this.qtde, this.item.toDto());
    }
}
