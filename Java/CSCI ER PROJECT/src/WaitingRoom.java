
import java.util.Scanner;

/**
 * Bryce Bauer CSCI 132 Out Lab 1: Emergency Room problem 1/25/2012
 */
public class WaitingRoom {

    static int choice;
    static Boolean done = false;
    static Scanner keyboard = new Scanner(System.in);
    static Queue quack = new Queue();

    static NewQuack[] newQuack = new NewQuack[4];

    static Room er = new Room();
    static boolean status = false;

    public static void main(String[] args) {
        
        for (int i = 0; i < 4; i++){
            newQuack[i] = new NewQuack();
        }


        // This while loop continuously executes a loop that allows the user to test class Stack1.
        // It is an example of how a class can be tested prior to its use in a real program.
        while (!done) {
            // Each time the loop starts, the user is presented with a menu with items for exercising
            // each method of clsss Stack1, in this case, push and pop. There is also a menu item for
            // terminating the loop.
            System.out.print("Enter 1 to create new patient, 2 to release patient from ER room, 3 to print status, 4 to turn status off, 5 to see who is in the ER room, 6 to print the linked list, 7 to quit: ");
            choice = keyboard.nextInt();
            System.out.println();

            //This switch statement selects the proper case for the menu choice made by the user.
            switch (choice) {
                case 1: // Create new patient in the Emergency Room
                    Patient patient = Patient.whatPriority();
                    if (er.isFull()) {
                        if (patient.getPriority() > er.getPriority()) {
                            newQuack[patient.getPriority() - 1].enqueue(patient);
                        } else if (patient.getPriority() == er.getPriority()) {
                            newQuack[patient.getPriority() - 1].enqueue(patient);
                        } else {
                            newQuack[patient.getPriority()- 1].push(er.move(patient));
                            System.out.println("The patient in the er has been moved because a higher priority patient came in.");
                            er.next(patient);
                        }
                    } else {
                        er.next(patient);
                    }
                    if (status) {
                        printStatus();
                    }
                    System.out.println();
                    break;
                case 2: // Release patient from emergency room
                    er.pop();
                    System.out.println();
                    if (er.isEmpty()) {
                        if (newQuack[0].hasPatient()) {
                            er.next(newQuack[0].pop());
//                        } else if (quack.hasPatient()) {
//                            er.next(quack.dequeue());
                        } else if (newQuack[1].hasPatient()) {
                            er.next(newQuack[1].pop());
                        } else if (newQuack[2].hasPatient()) {
                            er.next(newQuack[2].pop());
                        } else if (newQuack[3].hasPatient()) {
                            er.next(newQuack[3].pop());
                        } else {
                            System.out.println("All patients have been treated.");
                        }
                    }

                    if (status) {
                        printStatus();
                    }
                    break;
                case 3: // Turns print status on
                    status = true;
                    System.out.println("The status of the Er and waiting rooms will be printed");
                    break;
                case 4: // Turns print status off
                    status = false;
                    System.out.println("Status turned off");
                    break;
                case 5: // Set done to true so that the loop will end
                    System.out.println("the ER room is occupied by patient " + er.getId() + " with a priority of " + er.getPriority());
                    break;
                case 6:
                    NewQuack.print();
                    break;
                case 7:
                    done = true;
                    System.out.println("...quitting");
                    break;
                default:
                    // This default clause handles the case that the user has typed in an integer
                    // that is not one of the valid choices
                    System.out.println("The number you entered (" + choice + ") is not 1-7. Try again!");
                    System.out.println();
                    break;
            }
        }
    }

    public static void printStatus() {
        int total = 0;
        for (int i = 0; i < 4; i++) {
            total += newQuack[i].getNum();
        }
        total = (total + quack.getNum());
        if (er.isFull()) {
            System.out.println("The room is full and there are " + total + " patients waiting in the waiting room");
        } else {
            System.out.println("The room is not full and there are " + total + " patients waiting in the waiting room");
        }
        System.out.println("There was " + quack.getNum() + " patient(s) that were moved for a higher priority patient.");
    }
}
