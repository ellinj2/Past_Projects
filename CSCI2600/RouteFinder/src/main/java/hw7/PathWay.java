package hw7;

import java.io.*;
import java.util.*;
import hw4.*;
import hw6.MarvelPaths2;

//Model
public class PathWay{
	private Graph<String,Float> campus;
	private Map<Node<String, Float>, int[]> coords;
	private Map<Edge<Float,String>,String> angles;
	//private ArrayList<PathDisplay> observers;
	
	public PathWay() {
		//this.observers=new ArrayList<PathDisplay>();
		this.campus=new Graph<String,Float>("RPI Campus Map");
		this.coords=new HashMap<Node<String,Float>, int[]>();
		this.angles=new HashMap<Edge<Float,String>,String>();
	}
	
	
	public void populate(String nodeData, String edgeData) throws IOException {
		FileReader temp=new FileReader(nodeData);
		temp.close();
		temp=new FileReader(edgeData);
		temp.close();
		this.readData(nodeData, edgeData);
	}
	
	
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
        	Node<String,Float> building=new Node<String,Float>(name);
        	this.coords.put(building,location);
        	this.campus.addNode(building);
        	if(building.ID()!=ID) {
        		this.campus.forceID(building,ID);
        	}
        	//this.notifyObservers("Added building #"+building.ID()+": "+building.name()+" at "+location[0]+", "+location[1]);
        }
	}
	
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
        	Node<String,Float> head=this.campus.retrieveNodeID(Integer.parseInt(line.substring(0,i)));
        	Node<String,Float> tail=this.campus.retrieveNodeID(Integer.parseInt(line.substring(i+1,line.length())));
        	int[] hCoords=this.coords.get(head);
        	int[] tCoords=this.coords.get(tail);
        	float distance=(float)Math.sqrt((hCoords[0]-tCoords[0])*(hCoords[0]-tCoords[0])+(hCoords[1]-tCoords[1])*(hCoords[1]-tCoords[1]));
        	Edge<Float,String> path=new Edge<Float,String>(head,tail,distance,(Float)distance);
        	this.campus.addEdge(path);
        	Edge<Float,String> revPath=new Edge<Float,String>(tail,head,distance,(Float)distance);
        	this.campus.addEdge(revPath);
        	float angle = (float) Math.toDegrees(Math.atan2(hCoords[1] - tCoords[1], hCoords[0] - tCoords[0]));
           	angle-=90;
        	if(angle<0) {angle+=360;}
           	this.angles.put(path,getDirectionfromAngle(angle)[0]);
           	this.angles.put(revPath,getDirectionfromAngle(angle)[1]);
        	//this.notifyObservers("Added a "+String.format("%.3f",distance)+" pixel "+getDirectionfromAngle(angle)[0]+"ern path from "+head.name()+"("+head.ID()+") to "+tail.name()+"("+tail.ID()+")");
        }
	}
	
	
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
	
	public Node<String,Float> findNode(Object label){
		//if(label instanceof String) {
			try {
				int val=Integer.parseInt((String)label);
				return this.campus.retrieveNodeID(val);
			} catch(NumberFormatException e) {
				return this.campus.retrieveNode((String)label);
			}
		//}		
		//return null;
	}
	
	
	public Map<Node<String,Float>,Edge<Float,String>> Dijkstra(Node<String,Float> head, Node<String,Float> tail){
		Map<Node<String,Float>,Edge<Float,String>> parents=new HashMap<Node<String,Float>,Edge<Float,String>>();
		MarvelPaths2.Dijkstra(head, parents, this.campus);
		return parents;
	}
	
	
	public String EdgeDirection(Edge<Float,String> e) {
		return this.angles.get(e);
	}
	
	
	public LinkedList<Node<String,Float>> listNodes() {
		return this.campus.N();
	}
	
	/*
	public void addObserver(PathDisplay p) {
		this.observers.add(p);
	}
	*/
	
	/*
	private void notifyObservers(String s) {
		for(PathDisplay o:this.observers) {
			o.displayText(s);
		}
	}
	*/
	
	/*
	public static void main(String args[]) {
		//Construction tests
		//long startTime=System.currentTimeMillis();
		PathWay test=new PathWay();
		//test.addObserver(new PathDisplay(test));
		test.readData("data/RPI_map_data_Nodes.csv", "data/RPI_map_data_Edges.csv");
		//long endTime=System.currentTimeMillis();
		//System.out.println("That took "+(endTime-startTime)+" milliseconds");
	}
	*/
}
