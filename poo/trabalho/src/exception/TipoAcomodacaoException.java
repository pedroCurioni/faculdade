package exception;

public class TipoAcomodacaoException extends Exception {
	private static final long serialVersionUID = 3084518949399317039L;

	public TipoAcomodacaoException(String message) {
		super("Exceção de tipo de acomodação " + message);
	}

}
