package dto;

import exception.CategoriaException;
import model.Categoria;

import java.util.ArrayList;
import java.util.stream.Collectors;

public class CategoriaDto {
    private final String nome;

    public CategoriaDto(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public Categoria toDomain() throws CategoriaException {
        return new Categoria(this.nome);
    }

    @Override
    public String toString() {
        return "Nome: " + nome + "\n";
    }
}
