package utils;

import java.util.regex.Pattern;

public class ValidationUtils {
    private static final Pattern EMAIL_PATTERN = Pattern.compile("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$");
    public static final Pattern PHONE_PATTERN = Pattern.compile("^\\d{10,11}$");
    public static final Pattern CPF_PATTERN = Pattern.compile("\\d{11}");

    public static boolean isValidEmail(String email) {
        return EMAIL_PATTERN.matcher(email).matches();
    }

    public static boolean isValidPhone(String phone) {
        return PHONE_PATTERN.matcher(phone).matches();
    }

    public static int calcularDigito(String cpf, int[] pesos) {
        int soma = 0;
        for (int i = 0; i < pesos.length; i++) {
            soma += (cpf.charAt(i) - '0') * pesos[i];
        }
        int resto = soma % 11;
        return (resto < 2) ? 0 : (11 - resto);
    }

    public static String calcularDigitosVerificadores(String cpf) {
        int[] pesosPrimeiro = {10, 9, 8, 7, 6, 5, 4, 3, 2};
        int primeiroDigito = calcularDigito(cpf, pesosPrimeiro);

        int[] pesosSegundo = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
        int segundoDigito = calcularDigito(cpf + primeiroDigito, pesosSegundo);

        return primeiroDigito + "" + segundoDigito;
    }

    public static boolean isValidCpf(String cpf) {
        if (!CPF_PATTERN.matcher(cpf).matches()) {
            return false;
        }
        String cpfBase = cpf.substring(0, 9);
        String digitosVerificadoresCalculados = calcularDigitosVerificadores(cpfBase);
        String digitosVerificadoresOriginais = cpf.substring(9);
        return digitosVerificadoresCalculados.equals(digitosVerificadoresOriginais);
    }

}
