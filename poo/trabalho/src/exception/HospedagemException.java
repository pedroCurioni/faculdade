package exception;

public class HospedagemException extends Exception {

	private static final long serialVersionUID = 3084518949399317039L;

	public HospedagemException(String message) {
		super("Exceção de hospedagem " + message);
	}

}
