package model;

import java.io.Serializable;
import java.util.ArrayList;

import dto.CategoriaDto;
import exception.CategoriaException;

public class Categoria implements Serializable {
	private static final long serialVersionUID = -3816983440209789588L;
	private final String nome;
	private final ArrayList<Item> itens;

	public Categoria(String nome) throws CategoriaException {
		super();

		if (nome == null) {
			throw new CategoriaException("Nome da categoria deve ser preenchido");
		}

		this.nome = nome;
		this.itens = new ArrayList<Item>();
	}

	public String getNome() {
		return nome;
	}

	public ArrayList<Item> getItens() {
		return itens;
	}

	public void addItem(Item item) {
		itens.add(item);
	}

	public CategoriaDto toDto() {
		return new CategoriaDto(this.nome);
	}

}
