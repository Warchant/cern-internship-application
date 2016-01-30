import java.io.File;
import java.io.FileNotFoundException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/**
 * @author Bogdan
 *         Innopolis University
 *         1/28/2016
 */
public class Task1 {
    private static final int MAX_THREADS = 4;

    public static void main(String[] args) {

        if (args.length != 1) {
            System.out.println("First argument must be a path to a file specifying set of puzzles.");
            System.exit(1);
        } else {

            Scanner in = null;
            try {
                in = new Scanner(new File(args[0]));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                System.exit(2);
            }

            LinkedList<String> paths = new LinkedList<>();
            while (in.hasNext()) {
                paths.add(in.nextLine());
            }

            ExecutorService pool = Executors.newFixedThreadPool(MAX_THREADS);
            for (String path : paths) {
                pool.execute(new Solver(path));
            }

            pool.shutdown();
        }
    }
}
