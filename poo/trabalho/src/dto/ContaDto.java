package dto;

import exception.ItemException;
import model.Conta;

import java.util.ArrayList;

public class ContaDto {
    private final ArrayList<ItemContaDto> itens;

    public ContaDto(ArrayList<ItemContaDto> itens) {
        this.itens = itens;
    }

    public ArrayList<ItemContaDto> getItens() {
        return itens;
    }

    public Conta toDomain() throws ItemException {
        Conta conta = new Conta();
        for (ItemContaDto itemDto : this.itens) {
            conta.getItens().add(itemDto.toDomain());
        }
        return conta;
    }
}
