package controllers;

import dto.HospedeDto;
import exception.HospedeException;
import model.Hospede;

import java.io.Serializable;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class HospedeController implements Serializable {

    private static final long serialVersionUID = 5200395999076182997L;

    private final Map<String, Hospede> hospedes;

    public HospedeController() {
        hospedes = new TreeMap<>();
    }

    public void createHospede(HospedeDto hospedeDto) throws HospedeException {
        if (hospedes.containsKey(hospedeDto.getCpf())) {
            throw new HospedeException("Já existe um hospede com o CPF" + hospedeDto.getCpf());
        }

        Hospede hospede = hospedeDto.toDomain();
        hospedes.put(hospede.getCpf(), hospede);

        MainController.save();
    }

    public HospedeDto getHospedeDto(String cpf) throws HospedeException {
        Hospede hospede = hospedes.get(cpf);

        if (hospede == null) {
            throw new HospedeException("Não foi encontrado um hospede com o CPF" + cpf);
        }

        return hospede.toDto();
    }

    public Set<String> getHospedes() {
        return hospedes.keySet();
    }
}