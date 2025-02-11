package dto;

import exception.TipoAcomodacaoException;
import model.TipoAcomodacao;

public class TipoAcomodacaoDto {
    private final String nome;
    private final double tarifaDiaria;
    private final double adicionaAcompanhante;

    public TipoAcomodacaoDto(String nome, double tarifaDiaria, double adicionaAcompanhante) {
        this.nome = nome;
        this.tarifaDiaria = tarifaDiaria;
        this.adicionaAcompanhante = adicionaAcompanhante;
    }

    public String getNome() {
        return nome;
    }

    public double getTarifaDiaria() {
        return tarifaDiaria;
    }

    public double getAdicionaAcompanhante() {
        return adicionaAcompanhante;
    }

    public TipoAcomodacao toDomain() throws TipoAcomodacaoException {
        return new TipoAcomodacao(this.nome, this.tarifaDiaria, this.adicionaAcompanhante);
    }

    @Override
    public String toString() {
        return "Nome: " + nome + "\n" +
                "Tarifa Diaria: " + tarifaDiaria + "\n" +
                "Adiciona Acompanhante: " + adicionaAcompanhante + "\n";
    }
}
