package enums;

public enum ETipoPagamento {
	PIX("Pagamento via PIX"), DEBITO("Pagamento via Debito"), CREDITO("Pagamento via Credito");

	private final String descricao;

	private ETipoPagamento(String descricao) {
		this.descricao = descricao;
	}

	public String getDescricao() {
		return descricao;
	}

}
