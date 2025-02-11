package controllers;

import dto.AcomodacaoDto;
import dto.TipoAcomodacaoDto;
import enums.EEstadoOcupacao;
import exception.AcomodacaoException;
import exception.TipoAcomodacaoException;
import model.Acomodacao;
import model.TipoAcomodacao;

import java.io.Serializable;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class AcomodacaoController implements Serializable {

    private static final long serialVersionUID = 3808901469196034034L;
    private final Map<String, TipoAcomodacao> tipos;
    private final Map<Integer, Acomodacao> acomodacoes;

    public AcomodacaoController() {
        tipos = new TreeMap<>();
        acomodacoes = new TreeMap<>();
    }

    public void createTipoAcomodacao(TipoAcomodacaoDto tipoAcomodacaoDto) throws TipoAcomodacaoException {
        if (tipos.containsKey(tipoAcomodacaoDto.getNome())) {
            throw new TipoAcomodacaoException("Já existe um tipo com o nome " + tipoAcomodacaoDto.getNome());
        }

        TipoAcomodacao tipo = tipoAcomodacaoDto.toDomain();
        tipos.put(tipo.getNome(), tipo);

        MainController.save();
    }

    public TipoAcomodacaoDto getTipoAcomodacao(String nome) throws TipoAcomodacaoException {
        TipoAcomodacao tipo = tipos.get(nome);

        if (tipo == null) {
            throw new TipoAcomodacaoException("Não foi encontrado um tipo com o nome " + nome);
        }
        return tipo.toDto();
    }

    public Set<String> getTiposAcomodacao() {
        return tipos.keySet();
    }

    public void createAcomodacao(AcomodacaoDto acomodacaoDto) throws AcomodacaoException, TipoAcomodacaoException {
        if (acomodacoes.containsKey(acomodacaoDto.getNumero())) {
            throw new AcomodacaoException("Já existe uma acomodação com o número " + acomodacaoDto.getNumero());
        }

        Acomodacao acomodacao = acomodacaoDto.toDomain();
        acomodacoes.put(acomodacao.getNumero(), acomodacao);

        MainController.save();
    }

    public Set<Integer> getAcomodacoes() {
        return acomodacoes.keySet();
    }

    public AcomodacaoDto getAcomodacaoDto(int numero) throws AcomodacaoException, TipoAcomodacaoException {
        Acomodacao acomodacao = acomodacoes.get(numero);
        if (acomodacao == null) {
            throw new AcomodacaoException("Não foi encontrada acomodação com o número " + numero);
        }
        return acomodacao.toDto();
    }

    private Acomodacao getAcomodacao(int numero) throws AcomodacaoException {
        Acomodacao acomodacao = acomodacoes.get(numero);
        if (acomodacao == null) {
            throw new AcomodacaoException("Não foi encontrada acomodação com o número " + numero);
        }
        return acomodacao;
    }


    public void alterarEstadoAcomodacao(int numero, EEstadoOcupacao novoEstado) throws AcomodacaoException, TipoAcomodacaoException {
        Acomodacao acomodacao = getAcomodacao(numero);
        acomodacao.setEstadoOcupacao(novoEstado);

        MainController.save();
    }
}