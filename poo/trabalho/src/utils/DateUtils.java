package utils;

import java.util.Date;

public class DateUtils {
    public static long getIntervaloDias(Date dataInicial, Date dataFinal) {
        long milisegundoPorDia = (24 * 60 * 60 * 1000);
        return (dataFinal.getTime() - dataInicial.getTime()) / milisegundoPorDia;
    }
}
