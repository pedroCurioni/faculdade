public class Funcionario extends Pessoa{
    private int matricula;
    private boolean disponivel;

    public Funcionario(long cpf, String nome, long telefone, String email, int matricula, boolean disponivel) {
        super(cpf, nome, telefone, email);
        this.matricula = matricula;
        this.disponivel = disponivel;
    }
}
