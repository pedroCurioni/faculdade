package exception;

public class ItemException extends Exception {

	private static final long serialVersionUID = 3485885197977634267L;

	public ItemException(String message) {
		super("Exceção de item " + message);
	}

}
