package main;

import controllers.AcomodacaoController;
import controllers.MainController;

public class MainTeste {
	public static void main(String[] args) {
		MainController.load();

//        HospedeController hospedeController = MainController.getHospedeController();
		AcomodacaoController acomodacaoController = MainController.getAcomodacaoController();
		System.out.println(acomodacaoController.getTiposAcomodacao());
//        CatalogoController catalogoController = MainController.getCatalogoController();
//        HospedagemController hospedagemController = MainController.getHospedagemController();
//
//		try {
//			acomodacaoController.createTipoAcomodacao("Suite Master", 2100, 300);
//			acomodacaoController.createTipoAcomodacao("Quarto Simples", 500, 70);
//			acomodacaoController.createAcomodacao(1, 4, "Suite Master");
//		} catch (TipoAcomodacaoException | AcomodacaoException e) {
//			System.out.println(e.getMessage());
//		}
//
//        try {
//            hospedeController.createHospede("123456789", "test", "test@mail.com", 15152125);
//            hospedeController.createHospede("9876543321", "test2", "test2@mail.com", 21525155);
//        } catch (HospedeException e) {
//            System.out.println(e.getMessage());
//        }
//
//        try {
//            catalogoController.criarCategoria("Bebidas");
//
//            catalogoController.criarItens("Bebidas", 1, "Agua", 3);
//            catalogoController.criarItens("Bebidas", 2, "Coca-Cola", 5);
//        } catch (CategoriaException | ItemException e) {
//            System.out.println(e.getMessage());
//        }
//
//        try {
//            String hospedagemUUID = hospedagemController.createHospedagem(hospedeController.getHospede("123456789"), acomodacaoController.getAcomodacao(1));
//            hospedagemController.addItemConta(hospedagemUUID, catalogoController.getItem(1), 2);
//
//            System.out.println(hospedagemController.getHospedagem(hospedagemUUID).listar());
//        } catch (HospedagemException | HospedeException | AcomodacaoException | CatalogException | ItemException e) {
//            System.out.println(e.getMessage());
//        }

		MainController.save();

	}

}
