package hw6;

import hw4.*;
import hw5.MarvelParser;

import java.io.IOException;
import java.util.*;

/**
 * <b>MarvelPaths2</b> represents a dense graph representing a "multiverse" generated from a .csv file
 * It includes a Graph representation and a mapping of Node strings to Nodes. It differs from <b>MarvelPaths</b>
 * because the Edges are labeled with floats as weights instead of Strings as names
 */
public class MarvelPaths2{
	/*
	 * Abstraction function:
	 * From some file data.csv:
	 * 		this.Universe.N=<n1,n2,...,ni> for n1,n2... in data.csv column 1
	 * 		this.Universe.E=<e1,e2,...,ej> for e1,e2... in data.csv column 2 s.t. e=(data.csv(a,1), data.csv(b,1)) iff data.csv(a,2)==data.csv(b,2)
	 * 			that is, e connects 2 entries from column 1 if those entries have the same column 2 value
	 * 		this.reference=<s1,n1; s2,n2;...;si,ni> such that s=n.name
	 * 
	 * Representation invariant:
	 * 		reference.getKeySet()=={n.name()} for n in Universe.N()
	 */
	private Graph<String,Float> Universe; //Graph representation
	private Map<String, Node<String,Float>> reference; //Map Node.name.toString to Node for efficiency
	
	/*
	 * @effect creates a new MarvelPaths2 object
	 */
	public MarvelPaths2() {
		Universe=new Graph<String,Float>("Marvel Cinematic Universe");
		reference=new HashMap<String, Node<String,Float>>();
	}
	
	/*
	 * @param filename String directory for data file
	 * @modifies this.Universe, this.reference
	 * @effects Populates this.Universe and this.reference using the data file
	 */
	public void createNewGraph(String filename) {
		try {
			MarvelParser.readData2(filename, Universe, reference);
		} catch (IOException e) {
			System.out.println("Whoops...Found an error");
		}
	}
	
	/*
	 * @param n1 Node that Dijkstra's algorithm starts at
	 * @param parent Map that pairs a Node to the Edge that connects it to the spanning tree
	 * @modifies parent
	 * @effects populates parent with relevant data
	 */
	public static void Dijkstra(Node<String,Float> n1, Map<Node<String,Float>,Edge<Float,String>> parent, Graph<String,Float> uni){
		//Initialize n1 to null
		parent.put(n1,null);
		//Store optimal distances by Node ID starting as MAXVALUE
		float[] distance=new float[uni.maxID()];
		for(int i=0; i<distance.length; i++) {
			distance[i]=Float.MAX_VALUE;
		}
		//Set n1 to 0
		distance[n1.ID()-1]=0;
		//Track Nodes to visit
		LinkedList<Node<String,Float>> queue=new LinkedList<Node<String,Float>>();
		queue.add(n1);
		//Iterate until the queue is empty
		while(queue.size()>0) {
			Node<String,Float> n=queue.removeFirst();
			//Check neighbors
			for(Node<String,Float> v: n.outNeighborhood()) {
				Edge<Float,String> e=n.getMinEdge(v);
				//Check if the minimal Edge decreases the distance to v
				if(distance[n.ID()-1]+e.weight()<distance[v.ID()-1]) {
					distance[v.ID()-1]=distance[n.ID()-1]+e.weight();
					//Store the new parent Edge of v
					if(!parent.containsKey(v)) {
						parent.put(v,e);
					} else {
						parent.replace(v,e);
					}
					//Add v to the queue, even if it's been found before
					queue.add(v);
				}
			}
		}
	}
	
	/*
	 * @param node1 String value representing the label of the Node to start the search from
	 * @param node2 String value representing the label of the Node to stop the search at
	 * @return formatted String representing the optimal path from node1 to node2 using Dijkstra's algorithm
	 */
	public String findPath(String node1, String node2) {
		StringBuilder output=new StringBuilder();
		boolean trip=false;
		if(!reference.containsKey(node1.toString())) {
			output.append("unknown character "+node1+'\n');
			trip=true;
		}
		if(!reference.containsKey(node2.toString()) && !node1.toString().equals(node2.toString())) {
			output.append("unknown character "+node2+'\n');
			trip=true;
		}
		if(trip) {
			return output.toString();
		}

		output.append("path from "+node1+" to "+node2+":\n");
		
		if(node1.toString().equals(node2.toString())) {
			output.append("total cost: 0.000\n");
			return output.toString();
		}
		
		Node<String,Float> n1=reference.get(node1);
		Node<String,Float> n2=reference.get(node2);
		Map<Node<String,Float>,Edge<Float,String>> parents=new HashMap<Node<String,Float>, Edge<Float,String>>();
		Dijkstra(n1,parents,this.Universe);
		float cost=0;
		Edge<Float,String> e=parents.get(n2);
		if(e==null) {
			output.append("no path found\n");
			return output.toString();
		} else {
			LinkedList<Edge<Float,String>> path=new LinkedList<Edge<Float,String>>();
			while(e!=null) {
				cost+=e.weight();
				path.add(e);
				e=parents.get(e.head());
			}
			while(path.size()>0) {
				e=path.removeLast();
				output.append(e.head().name()+" to "+e.tail().name()+" with weight "+String.format("%.3f",e.weight())+"\n");
			}
		}
		
		output.append("total cost: "+String.format("%.3f",cost)+"\n");
		return output.toString();
	}
	
	//For testing purposes
	public int getSize(String val){
		if(val.equalsIgnoreCase("N")) {
			return Universe.size();
		}
		if(val.equalsIgnoreCase("E")) {
			return Universe.E().size();
		}
		return 0;
	}
	
}
