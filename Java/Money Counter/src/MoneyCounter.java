
import java.util.Scanner;

public class MoneyCounter {

    private static int numPennies;      //variable for number of pennies
    private static int numNickels;      //variable for number of nickles
    private static int numDimes;        //variable for number of dimes
    private static int numQuarters;     //variable for number of quarters
    private static int numOnes;         //variable for number of one dollar bills
    private static int numFives;        //variable for number of five dollar bills
    private static int numTens;         //variable for number of ten dollar bills
    private static int numTwenties;     //variable for number of twenty dollar bills
    private static float totMoney;      //variable for total amount of money
    private static float temp;          //temporary variable for the total value of coins or bill (value will change every time)    

    public static void main(String[] args) {
        totMoney = 0;
        int x = 1;
        System.out.println("Welcome to the Money Counter Program!");
        while (x != 0) {
            System.out.format("\nYou have $%6.2f\n", totMoney);
            System.out.println("Enter: 1 to count coins, 2 to count bills, 3 to reset total money, 4 to quit,");
            Scanner keyboard = new Scanner(System.in);
            int input = keyboard.nextInt();

            switch (input) {
                case 1:
                    countCoins();
                    break;
                case 2:
                    countBills();
                    break;
                case 3:
                    totMoney = 0;
                    break;
                case 4:
                    x = 0;
                    break;
                default:
                    System.out.println("ERROR you entered in the wrong number. Try Again!!!!!!!");

            }
        }

    }

    public static void countCoins() {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter: 1 to count pennies, 2 to count nickels, 3 to count dimes, 4 to count quarters");
        int input = keyboard.nextInt();
        switch (input) {
            case 1:
                System.out.println("How many pennies do you have?");
                numPennies = keyboard.nextInt();
                temp = ((float) numPennies / 100);
                totMoney += temp;
                break;
            case 2:
                System.out.println("How many nickels do you have?");
                numNickels = keyboard.nextInt();
                temp = ((float) numNickels / 20);
                totMoney += temp;
                break;
            case 3:
                System.out.println("How many dimes do you have?");
                numDimes = keyboard.nextInt();
                temp = ((float) numDimes / 10);
                totMoney += temp;
                break;
            case 4:
                System.out.println("How many quarters do you have?");
                numQuarters = keyboard.nextInt();
                temp = ((float) numQuarters / 4);
                totMoney += temp;
                break;
            default:
                System.out.println("You entered in the wrong value. try again");
        }
    }

    public static void countBills() {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter 1 to count one dollar bills, 2 to count five dollar bills, 3 to count dollar bills, 4 to count twenty dollar bills");
        int input = keyboard.nextInt();
        switch (input) {
            case 1:
                System.out.println("how many ones do you have?");
                numOnes = keyboard.nextInt();
                temp = ((float) numOnes * 1);
                totMoney += temp;
                break;
            case 2:
                System.out.println("How many fives do you have?");
                numFives = keyboard.nextInt();
                temp = ((float) numFives * 5);
                totMoney += temp;
                break;
            case 3:
                System.out.println("How many tens do you have?");
                numTens = keyboard.nextInt();
                temp = ((float) numTens * 10);
                totMoney += temp;
                break;
            case 4:
                System.out.println("How many twenties do you have?");
                numTwenties = keyboard.nextInt();
                temp = ((float) numTwenties * 20);
                totMoney += temp;
                break;
            default:
                System.out.println("You entered in an invalid number try again");
        }
    }
}