package hw4;

import java.util.*;

/** <b> Node </b> represents a <b> mutable </b> representation of a vertex in a graph.
 * It includes a unique identification integer, an in-neighborhood and an out-neighborhood.
 */

public class Node<L extends Comparable<L>,M extends Comparable<M>> {
	private int ID;
	private final L name;
	private Graph<L,M> parent;
	private LinkedList<Node<L,M>> in_neighborhood;
	private LinkedList<Node<L,M>> out_neighborhood;
	private Map<Node<L,M>, Edge<M,L>> minEdge;
	
	/** Abstract function
	 * 	For Node n with label name, the <i>i</i>th Node in some Graph:
	 * 		n=<name, i> such that name is the designated label and i is the relative ID number of the Node
	 */
	
	/* Representation invariant for every Node n:
	 * 		(n.ID>=1) && (n.ID>i => there exists some node with ID i in the graph
	 * 
	 * In other words:
	 * 		n.ID is at least 1
	 * 		Node IDs are consecutive integers from 1 to the size of the graph
	 */
	
	/**
	 * Special function for testing purposes
	 */
	public Node(L val) {
		this.name=val;
		this.parent=null;
		this.in_neighborhood=new LinkedList<Node<L,M>>();
		this.out_neighborhood=new LinkedList<Node<L,M>>();
		this.minEdge=new HashMap<Node<L,M>, Edge<M,L>>();
		//checkRep();
	}
	
