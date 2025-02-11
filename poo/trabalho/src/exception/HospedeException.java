package exception;

public class HospedeException extends Exception {

	private static final long serialVersionUID = -2584806486139400241L;

	public HospedeException(String message) {
		super("Exceção de hospede " + message);
	}
}
