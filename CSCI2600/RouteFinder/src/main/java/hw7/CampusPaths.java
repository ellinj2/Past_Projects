package hw7;

//import hw4.*;
import java.util.*;
import java.io.*;

//Controller class for RotueFinder
public class CampusPaths{
	/*
	 * Abstraction Function:
	 * 		this.campus=Graph(<V,E>) such that
	 * 			V={b1, b2,...} buildings and intersections on campus
	 * 			E={e1, e1,...} paths connecting buildings and intersections on campus
	 * 		this.window is a View object allowing analysis of the campus
	 * 
	 * Rep Invariant:
	 * 		if and only if campus=null, window=null
	 */
	private PathDisplay window;
	
	public CampusPaths(String nodeData, String edgeData) throws IOException {
		PathWay campus=new PathWay();
		campus.populate(nodeData, edgeData);
		this.window=new PathDisplay(campus);
	}
	
	/*
	 * Used as a buffer to access private window object
	 * @param building1 Object name or ID of the starting building
	 * @param building2 Object name or ID of the ending building
	 * @return String representing route from building1 to building2 as calculated in window.findPath()
	 */
	public String findPath(Object building1, Object building2) {
		return this.window.findPath(building1, building2);
	}
	
	/*
	 * Used as a buffer to access private window object
	 * @return String representing the buildings and respective IDs for all buildings as formatted in window.listNodes()
	 */
	public String listNodes() {
		return this.window.listNodes();
	}
	
	public static void main(String[] args) throws IOException {
		//long time=System.currentTimeMillis();
		CampusPaths map=new CampusPaths("data/RPI_map_data_Nodes.csv","data/RPI_map_data_Edges.csv");
		//System.out.println("Created the map in "+(System.currentTimeMillis()-time)+" milliseconds");
		Scanner scanner=new Scanner(System.in);
		String text;
		while(true) {
			text=scanner.nextLine();
			if(text.equals("q")) {
				//System.out.println("Exiting program");
				scanner.close();
				//System.out.println("\nThis software used "+String.format("%.2f",((float)(Runtime.getRuntime().totalMemory()-Runtime.getRuntime().freeMemory())/1024/1024))+"MB of data");
				return;
			} else if(text.equals("b")) {
				//long start=System.currentTimeMillis();
				System.out.print(map.listNodes());
				//System.out.println("Displayed all buildings in "+(System.currentTimeMillis()-start)+" milliseconds");
			} else if(text.equals("r")) {
				System.out.print("First building id/name, followed by Enter: ");
				String building1=scanner.nextLine();
				System.out.print("Second building id/name, followed by Enter: ");
				String building2=scanner.nextLine();
				//long start=System.currentTimeMillis();
				System.out.print(map.findPath(building1,building2));
				//System.out.println("Found the path in "+(System.currentTimeMillis()-start)+" milliseconds");
			} else if(text.equals("m")) {
				System.out.println("Accepted inputs:");
				System.out.println("b lists all buildings (only buildings) in the form name,id in lexicographic (alphabetical) order of name.\r\n" + 
						"r prompts the user for the ids or names of two buildings (only buildings!) and prints directions for the shortest route between them.\r\n" + 
						"q quits the program.\r\n" + 
						"m prints a menu of all commands.");
			} else {
				System.out.println("Unknown option");
			}
		}
		
	}
}
