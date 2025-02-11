package dto;

import enums.EEstadoOcupacao;
import exception.AcomodacaoException;
import exception.TipoAcomodacaoException;
import model.Acomodacao;

public class AcomodacaoDto {
    private final int numero;
    private final int ocupacaoMax;
    private final EEstadoOcupacao estadoOcupacao;
    private final TipoAcomodacaoDto tipoAcomodacaoDto;

    public AcomodacaoDto(int numero, int ocupacaoMax, EEstadoOcupacao estadoOcupacao, TipoAcomodacaoDto tipoAcomodacaoDto) {
        this.numero = numero;
        this.ocupacaoMax = ocupacaoMax;
        this.estadoOcupacao = estadoOcupacao;
        this.tipoAcomodacaoDto = tipoAcomodacaoDto;
    }

    public int getNumero() {
        return numero;
    }

    public int getOcupacaoMax() {
        return ocupacaoMax;
    }

    public EEstadoOcupacao getEstadoOcupacao() {
        return estadoOcupacao;
    }

    public TipoAcomodacaoDto getTipoAcomodacaoDto() {
        return tipoAcomodacaoDto;
    }

    public Acomodacao toDomain() throws TipoAcomodacaoException, AcomodacaoException {
        return new Acomodacao(this.numero, this.ocupacaoMax, this.tipoAcomodacaoDto.toDomain());
    }

    @Override
    public String toString() {
        return "Número: " + numero + "\n" + "Ocupação Máxima: " + ocupacaoMax + "\n" + "Estado de Ocupação: " + estadoOcupacao + "\n" + "Tipo de Acomodação: " + tipoAcomodacaoDto.getNome() + "\n";
    }
}
