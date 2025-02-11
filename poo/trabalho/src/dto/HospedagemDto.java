package dto;

import exception.AcomodacaoException;
import exception.HospedagemException;
import exception.HospedeException;
import exception.TipoAcomodacaoException;
import model.Hospedagem;

import java.util.ArrayList;
import java.util.Date;

public class HospedagemDto {
    private final String id;
    private final Date checkin;
    private final Date checkout;
    private final HospedeDto hospede;
    private final ArrayList<HospedeDto> acompanhantes;
    private final AcomodacaoDto acomodacao;
    private final ContaDto conta;
    private final ArrayList<PagamentoDto> pagamento;

    public HospedagemDto(String id, Date checkin, HospedeDto hospede, ArrayList<HospedeDto> acompanhantes, AcomodacaoDto acomodacao, ContaDto conta, ArrayList<PagamentoDto> pagamento, Date checkout) {
        this.id = id;
        this.checkin = checkin;
        this.hospede = hospede;
        this.acompanhantes = acompanhantes;
        this.acomodacao = acomodacao;
        this.conta = conta;
        this.pagamento = pagamento;
        this.checkout = checkout;
    }

    public String getId() {
        return id;
    }

    public Date getCheckin() {
        return checkin;
    }

    public Date getCheckout() {
        return checkout;
    }

    public HospedeDto getHospede() {
        return hospede;
    }

    public ArrayList<HospedeDto> getAcompanhantes() {
        return acompanhantes;
    }

    public AcomodacaoDto getAcomodacao() {
        return acomodacao;
    }

    public ContaDto getConta() {
        return conta;
    }

    public ArrayList<PagamentoDto> getPagamento() {
        return pagamento;
    }

    public Hospedagem toDomain() throws HospedeException, TipoAcomodacaoException, AcomodacaoException, HospedagemException {
        return new Hospedagem(this.hospede.toDomain(), this.acomodacao.toDomain());
    }
}
