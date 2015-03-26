import java.util.Stack;
import java.util.*;

// Bryce.Bauer
// CSCI 232 Lab 2
// Implementing Huffman Code

public class Huffman {

	static String inputStr; // this is for the input string
	static int freqTable[]; // this is an array of the frequency of the alphabet
							// in the message
	Tree huffTree; // this is the Huffman tree
	static int alphaSize = 28;
	static String codedMsg; // this is the string for the coded message
	static String decodedMsg;
	PriorityQ theQ; // this is a priority queue for the frequency of letters in
					// message
	String codeTable[]; // array for the code of each character in the message
	Huffman(String str) {
		inputStr = str;
		theQ = new PriorityQ(alphaSize);
		makeFreqTable();
		queueTrees();
		makeHuffTree();
		displayHuffTree();
		huffTree = null;
	}

	public static void makeFreqTable(){
		for (int j=0; j<inputStr.length(); j++){
			Node.letter = inputStr.charAt(j);
			for (int i=0; i<alphaSize; i++){
			freqTable[i]=i;			
		}
			int index = (int) inputStr.charAt(j)- 97;
			freqTable[index]++;
		}
	}

	public void queueTrees() {
		for (int j = 0; j < alphaSize; j++) {
			Node aNode = new Node((char) (j + 97), Node.freq);
			Tree aTree = new Tree();
			theQ.insert(aTree);
		}
	}

	public void makeHuffTree() {
		while (theQ.getSize() > 1) {
			Tree treeLeft = theQ.remove();
			Tree treeRight = theQ.remove();
			int TempFreq = treeLeft.root.freq + treeRight.root.freq;
		}
	}

	public void displayHuffTree() {
		 Stack globalStack = new Stack();
	      globalStack.push(Tree.root);
	      int nBlanks = 32;
	      boolean isRowEmpty = false;
	      System.out.println(
	      "......................................................");
	      while(isRowEmpty==false)
	         {
	         Stack localStack = new Stack();
	         isRowEmpty = true;

	         for(int j=0; j<nBlanks; j++)
	            System.out.print(' ');

	         while(globalStack.isEmpty()==false)
	            {
	            Node temp = (Node)globalStack.pop();
	            if(temp != null)
	               {
	               temp.displayNode();
	               localStack.push(temp.leftChild);
	               localStack.push(temp.rightChild);

	               if(temp.leftChild != null ||
	                                   temp.rightChild != null)
	                  isRowEmpty = false;
	               }
	            else
	               {
	               System.out.print("---");
	               localStack.push(null);
	               localStack.push(null);
	               }
	            for(int j=0; j<nBlanks*2-3; j++)
	               System.out.print(' ');
	            }  // end while globalStack not empty
	         System.out.println();
	         nBlanks /= 2;
	         while(localStack.isEmpty()==false)
	            globalStack.push( localStack.pop() );
	         }  // end while isRowEmpty is false
	      System.out.println(
	      "......................................................");
	      }  // end displayTree()

	}

	public void makeCodeTable(Node nd, String bc){
		if (nd.ch =='+'){
			makeCodeTable(nd.leftChild, bc +"0");
			makeCodeTable(nd.rightChild, bc +"1");
		}
		else{
			codeTable[index] = 
		}
	}

	public void encodeMsg(){
		makeCodeTable(huffTree.root, "");
		for (int j = 0; j < capsString.length(); j++) {
			int index =  ; 
			codedMsg = codedMsg + codeTable[index];
		}
		System.out.println(codedMsg);
	}

	public void decode(){
		while(aNode.ch ='+'){
			if(codedMsg.charAt(j++)=='0');
				theNode= theNode.leftChild;
				decodedMsg = decodedMsg + theNode.ch;
			else
				theNode= theNode.rightChild;
			decodedMsg = decodedMsg + theNode.ch;
		}
	}
}
