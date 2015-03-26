
// hashChain.java
// demonstrates hash table with separate chaining
// to run this program: C:>java HashChainApp
import java.io.*;
import java.util.*;
////////////////////////////////////////////////////////////////
class HashTable {

    private Tree[] hashArray; // array of lists
    private int arraySize;
    // -------------------------------------------------------------

    public HashTable(int size) // constructor
    {
        arraySize = size;
        hashArray = new Tree[arraySize]; // create array
        for (int j = 0; j < arraySize; j++) // fill array
        {
            hashArray[j] = new Tree(); // with lists
        }
    }
    //-------------------------------------------------------------

    public void displayTable() {
        for (int j = 0; j < arraySize; j++) // for each cell,
        {
            System.out.print(j + ". "); // display cell number
            hashArray[j].displayTree(); // display list
        }
    }
    // -------------------------------------------------------------

    public int hashFunc(String key) {
        int hashVal = 0;
        for (int j = 0; j < key.length(); j++) // left to right
        {
            int letter = key.charAt(j) - 96; // get char code
            hashVal = (hashVal * 27 + letter) % arraySize; // mod
        }
        return hashVal; // no mod
    } // end hashFunc()
    // -------------------------------------------------------------

    public void insert(Node node) // insert a link
    {
        String key = node.iData;
        int hashVal = hashFunc(key); // hash the key
        hashArray[hashVal].insert(node); // insert at hashVal
    } // end insert()
    // -------------------------------------------------------------

    public void delete(String key) // delete a link
    {
        int hashVal = hashFunc(key); // hash the key
        hashArray[hashVal].delete(key); // delete link
    } // end delete()
    // -------------------------------------------------------------

    public Node find(String key) // find link
    {
        int hashVal = hashFunc(key); // hash the key
        Node node = hashArray[hashVal].find(key); // get link
        return node; // return link
    }
    // -------------------------------------------------------------
} // end class HashTable
////////////////////////////////////////////////////////////////
class HashChainApp {

    public static void main(String[] args) throws IOException {
        String aKey;
        Node aDataItem, cDataItem;
        boolean run = false;
        String rdmString = "abcdefghijklmnopqrstuvwxyz";
        int size, n, keysPerCell = 100;
        // get sizes
        System.out.print(
                "Enter size of hash table: ");
        size = getInt();
        System.out.print(
                "Enter initial number of items: ");
        n = getInt();
        // make table
        HashTable theHashTable = new HashTable(size);
        for (int j = 0; j < n; j++) // insert data
        {
            aKey = randomString();
            aDataItem = new Node(aKey);
            theHashTable.insert(aDataItem);
        }
        while (run != true) // interact with user
        {
            System.out.print(
                    "Enter first letter of ");
            System.out.print(
                    "show, insert, delete, find, or exit: ");
            char choice = getChar();
            switch (choice) {
                case 's':
                    theHashTable.displayTable();
                    break;
                case 'i':
                    System.out.print("Enter key value to insert: ");
                    aKey = getString();
                    Node check = theHashTable.find(aKey);
                    if (check != null) {
                        System.out.println("Cannot enter in duplicates");
                    } else {
                        aDataItem = new Node(aKey);
                        theHashTable.insert(aDataItem);
                    }
                    break;
                case 'd':
                    System.out.print(
                            "Enter key value to delete: ");
                    aKey = getString();
                    theHashTable.delete(aKey);
                    break;
                case 'f':
                    System.out.print(
                            "Enter key value to find: ");
                    aKey = getString();
                    aDataItem = theHashTable.find(aKey);
                    if (aDataItem != null) {
                        System.out.println("Found " + aKey);
                    } else {
                        System.out.println("Could not find " + aKey);
                    }
                    break;
                case 'e':
                    run = true;
                    System.out.println("Now Exiting");
                    break;
                default:
                    System.out.print("Invalid entry\n");
            } // end switch
        } // end while
    } // end main()
    //--------------------------------------------------------------

