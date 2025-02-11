package exception;

public class ItemContaException extends Exception {
	private static final long serialVersionUID = 1374081667441241055L;

	public ItemContaException(String message) {
		super("Exceção de item Conta " + message);
	}
}
