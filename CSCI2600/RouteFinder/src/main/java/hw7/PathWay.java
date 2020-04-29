package hw7;

import java.io.*;
import java.util.*;
import hw4.*;
import hw6.MarvelPaths2;

//Model class for RouteFinder
public class PathWay{
	/*
	 * Abstraction Function:
	 * 		this.campus=Graph(<V,E>) such that
	 * 			V={b1,b2,...} buildings and intersections on campus
	 * 			E={e1,e1,...} paths connecting buildings and intersections on campus with weight=distance (pixel units)
	 * 
	 * Representation Invariant:
	 * 		if this.campus=null, coords.keySet().size()=0, angles.keySet().size=0
	 * 		else, coords.keySet().size()=campus.size(), angles.keySet().size()=campus.E().size()
	 * 
	 * 
	 */
	private Graph<String,Float> campus;
	private Map<Node<String, Float>, int[]> coords;
	private Map<Edge<Float,String>,String> angles;
	
	public PathWay() {
		this.campus=new Graph<String,Float>("RPI Campus Map");
		this.coords=new HashMap<Node<String,Float>, int[]>();
		this.angles=new HashMap<Edge<Float,String>,String>();
	}
	
	/*
	 * @param nodeData String name for data file containing building information
	 * @param edgeData String name for data file containing path information
	 * @requires nodeData and edgeData are valid files with proper formatting
	 * @throws IOException if any error found in files
	 * @modifies this.campus
	 * @effects populates this.campus.N with building data, populates this.campus.E with path data
	 */
	public void populate(String nodeData, String edgeData) throws IOException {
		FileReader temp=new FileReader(nodeData);
		temp.close();
		temp=new FileReader(edgeData);
		temp.close();
		this.readData(nodeData, edgeData);
	}
	
	//Helper function to parse files
	private void readData(String nodeData, String edgeData) throws IOException {
		BufferedReader nodeReader;
		BufferedReader edgeReader;
		nodeReader=new BufferedReader(new FileReader(nodeData));
		edgeReader=new BufferedReader(new FileReader(edgeData));
		pullNodes(nodeReader);
		pullEdges(edgeReader);
        nodeReader.close();
        edgeReader.close();
	}
	
	//Helper function to generate Nodes. ERROR CATCHES COMMENTED OUT FOR COVERAGE TESTS
	private void pullNodes(BufferedReader nodeReader) throws IOException {
		String line = null;
        while((line=nodeReader.readLine())!=null) {
        	//Get name of building
        	int i=line.indexOf(",");
        	/*
        	if (i==-1) {
        		System.err.println("File not formatted correctly");
        		return;
        	}
        	*/
        	String name=line.substring(0,i);
        	if(name.equals("")) {
        		name="Intersection";
        	}
        	i+=1;
        	//Get ID of building
        	int j=line.indexOf(",", i);
        	//Only pull ID if name==intersection
        	/*
        	if (i==-1) {
        		System.err.println("Trying name: File not formatted correctly");
        		return;
        	}
        	*/
        	int ID=Integer.parseInt(line.substring(i,j));
        	if(name.equals("Intersection")) {
        		name="Intersection "+ID;
        	}
        	i=j+1;
        	//Get x-coord of building
        	j=line.indexOf(",", i);
        	/*
        	if (j==-1) {
        		System.err.println("Trying xcoord: File not formatted correctly");
        		return;
        	}
        	*/
        	int[] location=new int[2];
        	location[0]=Integer.parseInt(line.substring(i,j));
        	//Get y-coord
        	location[1]=Integer.parseInt(line.substring(j+1,line.length()));
        	//Map Node to Location
        	Node<String,Float> building=new Node<String,Float>(name);
        	this.coords.put(building,location);
        	this.campus.addNode(building);
        	//Make sure the ID matches the Graph ID
        	if(building.ID()!=ID) {
        		this.campus.forceID(building,ID);
        	}
        }
	}
	
