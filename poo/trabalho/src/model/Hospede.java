package model;

import dto.HospedeDto;
import exception.HospedeException;
import utils.ValidationUtils;

import java.io.Serializable;

public class Hospede implements IHospede, Serializable {
    private static final long serialVersionUID = -9055290333638803998L;
    private final String cpf;
    private String nome;
    private String email;
    private long telefone;

    public Hospede(String cpf, String nome, String email, long telefone) throws HospedeException {
        super();

        if (cpf == null || nome == null || email == null) {
            throw new HospedeException("Todos os dados do hospede devem ser preenchidos");
        }

        if (!ValidationUtils.isValidCpf(cpf)) {
            throw new HospedeException("CPF inválido");
        }

        this.cpf = cpf;
        this.nome = nome;
        setEmail(email);
        setTelefone(telefone);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) throws HospedeException {
        if (!ValidationUtils.isValidEmail(email)) {
            throw new HospedeException("Formato de email inválido");
        }

        this.email = email;
    }

    public long getTelefone() {
        return telefone;
    }

    public void setTelefone(long telefone) throws HospedeException {
        if (!ValidationUtils.isValidPhone(Long.toString(telefone))) {
            throw new HospedeException("Formato de telefone inválido");
        }

        this.telefone = telefone;
    }

    public String getCpf() {
        return cpf;
    }

    public HospedeDto toDto() {
        return new HospedeDto(this.cpf, this.nome, this.email, this.telefone);
    }


}
