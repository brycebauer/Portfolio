
import java.io.IOException;

/**
 *
 * @author Bryce
 */
public class WarshallApp {

    public static void main(String[] args) throws IOException {
        Graph theGraph = new Graph();
        theGraph.addVertex('A'); //0
        theGraph.addVertex('B'); //1
        theGraph.addVertex('C'); //2
        theGraph.addVertex('D'); //3
        theGraph.addVertex('E'); //4


        theGraph.addEdge(0, 2); // edge for AC
        theGraph.addEdge(1, 0); // edge for BA
        theGraph.addEdge(1, 4); // edge for BE
        theGraph.addEdge(3, 4); // edge for DE
        theGraph.addEdge(4, 2); // edge for EC

        System.out.println("Original Adjacency Matrix");
        theGraph.adjMatDisplay(); // display adjacency matrix
        System.out.println();
        theGraph.warshall(); // calls and runs the Warshall Algorithm
        System.out.println();
    }
}
