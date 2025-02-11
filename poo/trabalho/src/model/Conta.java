package model;

import dto.ContaDto;
import dto.ItemContaDto;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Conta implements IConta, Serializable {

	private static final long serialVersionUID = 3217615595279629049L;
	private final ArrayList<ItemConta> itens;

	public Conta() {
		this.itens = new ArrayList<ItemConta>();
	}

	public ArrayList<ItemConta> getItens() {
		return itens;
	}

	@Override
	public void addItem(Item item, int qtde) {
		ItemConta ic = new ItemConta(new Date(), item.getPreco(), qtde, item);
		itens.add(ic);
	}

	@Override
	public void removeItem(int index) {
		itens.remove(index);
	}

	@Override
	public double getTotal() {
		double total = 0;

		for (ItemConta itemConta : itens) {
			total += itemConta.getTotal();
		}

		return total;
	}

	@Override
	public StringBuilder listar() {
		StringBuilder sb = new StringBuilder();

		for (ItemConta itemConta : itens) {
			sb.append("\n").append(itemConta.listar());
		}

		return sb;
	}

	public ContaDto toDto() {
		ArrayList<ItemContaDto> itemDtos = new ArrayList<>();
		for (ItemConta item : this.itens) {
			itemDtos.add(item.toDto());
		}
		return new ContaDto(itemDtos);
	}
}