	/**
	 * @param val The ID of the Node
	 * @param g The Graph this Node is a part of
	 * @requires val>=1 && g!=null
	 * @effects Constructs new Node with ID=val
	 */
	public Node(L val, Graph<L,M> g) {
		this.name=val;
		this.parent=g;
		this.in_neighborhood=new LinkedList<Node<L,M>>();
		this.out_neighborhood=new LinkedList<Node<L,M>>();
		g.addNode(this);
		this.minEdge=new HashMap<Node<L,M>, Edge<M,L>>();
		//checkRep();
	}
	
	
	/**
	 * Strictly for adding Node to a Graph
	 * 
	 * @modifies this.ID
	 * @effects set this.ID to Graph.size
	 */
	void setID(int n) {
		this.ID=n;
	}
	
	
	/**
	 * @param other Node object to be added to the in-neighborhood of this Node
	 * @requires other!=null
	 * @modifies other
	 * @effects Adds other to this.in_neighborhood. Adds this to other.out_neighborhood
	 */
	public void addIn(Node<L,M> other) {
		this.in_neighborhood.add(other);
		other.recAddOut(this);
		//checkRep();
	}
	
	
	/**Implementation of addIn for reciprocal adding of Node*/
	public void recAddIn(Node<L,M> other) {
		this.in_neighborhood.add(other);
		//checkRep();
	}
	
	
	/**
	 * @param other Node object to be added to the out-neighborhood of this Node
	 * @requires other!=null
	 * @modifies other
	 * @effects Adds other to this.out_neighborhood. Adds this to other.in_neighborhood
	 */
	public void addOut(Node<L,M> other) {
		this.out_neighborhood.add(other);
		other.recAddIn(this);
		//checkRep();
	}
	
	
	/**Implementation of addOut for reciprocal adding of Node*/
	public void recAddOut(Node<L,M> other) {
		this.out_neighborhood.add(other);
	}
	
	
	/*
	 * @param other Node to connect to
	 * @param e Edge connecting this to other
	 * @modifies this.minEdge
	 * @effects if e is lexicographically smaller than the value in minEdge[other], minEdge[other]=e
	 * @return true if e was added to this.minEdge. False otherwise
	 */
	boolean setMinEdge(Node<L,M> other, Edge<M,L> e) {
		if(!this.minEdge.containsKey(other)) {
			this.minEdge.put(other,e);
			return true;
		}
		else {
			if (e.compareName(this.minEdge.get(other))<0) {
				this.minEdge.replace(other, e);
				return true;
			}
		}
		return false;
	}
	
	
	/*
	 * @param other Node to retrieve from this.minEdge
	 * @return return the Edge stored in minEdge[other]
	 */
	public Edge<M,L> getMinEdge(Node<L,M> other) {
		return this.minEdge.get(other);
	}
	
	
	/**
	 * @return The ID of the Node
	 */
	public int ID() {
		return this.ID;
	}

	
	/**
	 * @return The name of this Node
	 */
	public L name() {
		return this.name;
	}
	
	
	/**
	 * @return Size of the Node's in-neighborhood
	 */
	public int inDegree() {
		return this.in_neighborhood.size();
	}
	
	
	/**
	 * @returns Size of the Node's out-neighborhood
	 */
	public int outDegree() {
		return this.out_neighborhood.size();
	}
	
	
	/**
	 * @return Array of Nodes in this.in_neighborhood sorted by name
	 */
	public LinkedList<Node<L,M>> inNeighborhood() {
		this.sortIns();
		LinkedList<Node<L,M>> retVal=new LinkedList<Node<L,M>>(this.in_neighborhood);
		return retVal;
	}
	
	
	/**
	 * @return Array of Nodes in this.out_neighborhood sorted by name
	 */
	public LinkedList<Node<L,M>> outNeighborhood() {
		this.sortOuts();
		LinkedList<Node<L,M>> retVal=new LinkedList<Node<L,M>>(this.out_neighborhood);
		return retVal;
	}
	
	
	/**
	 * @modifies this.in_neighborhood
	 * @effects sorts this.in_neighborhood by name
	 */
	public void sortIns() {
		Comparator<Node<L,M>> byName=(Node<L,M> n1, Node<L,M> n2)->n1.compareName(n2);
		Collections.sort(this.in_neighborhood, byName);
	}
	
	
	/**
	 * @modifies this.out_neighborhood
	 * @effects sorts this.out_neighborhood by name
	 */
	public void sortOuts() {
		Comparator<Node<L,M>> byName=(Node<L,M> n1, Node<L,M> n2)->n1.compareName(n2);
		Collections.sort(this.out_neighborhood, byName);
	}
	
	
	/**
	 * @param other The Node to be compared to
	 * @requires other!=null
	 * @returns 1 if this.ID>other.ID
	 * @returns 0 if this.ID==other.ID
	 * @returns -1 if this.ID<other.ID
	 */
	public int compareTo(Node<L,M> other) {
		if(this.ID()>other.ID()) {
			return 1;
		} else if(this.ID==other.ID()) {
			return 0;
		} else {
			return -1;
		}
	}
	
	
	/**
	 * @param other The Node to be compared to
	 * @requires other!=null
	 * @returns this.name().compareTo(other.name())
	 */
	public int compareName(Node<L,M> other) {
		return this.name().toString().compareTo(other.name().toString());
	}
	
	
	/**
	 * Specific function for testing purposes
	 */
	void setParent(Graph<L,M> g) {
		this.parent=g;
	}
	
	
	/**
	 * @return the Graph this Node is in
	 */
	public Graph<L,M> parent() {
		return this.parent;
	}
	
	
	/**
	 * Returns a String representation of this Node object
	 * 
	 * @returns A String representation of the Node represented by this object,
	 * 		with neighboring Nodes sorted by ID
	 * 
	 * 		Format:
	 * 		Data for Node: this.ID
	 * 		In Degree: this.inDegree
	 * 		In Neighborhood: this.in_neighborhood
	 * 		Out Degree: this.outDegree
	 * 		Out Neighborhood: this.out_neighborhood
	 * 
	 */
	@Override
	public String toString() {
		StringBuilder output=new StringBuilder();
		output.append("Data from Node: "+this.name);
		if(this.parent!=null) {
			output.append(", Node #"+this.ID+" in Graph: "+this.parent.ID());
		}
		if(this.inDegree()>0) {
			Collections.sort(this.in_neighborhood, Comparator.comparingInt(obj->obj.ID()));
			output.append("\nIn Degree: "+this.inDegree()+"\n");
			output.append("In Neighborhood: ");
			int counter=0;
			for(Node<L,M> n: this.in_neighborhood) {
				output.append(n.ID());
				counter++;
				if(counter!=this.inDegree()) {
					output.append(", ");
				}
			}
		}
		if(this.outDegree()>0) {
			Collections.sort(this.out_neighborhood, Comparator.comparingInt(obj->obj.ID()));
			output.append("\nOut Degree: "+this.outDegree()+"\n");
			output.append("Out Neighborhood: ");
			int counter=0;
			for(Node<L,M> n: this.out_neighborhood) {
				output.append(n.ID());
				counter++;
				if(counter!=this.outDegree()) {
					output.append(", ");
				}
			}
		}
		return output.toString();
	}
	
	/*Never gets called
	private void checkRep() throws RuntimeException {
		if(this.ID<=0 && this.parent!=null) {
			throw new RuntimeException("Error: The ID of Node "+this.ID()+" is not an appropriate value");
		}
		if(this.parent!=null && this.ID>this.parent.size()+1) {
			throw new RuntimeException("Error: The ID of Node "+this.ID()+" is beyond the size of the graph");
		}
	}*/
	
	@Override
	public boolean equals(Object o) {
		if(o instanceof Node<?,?>) {
			if(((Node<?,?>)o).name().equals(this.name) && ((Node<?,?>)o).ID()==this.ID){
				return true;
			}
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		return this.name.hashCode();
	}
	
}
