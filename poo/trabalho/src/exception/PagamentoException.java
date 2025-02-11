package exception;

public class PagamentoException extends Exception {

	private static final long serialVersionUID = 4175407502064560790L;

	public PagamentoException(String message) {
		super("Exceção de pagamento " + message);
	}
}
