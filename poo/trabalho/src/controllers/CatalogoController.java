package controllers;

import dto.CategoriaDto;
import dto.ItemDto;
import exception.CategoriaException;
import exception.ItemException;
import model.Categoria;
import model.Item;

import java.io.Serializable;
import java.util.*;

public class CatalogoController implements Serializable {
    private static final long serialVersionUID = -6427195665424781733L;
    private final Map<String, Categoria> categorias;
    private final Map<Long, Item> itens;

    public CatalogoController() {
        categorias = new TreeMap<>();
        itens = new TreeMap<>();
    }

    public void criarCategoria(CategoriaDto categoriaDto) throws CategoriaException {
        String nome = categoriaDto.getNome();
        if (categorias.containsKey(nome)) {
            throw new CategoriaException("Já existe uma categoria com o nome " + nome);
        }

        Categoria categoria = categoriaDto.toDomain();
        categorias.put(nome, categoria);

        MainController.save();
    }

    public CategoriaDto getCategoriaDTO(String nome) throws CategoriaException {
        Categoria categoria = categorias.get(nome);

        if (categoria == null) {
            throw new CategoriaException("Não foi encontrado uma categoria com o nome " + nome);
        }

        return categoria.toDto();
    }

    private Categoria getCategoria(String nome) throws CategoriaException {
        Categoria categoria = categorias.get(nome);

        if (categoria == null) {
            throw new CategoriaException("Não foi encontrado uma categoria com o nome " + nome);
        }

        return categoria;
    }

    public Set<String> getCategorias() {
        return categorias.keySet();
    }

    public void criarItens(String nomeCategoria, ItemDto itemDto) throws ItemException, CategoriaException {
        long codigo = itemDto.getCodigo();
        if (itens.containsKey(codigo)) {
            throw new ItemException("Já existe um item com o codigo " + codigo);
        }

        Categoria categoria = getCategoria(nomeCategoria);
        Item item = itemDto.toDomain();

        categoria.addItem(item);
        itens.put(codigo, item);

        MainController.save();
    }

    public ItemDto getItemDto(long codigo) throws ItemException {
        Item item = itens.get(codigo);

        if (item == null) {
            throw new ItemException("Não foi encontrado um item com o codigo " + codigo);
        }

        return item.toDto();
    }

    public List<ItemDto> getItensByCategoria(String nomeCategoria) throws CategoriaException {
        Categoria categoria = getCategoria(nomeCategoria);
        List<ItemDto> itemDtos = new ArrayList<>();
        for (Item item : categoria.getItens()) {
            itemDtos.add(item.toDto());
        }
        return itemDtos;
    }

    public Set<Long> getItens() {
        return itens.keySet();
    }
}