package dto;

import exception.ItemException;
import model.ItemConta;

import java.util.Date;

public class ItemContaDto {
    private final Date dataHora;
    private final double preco;
    private final int qtde;
    private final ItemDto itemDto;

    public ItemContaDto(Date dataHora, double preco, int qtde, ItemDto itemDto) {
        this.dataHora = dataHora;
        this.preco = preco;
        this.qtde = qtde;
        this.itemDto = itemDto;
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

    public ItemDto getItemDto() {
        return itemDto;
    }

    public ItemConta toDomain() throws ItemException {
        return new ItemConta(this.dataHora, this.preco, this.qtde, this.itemDto.toDomain());
    }
}
