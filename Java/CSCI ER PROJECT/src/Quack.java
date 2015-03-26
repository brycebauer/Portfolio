/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * Bryce Bauer CSCI 132, InLab4 2/8/2012
 */
public class Quack {

// This is an array implementation of a queue and a stack put together of integer values
    // instance variables
    int queueSize = 0;
    Patient[] queue = new Patient[100];
    int front = 0;
    int back = 0;
    Boolean empty = true;
    Boolean full = false;

    public void enqueue(Patient enqueueValue) {
        // ASSERT Precondition: (1) If enqueue is called, the queue is not full. (This must be checked by the
        //        calling method by first calling method isFull in this class and not calling enqueue if
        //        the queue is full. Errors will occur otherwise.) (2) queueSize contains the number of 
        //        elements in the queue. (3) back points to the first free element at the back of the qeuue.
        queue[back] = enqueueValue;
        // ASSERT back now points to the last element in the queue, and queueSize contains one less than
        // the number of elements in the queue.
        back = (back + 1) % 100;
        // ASSERT back now points to the first free element at the end of the queue, unless the
        //        queue is full, in which case it points to the first element of the queue. That is,
        //        the queue has wrapped around and is now full.
        //        However, enqueue will not be called if the queue is full until a dequeue is first
        //        called, resulting in back pointing as it should to the first free element at the end
        //        of the queue. And queueSize contains one less than the number of elelments in the queue.
        queueSize++;
        // ASSERT Postcondition: (1) The enqueueValue has been place at the end of the queue
        //        (2) back points to the first free element of the queue.
        //        (3) queueSize contains the number of elements in the queue.           
    }

    public void push(Patient pushValue) //this method turns the queue in to a quack because we are saying that we can push a value to the front of the queue
    {
        front = (front + 99) % 100;  // another way to write (front -1) % 100
        queue[front] = pushValue;
        queueSize++;
    }

    public Patient dequeue() {
        // ASSERT Precondition: (1) If dequeue is called, the queue is not empty. (This must be checked by the
        //        calling method by first calling method isEmpty in this class and not calling dequeue if
        //        the queue is empty. Errors will occur otherwise.) (2) queueSize contains the number of 
        //        elements in the queue. (3) front points to the frontmost element in the queue.
        Patient dequeueValue = queue[front];
        queue[front] = null;
        // ASSERT firstElement contains the first element of the queue, queueSize is one larger than the
        //        number of elements in the queue (since one was removed), and front points to the now-empty
        //        position in the queue of the element just removed (i.e., to the element just in front of
        //        the queue as it now stands.
        front = (front + 1) % 100;
        // ASSERT front now points to the frontmost element of the queue.
        queueSize--;
        // ASSERT queueSize now contains the number of elements in the queue.
        // ASSERT Postcondition: (1) The first value in the queue has been removed and returned to the caller.
        //        (2) front points to the frontmost element of the queue.
        //        (3) queueSize contains the number of elements in the queue. 
        return dequeueValue;
    }

    public Boolean isEmpty() {
        if (queueSize == 0) {
            return true;
        } else {
            return false;
        }
    }

    public Boolean isFull() {
        if (queueSize == 100) {
            return true;
        } else {
            return false;
        }
    }

    public Boolean hasPatient() {
        if (queueSize == 0) {
            return false;
        } else {
            return true;
        }
    }

    public int getNum() {
        return queueSize;
    }
}
