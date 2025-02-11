package model;

import controllers.CatalogoController;
import dto.HospedagemDto;
import dto.HospedeDto;
import dto.ItemContaDto;
import dto.PagamentoDto;
import enums.EEstadoOcupacao;
import exception.AcomodacaoException;
import exception.HospedagemException;
import exception.TipoAcomodacaoException;

import javax.swing.*;
import java.io.Serializable;
import java.lang.reflect.Array;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Objects;
import java.util.UUID;

public class Hospedagem implements Serializable {

    private static final long serialVersionUID = -7784924975867217982L;
    private static int InicioCheckIn = 13;
    private static int limiteCheckout = 12;
    private final String id = UUID.randomUUID().toString();
    private final Date checkin = new Date();
    private Date checkout = null;

    private final IHospede hospede;
    private final ArrayList<IHospede> acompanhantes = new ArrayList<IHospede>();
    private final IAcomodacao acomodacao;
    private IConta conta = new Conta();
    private final ArrayList<Pagamento> pagamento = new ArrayList<Pagamento>();

    public Hospedagem(IHospede hospede, IAcomodacao acomodacao) throws HospedagemException {
        if (acomodacao.getEstadoOcupacao() != EEstadoOcupacao.DISPONIVEL) {
            throw new HospedagemException("Acomodação indisponivel");
        }

        if (hospede == null) {
            throw new HospedagemException("Hospede não pode ser nulo");
        }

        this.hospede = hospede;
        this.acomodacao = acomodacao;
        this.acomodacao.setEstadoOcupacao(EEstadoOcupacao.OCUPADO);
    }

    public static int getInicioCheckIn() {
        return InicioCheckIn;
    }

    public static int getLimiteCheckout() {
        return limiteCheckout;
    }

    public Date getCheckin() {
        return checkin;
    }

    public Date getCheckout() {
        return checkout;
    }

    public void setCheckout(Date checkout) {
        this.checkout = checkout;
    }

    public IHospede getHospede() {
        return hospede;
    }

    public IAcomodacao getAcomodacao() {
        return acomodacao;
    }

    public IConta getConta() {
        return conta;
    }

    public ArrayList<Pagamento> getPagamento() {
        return pagamento;
    }

    public String getId() {
        return id;
    }

    public ArrayList<IHospede> getAcompanhantes() {
        return acompanhantes;
    }

    public void addPagamento(Pagamento p) {
        pagamento.add(p);
    }

    public void addItem(Item item, int qtde) {
        conta.addItem(item, qtde);
    }

    public void removeItem(int index) {
        conta.removeItem(index);
    }

    public void addAcompanhantes(ArrayList<IHospede> i) throws AcomodacaoException {
        if (i.size() + quantidadeOcupantes() > acomodacao.getOcupacaoMax()) {
            throw new AcomodacaoException("Quantidade de acompanhantes excede a capacidade da acomodação");
        }

        acompanhantes.addAll(i);
    }

    public int quantidadeOcupantes() {
        return acompanhantes.size() + 1;
    }

    public double calculaTotalDiaria() {
        return (acomodacao.getTarifaDiaria() + acomodacao.getAdicionaAcompanhante()) * (Integer.max(quantidadeOcupantes() - 1, 1));
    }

    public static long getIntervaloDias(Date dataInicial, Date dataFinal) {
        long milisegundoPorDia = (24 * 60 * 60 * 1000);
        return (dataFinal.getTime() - dataInicial.getTime()) / milisegundoPorDia;
    }

    public double precoTotalHospedagem() {
        int intervaloDias = (int) getIntervaloDias(checkin, Objects.requireNonNullElseGet(checkout, Date::new));

        return Integer.max(intervaloDias, 1) * calculaTotalDiaria();

    }

    public double precoTotalPagamento() {
        double total = 0;
        for (Pagamento p : pagamento) {
            total += p.getValor();
        }
        return total;
    }

    public double precoTotal() {
        return precoTotalHospedagem() + conta.getTotal();
    }

    public StringBuilder listarConta() {
        return conta.listar();
    }

    public StringBuilder listar() {

        StringBuilder sb = new StringBuilder();

        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");

        sb.append("Hospede: ").append(hospede.getNome());
        sb.append("\nTipo: ").append(acomodacao.getTipo());
        sb.append("\nCheckin: ").append(sdf.format(getCheckin()));

        if (checkout == null) {
            sb.append("\nCheckout:").append("Ainda não fez checkout");
        } else {
            sb.append("\nCheckout: ").append(sdf.format(getCheckout()));
        }

        sb.append("\n---\nConta: ").append(conta.listar()).append("\n---");

        sb.append("\nOcupantes: ").append(quantidadeOcupantes());
        sb.append("\nValor Total Diaria: ").append(calculaTotalDiaria());
        sb.append("\nTotal Pagamentos: ").append(precoTotalPagamento());
        sb.append("\nPreco Total: ").append(precoTotal());

        return sb;
    }

    public void checkout(Pagamento pagamentoFinal) throws HospedagemException {
        if (precoTotalPagamento() + pagamentoFinal.getValor() < precoTotal()) {
            throw new HospedagemException("Pagamento insuficiente, faltando R$ " + (precoTotal() - (precoTotalPagamento() + pagamentoFinal.getValor())));
        }

        if (pagamentoFinal.getValor() > 0) {
            pagamento.add(pagamentoFinal);
        }

        checkout = new Date();
    }

    public HospedagemDto toDto() throws TipoAcomodacaoException {
        ArrayList<HospedeDto> acompanhantesDto = new ArrayList<>();
        for (IHospede acompanhante : this.acompanhantes) {
            acompanhantesDto.add(((Hospede) acompanhante).toDto());
        }
        ArrayList<PagamentoDto> pagamentosDto = new ArrayList<>();
        for (Pagamento pagamento : this.pagamento) {
            pagamentosDto.add(pagamento.toDto());
        }
        return new HospedagemDto(this.id, this.checkin, ((Hospede) this.hospede).toDto(), acompanhantesDto, ((Acomodacao) this.acomodacao).toDto(), this.conta.toDto(), pagamentosDto, this.checkout);
    }

}
