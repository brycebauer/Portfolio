
import java.util.Random;
import java.util.Scanner;
/*
 * Bryce Bauer CSCI 132 OutLab 5
 */

public class BubbleSort {

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        Random generator = new Random(314159);

        // Populate an array of the desired size with uniformly distributed 
        // random numbers
        System.out.print("Enter the number of droids you want to create: ");
        int listSize = keyboard.nextInt();
        Droid[] list = new Droid[listSize];
        int i = 0;
        int j = 1;
        while (i < listSize) {
            list[i] = new Droid();
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
        boolean exchanges = false;
        do {
            exchanges = true;
            for (j = 0; j < listSize; j++) {
                for (i = 0; i < listSize; i++) {
                    if (list[i].getId() > list[j].getId()) {
                        Droid temp = list[j];
                        list[j] = list[i];
                        list[i] = temp;
                    }
                }
                exchanges = false;
            }
        } while (exchanges);


        // Print the number of statements executed for use in run time complexity
        // analysis
        System.out.println();

        for (i = 0; i <= listSize - 1; i++) {
            System.out.print(list[i].getId() + " ");
        }

        System.out.println();
        // Print the array to be sure it is sorted
        System.out.println("Here are the sorted droids you wanted:");
        for (i = 0; i <= listSize - 1; i++) {
            System.out.print(list[i].getName() + " ");
        }
        System.out.println();
    }
}
