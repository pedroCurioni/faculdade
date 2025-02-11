package model;

import dto.HospedeDto;

public interface IHospede {

    public String getCpf();

    public String getNome();

    public String getEmail();

    public long getTelefone();

    public HospedeDto toDto();

}
