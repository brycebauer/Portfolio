
/**
 * Bryce Bauer CSCI 132 Out Lab 1: Emergency Room Problem 1/25/2012
 */
public class Room extends WaitingRoom {
    // instance varialbles

    private int pushValue;
    private Patient[] room = new Patient[1];
    private Patient serving;
    private boolean isFull,
            isEmpty;

    // constructor for Stack
    public Room() {
    }

    public void next(Patient pushValue) {
        if (isFull()) {
            System.out.println("Too many patients in room");
            System.out.println();
        } else {
            serving = pushValue;
        }
    }

    public Patient move(Patient moveValue) {
        if (isEmpty()) {
            System.out.println("There is no one to move");
        } else {
            moveValue = serving;
            serving = null;
        }
        return moveValue;
    }

    public Patient pop() {
        if (isEmpty()) {
            System.out.println();
            return null;
        } else {
            System.out.println("The patient " + serving.getID() + " with a priority " + serving.getPriority() + " is released.");
            Patient x = serving;
            serving = null;
            return x;
        }
    }

    public int getPriority() {
        return serving.getPriority();
    }

    public int getId() {
        return serving.getID();
    }

    public boolean isEmpty() {
        if (serving == null) {
            return true;
        } else {
            return false;
        }
    }

    public boolean isFull() {
        if (serving != null) {
            return true;
        } else {
            return false;
        }
    }
}