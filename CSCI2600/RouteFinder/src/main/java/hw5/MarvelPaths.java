package hw5;

import hw4.*;
import java.io.*;
import java.util.*;

/**
 * <b>MarvelPaths</b> represents a dense graph representing a "multiverse" generated from a .csv file
 * It includes a Graph representation and a mapping of Node strings to Nodes
 */

class MarvelPaths{
	private Graph<String,String> Universe; //Graph representation
	private Map<String, Node<String,String>> reference; //Map Node.name.toString to Node for efficiency

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
	
	
	/*
	 * @effects creates new MarvelPaths object with empty instances of Universe and reference
	 */
	public MarvelPaths() {
		Universe=new Graph<String,String>("Marvel Cinematic Universe");
		reference=new HashMap<String, Node<String,String>>();
	}
	
	
	/*
	 * @param filename String directory for data file
	 * @modifies this.Universe, this.reference
	 * @effects Populates this.Universe and this.reference using the data file, then sorts the Nodes and Edges lexicographically to optimize runtime
	 */
	public void createNewGraph(String filename) {
		//Get data from file and populate Graph
		try {
			MarvelParser.readData(filename, Universe, reference);
		} catch (IOException e) {
			System.out.println("Whoops...Found an error");
		}
		Universe.sortNodes();
	}
	
	
	/*
	 * @param start Node to start the BFS operation
	 * @param end Node to end the BFS operation
	 * @requires start!=null, end!=null
	 * @return Mapping of each Node to the Edge that connected it to the previous Node. Null if no start-end path found
	 */
	public Map<Node<String,String>, Edge<String,String>> BFS(Node<String,String> start, Node<String,String> end){
		LinkedList<Node<String,String>> Q=new LinkedList<Node<String,String>>();
		Map<Node<String,String>, Edge<String,String>> M=new HashMap<Node<String,String>, Edge<String,String>>();
		Q.add(start);
		M.put(start, null);
		
		while(Q.size()>0) {
			Node<String,String> n=Q.removeFirst();
			for(Node<String,String> v: n.outNeighborhood()) {
				if(!M.containsKey(v)) {
					M.put(v, n.getMinEdge(v));
					if(v.name().toString().equals(end.name().toString())) {
						return M;
					}
					Q.add(v);
				}
			}
		}
		
		return null;
	}
	
	
	/*
	 * @param node1 Node label to start BFS from
	 * @param node2 Node label to end BFS at
	 * @requires node1!=null, node2!=null
	 * @return Formatted String output from the BFS algorithm displaying the path taken from node1 to node2
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
			return output.toString();
		}
		
		Map<Node<String,String>,Edge<String,String>> path=BFS(reference.get(node1.toString()), reference.get(node2.toString()));
		
		if(path==null) {
			output.append("no path found\n");
		}
		else {
			LinkedList<Edge<String,String>> route=new LinkedList<Edge<String,String>>();
			Edge<String,String> e=path.get(reference.get(node2.toString()));
			while(e!=null) {
				route.add(e);
				e=path.get(e.head());
			}
			while(route.size()>0) {
				e=route.removeLast();
				output.append(e.head().name()+" to "+e.tail().name()+" via "+e.name()+'\n');
			}
		}
		
		return output.toString();
	}
	
	//For testing purposes
	/*
	 * @param val String representing what aspect of Universe wants to be accessed
	 * @return Universe.size if val=="N". Universe.E.size() if val=="E". 0 otherwise
	 */
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
