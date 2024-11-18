import java.util.Scanner;
import java.util.Random;

public class Main {
    public static void jv_print_board(char[][] jogo) {
        for (int i = 0; i < 3; i++) {
            System.out.print("|");
            for (int j = 0; j < 3; j++) {
                System.out.print(jogo[i][j] + "|");
            }
            System.out.print("\n-------\n");
        }
    }

    public static void jogo_da_velha() {
        char[][] board = new char[3][3];
        int x = 0, y = 0;

        Scanner sc = new Scanner(System.in);
        Random rand = new Random();

        jv_print_board(board);

        int starter = rand.nextInt(2);

        if (starter == 0) {
            System.out.println("Escolha uma posição!");
        } else {
            x = rand.nextInt(3);
            y = rand.nextInt(3);
        }

    }

    public static void main(String[] args) {
        jogo_da_velha();
    }
}