    public static String randomString() {
        char[] chars = "abcdefghijklmnopqrstuvwxyz".toCharArray();
        StringBuilder sb = new StringBuilder();
        Random random = new Random();
        int stringSize = random.nextInt(6);
        for (int i = 1; i <= stringSize; i++) {
            char c = chars[random.nextInt(chars.length)];
            sb.append(c);
        }
        String output = sb.toString();
        System.out.println("The random string " + output + " was inserted");
        return output;
    }
    //--------------------------------------------------------------

    public static String getString() throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        String s = br.readLine();
        return s;
    }
    //-------------------------------------------------------------

    public static char getChar() throws IOException {
        String s = getString();
        return s.charAt(0);
    }
    //-------------------------------------------------------------

    public static int getInt() throws IOException {
        String s = getString();
        return Integer.parseInt(s);
    }
    //--------------------------------------------------------------
} // end class HashChainApp
////////////////////////////////////////////////////////////////
class Node {

    public String iData; // data item (key)
    public Node leftChild; // this node's left child
    public Node rightChild; // this node's right child

    Node(String aKey) {
        iData = aKey;
    }

    public void displayNode() // display ourself
    {
        System.out.print('{');
        System.out.print(iData);
        System.out.print("} ");
    }
} // end class Node
////////////////////////////////////////////////////////////////
class Tree {

    private Node root; // first node of tree
    // -------------------------------------------------------------

    public Tree() // constructor
    {
        root = null;
    } // no nodes in tree yet
    //-------------------------------------------------------------

    public Node find(String key) // find node with given key
    { // (assumes non-empty tree)
        Node current = root; // start at root
        while (current.iData.compareTo(key) == -1) // while no match,
        {
            if (key.compareTo(current.iData) == -1) // go left?
            {
                current = current.leftChild;
            } else // or go right?
            {
                current = current.rightChild;
            }
            if (current == null) // if no child,
            {
                return null; // didn't find it
            }
        }
        return current; // found it
    } // end find()
    // -------------------------------------------------------------

    public void insert(String id) {

        Node node = new Node(id); // make new node
        insert(node);
    }

    public void insert(Node node) {
        if (root == null) // no node in root
        {
            root = node;
        } else // root occupied
        {
            Node current = root; // start at root
            Node parent;
            while (true) // (exits internally)
            {
                parent = current;
                if (node.iData.compareTo(current.iData) == -1) // go left?
                {
                    current = current.leftChild;
                    if (current == null) // if end of the line,
                    { // insert on left
                        parent.leftChild = node;
                        return;
                    }
                } // end if go left
                else // or go right?
                {
                    current = current.rightChild;
                    if (current == null) // if end of the line
                    { // insert on right
                        parent.rightChild = node;
                        return;
                    }
                } // end else go right
            } // end while
        } // end else not root
    } // end insert()
    // -------------------------------------------------------------

    public boolean delete(String key) // delete node with given key
    { // (assumes non-empty list)
        Node current = root;
        Node parent = root;
        boolean isLeftChild = true;
        while (current.iData.compareTo(key) == -1) // search for node
        {
            parent = current;
            if (key.compareTo(current.iData) == -1) // go left?
            {
                isLeftChild = true;
                current = current.leftChild;
            } else // or go right?
            {
                isLeftChild = false;
                current = current.rightChild;
            }
            if (current == null) // end of the line,
            {
                return false; // didn't find it
            }
        } // end while
        // found node to delete
        // if no children, simply delete it
        if (current.leftChild == null
                && current.rightChild == null) {
            if (current == root) // if root,
            {
                root = null; // tree is empty
            } else if (isLeftChild) {
                parent.leftChild = null; // disconnect
            } else // from parent
            {
                parent.rightChild = null;
            }
        } // if no right child, replace with left subtree
        else if (current.rightChild == null) {
            if (current == root) {
                root = current.leftChild;
            } else if (isLeftChild) {
                parent.leftChild = current.leftChild;
            } else {
                parent.rightChild = current.leftChild;
            }
        } // if no left child, replace with right subtree
        else if (current.leftChild == null) {
            if (current == root) {
                root = current.rightChild;
            } else if (isLeftChild) {
                parent.leftChild = current.rightChild;
            } else {
                parent.rightChild = current.rightChild;
            }
        } else // two children, so replace with inorder successor
        {
            // get successor of node to delete (current)
            Node successor = getSuccessor(current);
            // connect parent of current to successor instead
            if (current == root) {
                root = successor;
            } else if (isLeftChild) {
                parent.leftChild = successor;
            } else {
                parent.rightChild = successor;
            }
            // connect successor to current's left child
            successor.leftChild = current.leftChild;
        } // end else two children
        // (successor cannot have a left child)
        return true; // success
    } // end delete()
    // -------------------------------------------------------------
    // returns node with next-highest value after delNode
    // goes to right child, then right child's left descendents

