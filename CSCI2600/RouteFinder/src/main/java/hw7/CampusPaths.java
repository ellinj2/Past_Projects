package hw7;

//import hw4.*;
import java.util.*;
import java.io.*;

//Controller
public class CampusPaths{
	private PathWay campus;
	public PathDisplay window;
	
	public CampusPaths(String nodeData, String edgeData) throws IOException {
		this.campus=new PathWay();
		this.campus.populate(nodeData, edgeData);
		this.window=new PathDisplay(this.campus);
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
				System.out.print(map.window.listNodes());
				//System.out.println("Displayed all buildings in "+(System.currentTimeMillis()-start)+" milliseconds");
			} else if(text.equals("r")) {
				System.out.print("First building id/name, followed by Enter: ");
				String building1=scanner.nextLine();
				System.out.print("Second building id/name, followed by Enter: ");
				String building2=scanner.nextLine();
				//long start=System.currentTimeMillis();
				System.out.print(map.window.findPath(building1,building2));
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
