
import java.util.Random;
import java.util.Scanner;
/*
 * Bryce Bauer CSCI 132 OutLab 5
 */

public class InsertionSort {

    public static void main(String[] args) {
        int i = 0;
        int j;
        Boolean done = false;
        Scanner keyboard = new Scanner(System.in);
        Random generator = new Random(314159);

        // Populate an array of the desired size with uniformly distributed 
        // random numbers
        System.out.print("Enter the number of droids to be created: ");
        int listSize = keyboard.nextInt();
        Droid2[] list = new Droid2[listSize];
        while (i < listSize) {
            list[i] = new Droid2();
            list[i].setId(generator.nextInt());
            list[i].setName("R2D" + i);
            i++;
        }

        // Print the randomly generated random numbers for inspection
        System.out.println();
        for (i = 0; i < listSize; i++) {
            System.out.print(list[i].getId() + " ");
        }
        System.out.println();

        // Sort the array with the course version of selection sort.
        // Include instrumentation for counting the number of statements executed
        int n = listSize;
        for (i = 1; i < n; i++) {
            j = i;
            Droid2 temp = list[i];
            while ((j > 0) && (list[j - 1].getId() > temp.getId())) {
                list[j] = list[j - 1];
                j--;
            }
            list[j] = temp;
        }
        // Print the number of statements executed for use in run time complexity
        // analysis

        // Print the array to be sure it is sorted
        System.out.println("Here are the sorted droids you wanted:");
        for (i = 0; i < listSize; i++) {
            System.out.print(list[i].getName() + " ");
        }
        System.out.println();

    }
}
