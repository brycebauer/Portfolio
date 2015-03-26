
import java.util.*;

/*
 * To change this template, choose Tools | Templates and open the template in
 * the editor.
 */
/**
 *
 * @author Bryce
 */
class dfs {

    private static Map<Integer, LinkedHashSet<Integer>> map = new HashMap<Integer, LinkedHashSet<Integer>>();
    private int startNode;
    private int numLinks;

    public dfs(int startNode, int numLinks) {
        super();
        this.startNode = startNode;
        this.numLinks = numLinks;
    }

    public void addEdge(int source, int destiny) {
        LinkedHashSet<Integer> adjacente = map.get(source);
        if (adjacente == null) {
            adjacente = new LinkedHashSet<Integer>();
            map.put(source, adjacente);
        }
        adjacente.add(destiny);
    }

    public void addLink(int source, int destiny) {
        addEdge(source, destiny);
        addEdge(destiny, source);
    }

    public LinkedList<Integer> adjacentNodes(int last) {
        LinkedHashSet<Integer> adjacente = map.get(last);
        System.out.println("adjacentes:" + adjacente);
        if (adjacente == null) {
            return new LinkedList<Integer>();
        }
        return new LinkedList<Integer>(adjacente);
    }

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.println("Enter in the number of verticies:");
        int numVertices = input.nextInt();
        System.out.println("Enter in the number of links:");
        int numLinks = input.nextInt();
        System.out.println("Enter in the start node:");
        int startNode = input.nextInt();
        int endNode = startNode;

        dfs mapa = new dfs(startNode, numLinks);

        for (int i = 0; i < numLinks; i++) {
            System.out.println("Enter in the start and end for each path");
            mapa.addLink(input.nextInt(), input.nextInt());
        }

        List<ArrayList<Integer>> paths = new ArrayList<ArrayList<Integer>>();
        List<Integer> visited = new ArrayList<Integer>();
        visited.add(startNode);
        Integer currentNode = 0;

        Iterator it = map.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pairs = (Map.Entry) it.next();
            currentNode = (Integer) pairs.getKey();
            //System.out.println("Current Node:" + currentNode);
            mapa.findAllPaths(mapa, visited, paths, currentNode);

        }
    }

    private void findAllPaths(dfs mapa, List<Integer> visited,
            List<ArrayList<Integer>> paths, Integer currentNode) {

        if (currentNode.equals(startNode)) {
            paths.add(new ArrayList<Integer>(visited));

            LinkedList<Integer> nodes = mapa.adjacentNodes(currentNode);
            //System.out.println("visited:" + visited);

            for (Integer node : nodes) {
                //System.out.println("nodes:" + nodes);
                List<Integer> temp = new ArrayList<Integer>();
                temp.addAll(visited);
                temp.add(node);
                findAllPaths(mapa, temp, paths, node);
            }

        } else {
            LinkedList<Integer> nodes = mapa.adjacentNodes(currentNode);
            System.out.println("currentNode:" + currentNode);
            //System.out.println("nodes:" + nodes);
            for (Integer node : nodes) {
                if (visited.contains(node)) {
                    continue;
                }
                List<Integer> temp = new ArrayList<Integer>();
                temp.addAll(visited);
                System.out.println("visited:" + visited);
                temp.add(node);
                findAllPaths(mapa, temp, paths, node);
            }
        }

    }
}
