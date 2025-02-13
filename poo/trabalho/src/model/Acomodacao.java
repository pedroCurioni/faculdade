package model;

import java.io.Serializable;

import dto.AcomodacaoDto;
import enums.EEstadoOcupacao;
import exception.AcomodacaoException;

public class Acomodacao implements IAcomodacao, Serializable {

    private static final long serialVersionUID = -4481161490787219312L;
    private final int numero;
    private final int ocupacaoMax;
    private EEstadoOcupacao estadoOcupacao;
    private TipoAcomodacao tipo;

    public Acomodacao(int numero, int ocupacaoMax, TipoAcomodacao tipo) throws AcomodacaoException {
        super();

        if (numero <= 0) {
            throw new AcomodacaoException("Número da acomodação deve ser maior que zero.");
        }

        if (ocupacaoMax <= 0) {
            throw new AcomodacaoException("Ocupação máxima da acomodação deve ser maior que zero.");
        }

        if (tipo == null) {
            throw new AcomodacaoException("Tipo da acomodação não pode ser nulo.");
        }

        this.numero = numero;
        this.ocupacaoMax = ocupacaoMax;
        this.estadoOcupacao = EEstadoOcupacao.DISPONIVEL;
        this.tipo = tipo;
    }

    public EEstadoOcupacao getEstadoOcupacao() {
        return estadoOcupacao;
    }

    public void setEstadoOcupacao(EEstadoOcupacao estadoOcupacao) {
        this.estadoOcupacao = estadoOcupacao;
    }

    public String getTipo() {
        return tipo.getNome();
    }

    public void setTipo(TipoAcomodacao tipo) {
        this.tipo = tipo;
    }

    public int getNumero() {
        return numero;
    }

    public int getOcupacaoMax() {
        return ocupacaoMax;
    }

    @Override
    public double getTarifaDiaria() {

        return tipo.getTarifaDiaria();
    }

    @Override
    public double getAdicionaAcompanhante() {
        return tipo.getAdicionaAcompanhante();
    }

    public AcomodacaoDto toDto() {
        return new AcomodacaoDto(
                this.numero,
                this.ocupacaoMax,
                this.estadoOcupacao,
                this.tipo.toDto()
        );
    }

}
