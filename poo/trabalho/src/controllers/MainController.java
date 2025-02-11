package controllers;

import java.io.Serializable;

import persistence.Serializer;

public class MainController implements Serializable {

	private static final long serialVersionUID = 970891977812041717L;

	static MainController instance;

	private final CatalogoController catalogoController;
	private final AcomodacaoController acomodacaoController;
	private final HospedagemController hospedagemController;
	private final HospedeController hospedeController;

	private MainController() {
		catalogoController = new CatalogoController();
		acomodacaoController = new AcomodacaoController();
		hospedagemController = new HospedagemController();
		hospedeController = new HospedeController();
	}

	public static MainController getInstance() {
		return instance;
	}

	public static CatalogoController getCatalogoController() {
		return instance.catalogoController;
	}

	public static AcomodacaoController getAcomodacaoController() {
		return instance.acomodacaoController;
	}

	public static HospedagemController getHospedagemController() {
		return instance.hospedagemController;
	}

	public static HospedeController getHospedeController() {
		return instance.hospedeController;
	}

	public static void load() {

		instance = Serializer.readFile();

		if (instance == null) {
			instance = new MainController();
		}
	}

	public static void save() {
		Serializer.writeFile(instance);
	}
}
