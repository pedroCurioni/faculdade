package dto;

import exception.HospedeException;
import model.Hospede;

public class HospedeDto {
    private final String cpf;
    private final String nome;
    private final String email;
    private final long telefone;

    public HospedeDto(String cpf, String nome, String email, long telefone) {
        this.cpf = cpf;
        this.nome = nome;
        this.email = email;
        this.telefone = telefone;
    }

    public String getCpf() {
        return cpf;
    }

    public String getNome() {
        return nome;
    }

    public String getEmail() {
        return email;
    }

    public long getTelefone() {
        return telefone;
    }

    public Hospede toDomain() throws HospedeException {
        return new Hospede(this.cpf, this.nome, this.email, this.telefone);
    }

    @Override
    public String toString() {
        return "CPF: " + cpf + "\n" +
                "Nome: " + nome + "\n" +
                "Email: " + email + "\n" +
                "Telefone: " + telefone + "\n";
    }
}
