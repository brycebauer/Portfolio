/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Bryce
 */
class Graph {

    private final int max_verts = 31;
    private int vertcounter = 0;
    private Vertex vertexList[]; // array for the verticies
    private int adjMat[][];      // 2D array for the adjacency matrix
    private int nVerts;          // current number of verticies

    public Graph() { // constructor for the graph class
        vertexList = new Vertex[max_verts];
        adjMat = new int[max_verts][max_verts];
        nVerts = 0;
        for (int j = 0; j < max_verts; j++) {
            for (int k = 0; k < max_verts; k++) {
                adjMat[j][k] = 0;
            }
        }
    }

    public void addVertex(char theLabel) {
        vertexList[nVerts++] = new Vertex(theLabel);
        vertcounter++;
    }

    public void addEdge(int start, int end) {
        if (start < 0 || start > (max_verts-1) || end < 0 || end > (max_verts - 1)){
            System.out.println("Invalid entry!!!!");
            System.out.println("You have entered in an edge that exceeds the minimum or mazimum");
    }
        else
        adjMat[start][end] = 1;
    }

    public void adjMatDisplay() {  //displays the adjacency matrix with testing for if an edge is added that is out of the array bounds
        int loopcounter = 0;
        for (int a = 0; a < vertcounter; a++) {
            System.out.print("  " + vertexList[a].label + " ");
            loopcounter++;

        }
        System.out.println();
        for (int k = 0; k < vertcounter; k++) {
            System.out.print(vertexList[k].label);
            for (int i = 0; i < loopcounter; i++) {

                System.out.print(" " + adjMat[k][i] + "  ");

            }
            System.out.println();
        }

    }

    public void warshall() {   //runs the Floyd-Warshall Algorithm
        for (int i = 0; i < max_verts; i++) {
            for (int j = 0; j < max_verts; j++) {
                if (adjMat[i][j] == 1) {
                    for (int k = 0; k < max_verts; k++) {
                        if (adjMat[k][i] == 1) {
                            adjMat[k][j] = 1;
                        }
                    }
                }
            }
        }
        System.out.println("Transitive Closure");  //
        adjMatDisplay();
    }
}

class Vertex {
    public char label; // label for the vertex like vertex A
    public boolean wasVisited; // will let program know if vertex was visited
    
    public Vertex(char theLabel){  // Construtor for the Vertecies
        label = theLabel;
        wasVisited = false;
    }
}
