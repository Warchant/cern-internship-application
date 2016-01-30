import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * @author Bogdan
 *         Innopolis University
 *         1/28/2016
 */
public class Solver extends Thread {
    private String path;
    private int[] field;
    private double time;

    public boolean isSolvable() {
        for (int i = 0; i < 81; i++)
            if (this.field[i] == 0)
                return false;

        return true;
    }

    public int[][] getSolution() {
        if (!isSolvable()) return null;

        int[][] solution = new int[9][9];
        for (int i = 0; i < 81; i++) {
            int col = i % 9;
            int row = i / 9;

            solution[row][col] = field[i];
        }
        return solution;
    }

    static {
        System.loadLibrary("Solver");
    }

    native private int[] solve(int[] field);

    public static int[] parseField(String path) throws FileNotFoundException, NoSuchElementException {
        Scanner in = new Scanner(new File(path));

        in.useDelimiter("[\n ]+");

        int[] field = new int[9 * 9];
        for (int i = 0; i < 81; i++) {
            String token = in.next();
            try {
                field[i] = Integer.parseInt(token);
            } catch (NumberFormatException e) {
                field[i] = 0;
            }
        }

        return field;
    }

    public Solver(String path) {
        this.path = path;
    }

    @Override
    public void run() {
        long start = System.nanoTime();
        try {
            this.field = parseField(this.path);
            this.field = solve(field);
        } catch (Exception e) {
            System.err.println(e.getMessage());
            return;
        }
        time = (System.nanoTime() - start) / 1e9;

        int[][] solution = getSolution();
        if (solution != null) {
            System.out.println("Solution for: " + path + ", finished in " + time + " seconds.");

            PrintWriter pw = null;
            try {
                pw = new PrintWriter(path + "-solved.txt");
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        pw.print(solution[i][j] + " ");
                    }
                    pw.println();
                }
                pw.close();
            } catch (FileNotFoundException e) {
                System.err.println(e.getMessage());
                return;
            }
        } else {
            System.out.println("There is no solution for: " + path);
        }
    }
}
