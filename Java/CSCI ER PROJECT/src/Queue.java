/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author bryce.bauer
 */
public class Queue {

    private int top, bottom;
    private Patient[] queue = new Patient[100];
    private Patient waiting;
    int counter;
    // constructor for Stack

    public Queue() {
        top = 0;
        bottom = 0;
    }

    public void enqueue(Patient n) {
        if (isFull()) {
            System.out.println("Queue is full");
        } else {

            // assert top points to the first free element on top of the stack
            queue[bottom] = n;
            // assert pushValue is on top of stack and top points to the pushValue
            bottom = (bottom + 1) % 100;
            // assert top points to the first free element on top of the stack
            counter++;
        }
    }

    public Patient dequeue() {
        if (isEmpty()) {
            System.out.println();
            return null;
        } else {
            Patient x = queue[top];
            queue[top] = null;
            top = (top + 1) % 100;
            counter--;
            return x;
        }
    }

    public int getNum() {
        return counter;
    }

    public boolean isEmpty() {
        if (top == bottom) {
            return true;
        } else {
            return false;
        }
    }

    public boolean hasPatient() {
        if (counter == 0) {
            return false;
        } else {
            return true;
        }
    }

    public boolean isFull() {
        if ((bottom + 1) % 100 == top) {
            return true;
        } else {
            return false;
        }
    }
}
