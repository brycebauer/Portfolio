/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.Scanner;

/**
 *
 * @author bryce.bauer
 */
public class Patient extends WaitingRoom {

    private int id;  //this is the id number of the patient
    private int priority;    //priority number for the patients case

    public Patient(int in_id, int in_priority) {
        id = in_id;
        priority = in_priority;
    }

    public static Patient whatPriority() {
        int choice, id, priority;
        boolean done = false;
        Scanner in = new Scanner(System.in);
        while (!done) {
            System.out.println();
            System.out.println("Enter in the priority of the patient: 1 -high priority, 2 -medium priority, 3 -low priority, 4 -no priority");
            choice = in.nextInt();
            System.out.println();
            System.out.println("Enter in Patient's ID number: ");
            id = in.nextInt();
            System.out.println("Reenter the Patient's priority number: ");
            priority = in.nextInt();
            if (priority != choice) {
                System.out.println("The priority number do not match.");
            } else if (priority < 1 || priority > 4) {
                System.out.println("This is not a valid proiority number");
            } else {
                return new Patient(id, priority);
            }

        }
        return (null);
    }

    public int getPriority() {
        return priority;
    }

    public int getID() {
        return id;
    }
}
