package controllers;

import dto.HospedagemDto;
import dto.HospedeDto;
import dto.ItemDto;
import dto.PagamentoDto;
import enums.ETipoPagamento;
import exception.*;
import model.Hospedagem;
import model.IHospede;
import model.Pagamento;

import java.io.Serializable;
import java.util.*;

public class HospedagemController implements Serializable {

    private static final long serialVersionUID = 1655952344085199124L;

    private final Map<String, Hospedagem> hospedagens;

    public HospedagemController() {
        hospedagens = new TreeMap<>();
    }

    public String createHospedagem(HospedagemDto hospedagemDto) throws HospedagemException, HospedeException, TipoAcomodacaoException, AcomodacaoException, PagamentoException, ItemException {
        Hospedagem hospedagem = hospedagemDto.toDomain();
        hospedagens.put(hospedagem.getId(), hospedagem);

        MainController.save();

        return hospedagem.getId();
    }

    public Set<String> getHospedagens() {
        return hospedagens.keySet();
    }

    public HospedagemDto getHospedagemDto(String id) throws HospedagemException, TipoAcomodacaoException {
        Hospedagem hospedagem = hospedagens.get(id);

        if (hospedagem == null) {
            throw new HospedagemException("Hospedagem não encontrada");
        }

        return hospedagem.toDto();
    }

    public Hospedagem getHospedagem(String id) throws HospedagemException, TipoAcomodacaoException {
        Hospedagem hospedagem = hospedagens.get(id);

        if (hospedagem == null) {
            throw new HospedagemException("Hospedagem não encontrada");
        }

        return hospedagem;
    }


    public void addAcompanhante(String idHospedagem, ArrayList<HospedeDto> acompanhantesDto) throws TipoAcomodacaoException, HospedagemException, HospedeException, AcomodacaoException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);

        ArrayList<IHospede> acompanhantes = new ArrayList<>();
        for (HospedeDto hospede : acompanhantesDto) {
            acompanhantes.add(hospede.toDomain());
        }

        hospedagem.addAcompanhantes(acompanhantes);

        MainController.save();
    }

    public void addPagamento(String idHospedagem, PagamentoDto pagamentoDto) throws PagamentoException, TipoAcomodacaoException, HospedagemException {
        Pagamento pagamento = pagamentoDto.toDomain();

        Hospedagem hospedagem = getHospedagem(idHospedagem);
        hospedagem.addPagamento(pagamento);

        MainController.save();
    }

    public void addItemConta(String idHospedagem, ItemDto itemDto, int qtde) throws HospedagemException, ItemException, TipoAcomodacaoException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);
        hospedagem.addItem(itemDto.toDomain(), qtde);

        MainController.save();
    }

    public void removeItemConta(String idHospedagem, int index) throws TipoAcomodacaoException, HospedagemException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);
        hospedagem.removeItem(index);

        MainController.save();
    }

    public StringBuilder listarHospedagem(String idHospedagem) throws HospedagemException, TipoAcomodacaoException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);
        return hospedagem.listar();
    }

    public StringBuilder listarConta(String idHospedagem) throws HospedagemException, TipoAcomodacaoException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);
        return hospedagem.listarConta();
    }

    public void checkout(String idHospedagem, PagamentoDto pagamentoFinalDto) throws HospedagemException, PagamentoException, TipoAcomodacaoException, AcomodacaoException, HospedeException {
        Hospedagem hospedagem = getHospedagem(idHospedagem);
        Pagamento pagamento = null;
        if (pagamentoFinalDto != null) {
            pagamento = pagamentoFinalDto.toDomain();
        } else {
            // Não houve pagamento final, então o pagamento é 0
            pagamento = new Pagamento(ETipoPagamento.DEBITO, new Date(), 0);
        }
        hospedagem.checkout(pagamento);
        MainController.save();
    }
}