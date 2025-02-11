package exception;

public class CategoriaException extends Exception {

	private static final long serialVersionUID = 4097189256828787181L;

	public CategoriaException(String message) {
		super("Exceção de categoria " + message);
	}
}
