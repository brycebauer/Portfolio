import java.io.*;
// Bryce.Bauer
// CSCI 232 Lab 2
// Implementing Huffman Code

public class HuffmanApp {
	static String str;
	public static void main(String[] args) throws IOException {
		System.out.println("Welcome to the Huffman Code App");
		int run = 0;
		str = getText();
		Huffman huff = new Huffman(str);
		while (run != 1) {

			System.out.println("Enter first letter of show, code, decode, or type x to exit:");
			int choice = getChar();
			switch (choice) {
			case 's':
				huff.displayHuffTree();
				System.out.println(str);
				break;
			case 'c':
				huff.encodeMsg();
				break;
			case 'd':
				huff.decode();
				break;
			case 'x':
				System.out.println("Now Exiting");
				run = 1;
				break;
			default:
				System.out.println("Invalid entry\n");
			}

		}

	}

	public static String getText() throws IOException {
		System.out.println("Enter your message and push enter when done:");
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);
		str = br.readLine();
		return str;
	}

	public static char getChar() throws IOException {
		str = getString();
		return str.charAt(0);
	}

	public static String getString() throws IOException {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);
		str = br.readLine();
		return str;
	}

}