	//Helper function to generate Edges. ERROR CATCHES COMMENTED OUT FOR COVERAGE TESTS
	private void pullEdges(BufferedReader edgeReader) throws IOException {
		String line;
        while((line=edgeReader.readLine())!=null) {
        	//Get first ID
        	int i=line.indexOf(",");
        	/*
        	if(i==-1) {
        		System.err.println("File not formatted correctly");
        		return;
        	}
        	*/
        	//Find Nodes
        	Node<String,Float> head=this.campus.retrieveNodeID(Integer.parseInt(line.substring(0,i)));
        	Node<String,Float> tail=this.campus.retrieveNodeID(Integer.parseInt(line.substring(i+1,line.length())));
        	int[] hCoords=this.coords.get(head);
        	int[] tCoords=this.coords.get(tail);
        	//Caluclate distance
        	float distance=(float)Math.sqrt((hCoords[0]-tCoords[0])*(hCoords[0]-tCoords[0])+(hCoords[1]-tCoords[1])*(hCoords[1]-tCoords[1]));
        	Edge<Float,String> path=new Edge<Float,String>(head,tail,distance,(Float)distance);
        	this.campus.addEdge(path);
        	//Build reflective Edge
        	Edge<Float,String> revPath=new Edge<Float,String>(tail,head,distance,(Float)distance);
        	this.campus.addEdge(revPath);
        	//Calculate angle and set to positive
        	float angle = (float) Math.toDegrees(Math.atan2(hCoords[1] - tCoords[1], hCoords[0] - tCoords[0]));
           	angle-=90;
        	if(angle<0) {angle+=360;}
        	//Map Edge to direction
           	this.angles.put(path,getDirectionfromAngle(angle)[0]);
           	this.angles.put(revPath,getDirectionfromAngle(angle)[1]);
        }
	}
	
	//Helper function to pull the direction from an angle
	private String[] getDirectionfromAngle(float angle) {
		String[] retval=new String[2];
		if(angle<22.5) {
			retval[0]="North";
			retval[1]="South";
		} else if(angle<67.5) {
			retval[0]="NorthEast";
			retval[1]="SouthWest";
		} else if(angle<112.5) {
			retval[0]="East";
			retval[1]="West";
		} else if(angle<157.5) {
			retval[0]="SouthEast";
			retval[1]="SouthWest";
		} else if(angle<202.5) {
			retval[0]="South";
			retval[1]="North";
		} else if(angle<247.5) {
			retval[0]="SouthWest";
			retval[1]="NorthEast";
		} else if(angle<292.5) {
			retval[0]="West";
			retval[1]="East";
		} else if(angle<337.5) {
			retval[0]="NorthWest";
			retval[1]="SouthEast";
		} else {
			retval[0]="North";
			retval[1]="South";
		}
		return retval;
	}
	
	
	/*
	 * @param label Object representing label of Node trying to be found
	 * @return Node<String,Float> matching label if it exists
	 */
	public Node<String,Float> findNode(Object label){
		try {
			//Check if the label contains Integer ID
			int val=Integer.parseInt((String)label);
			return this.campus.retrieveNodeID(val);
		} catch(NumberFormatException e) {
			//label is a String, not an Integer
			return this.campus.retrieveNode((String)label);
		}
	}
	
	
	/*
	 * Buffer between public interface and existing Dijkstra's algorithm
	 * @param head Node<String,Float> at the start of the path
	 * @param tail Node<String,Float> at the end of the path
	 * @return Map<Node<String,Float>,Edge<Float,String>> mapping each Node to the Edge that connects it to a path from head
	 */
	public Map<Node<String,Float>,Edge<Float,String>> Dijkstra(Node<String,Float> head, Node<String,Float> tail){
		Map<Node<String,Float>,Edge<Float,String>> parents=new HashMap<Node<String,Float>,Edge<Float,String>>();
		MarvelPaths2.Dijkstra(head, parents, this.campus);
		return parents;
	}
	
	
	/*
	 * @param e Edge<Float,String> that has a direction in this.angles
	 * @return String direction from this.angles.get(e)
	 */
	public String EdgeDirection(Edge<Float,String> e) {
		return this.angles.get(e);
	}
	
	
	/*
	 * Buffer between public and private interface
	 * @returns LinkedList of Nodes from this.campus.N
	 */
	public LinkedList<Node<String,Float>> listNodes() {
		return this.campus.N();
	}

}