    private Node getSuccessor(Node delNode) {
        Node successorParent = delNode;
        Node successor = delNode;
        Node current = delNode.rightChild; // go to right child
        while (current != null) // until no more
        { // left children,
            successorParent = successor;
            successor = current;
            current = current.leftChild; // go to left child
        }
        // if successor not
        if (successor != delNode.rightChild) // right child,
        { // make connections
            successorParent.leftChild = successor.rightChild;
            successor.rightChild = delNode.rightChild;
        }
        return successor;
    }
    // -------------------------------------------------------------

    public void traverse(int traverseType) {
        switch (traverseType) {
            case 1:
                System.out.print("\nPreorder traversal: ");
                preOrder(root);
                break;
            case 2:
                System.out.print("\nInorder traversal: ");
                inOrder(root);
                break;
            case 3:
                System.out.print("\nPostorder traversal: ");
                postOrder(root);
                break;
        }
        System.out.println();
    }
    // -------------------------------------------------------------

    private void preOrder(Node localRoot) {
        if (localRoot != null) {
            System.out.print(localRoot.iData + " ");
            preOrder(localRoot.leftChild);
            preOrder(localRoot.rightChild);
        }
    }
    // -------------------------------------------------------------

    private void inOrder(Node localRoot) {
        if (localRoot != null) {
            inOrder(localRoot.leftChild);
            System.out.print(localRoot.iData + " ");
            inOrder(localRoot.rightChild);
        }
    }
    // -------------------------------------------------------------

    private void postOrder(Node localRoot) {
        if (localRoot != null) {
            postOrder(localRoot.leftChild);
            postOrder(localRoot.rightChild);
            System.out.print(localRoot.iData + " ");
        }
    }
    // -------------------------------------------------------------

    public void displayTree() {
        Stack globalStack = new Stack();
        globalStack.push(root);
        int nBlanks = 32;
        boolean isRowEmpty = false;
        System.out.println(
                "......................................................");
        while (isRowEmpty == false) {
            Stack localStack = new Stack();
            isRowEmpty = true;
            for (int j = 0; j < nBlanks; j++) {
                System.out.print(' ');
            }
            while (globalStack.isEmpty() == false) {
                Node temp = (Node) globalStack.pop();
                if (temp != null) {
                    System.out.print(temp.iData);
                    localStack.push(temp.leftChild);
                    localStack.push(temp.rightChild);
                    if (temp.leftChild != null
                            || temp.rightChild != null) {
                        isRowEmpty = false;
                    }
                } else {
                    System.out.print("--");
                    localStack.push(null);
                    localStack.push(null);
                }
                for (int j = 0; j < nBlanks * 2 - 2; j++) {
                    System.out.print(' ');
                }
            } // end while globalStack not empty
            System.out.println();
            nBlanks /= 2;
            while (localStack.isEmpty() == false) {
                globalStack.push(localStack.pop());
            }
        } // end while isRowEmpty is false
        System.out.println(
                "......................................................");
    } // end displayTree()
    // -------------------------------------------------------------
} // end class Tree
////////////////////////////////////////////////////////////////

