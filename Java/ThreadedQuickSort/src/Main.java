
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author Bryce
 */
public class Main {

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);

        System.out.print("Enter the size of the array to be sorted: ");
        int numberOfElements = keyboard.nextInt();
        int[] crazy = new int[numberOfElements];
        System.out.println();

        Random randomInt = new Random(1393);

        for (int i = 0; i < numberOfElements; i++) {
            crazy[i] = randomInt.nextInt(numberOfElements);
        }
        //this will partition the whole array into two parts
        QuickSortThreaded thread1 = new QuickSortThreaded(crazy, 0, (numberOfElements / 2 - 1), 1);
        QuickSortThreaded thread2 = new QuickSortThreaded(crazy, (numberOfElements / 2), numberOfElements, 2);

        thread1.start();
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            //ignore
        }

    }
}
