package exception;

public class ContaException extends Exception {

	private static final long serialVersionUID = -9205750072440439408L;

	public ContaException(String message) {
		super("Exceção de cconta " + message);
	}

}
