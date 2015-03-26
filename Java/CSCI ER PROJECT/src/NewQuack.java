
class NewQuack {

    // StackNode is a private static  subclass contained in class 
    // StackLinked. "Private" means that this class is only visible inside
    // class StackLinked. This is purposefully done, because class
    // StackLinked manages a linked list of StackNode objects, and only
    // StackLinked needs to be aware of the type of nodes (StackNodes)
    // that it uses for the linked list.
    // This is a common approach for managing linked lists of all types.
    // The objective of a linked list is to hold objects of some type in
    // a flexible linked data structure. Thus, the nodes in the linked
    // structure must have (pointers to) objects of the type being stored
    // plus a link (pointer to) other nodes. Thus a node is made up of
    // a (pointer to) an object and one or more added fields that are
    // serve as pointers to other nodes of this type. This is what class
    // StackNode does. It consists of a Patient object pointer variable
    // called "patient" and one more variable called "nextNode" that can
    // point to other StackNodes.
    private static class StackNode {
        //instance variables

        Patient patient;
        StackNode nextNode;

        // Constructor for objects of class StackNode
        StackNode(Patient newPatient) {
            patient = newPatient;
        }
    }
    // Instance variable for class StackLinked
    static StackNode top = null;
    StackNode back = null;
    int numPatients = 0;

    public void push(Patient newPatient) {
        StackNode newNode = new StackNode(newPatient);
        if (top == null) {
            top = newNode;
            newNode.nextNode = null;
            back = top;
        } else {
            newNode.nextNode = top;
            top = newNode;
            //newNode.nextNode = null;
        }
        numPatients++;
    }

    public Patient pop() {
        Patient returnedPatient;
        // ASSERT top points to the first free element on top of the stack
        returnedPatient = top.patient;
        top = top.nextNode;
        numPatients--;
        return (returnedPatient);
    }

    public void enqueue(Patient newPatient) {
        StackNode newNode = new StackNode(newPatient);
        if (top == null) {
            top = newNode;
            newNode.nextNode = null;
            back = top;
        } else {
            back.nextNode = newNode;
            back = newNode;
           // newNode.nextNode = null;
        }
        /* if (back == null) {
        back = newNode;
        back.nextNode = null;
        } else
        newNode.nextNode = back;
        back = newNode;*/

        numPatients++;
    }

    public Boolean isEmpty() {
        if (top == null && back == null) {
            return true;
        } else {
            return false;
        }
    }

    public Boolean hasPatient() {
        if (top != null) {
            return true;
        } else {
            return false;
        }
    }

    public int getNum() {
        return numPatients;
    }

    public static void print() {
        if (top == null) {
            System.out.println("The stack is empty!");
            System.out.println();
        } else {
            StackNode temp = top;
            System.out.println("Current stack contents");
            System.out.println("    id priority");
            System.out.println();
            while (temp != null) {
                System.out.println("     " + temp.patient.getID() + " "
                        + temp.patient.getPriority());
                temp = temp.nextNode;
            }
            System.out.println();
        }
    }
}