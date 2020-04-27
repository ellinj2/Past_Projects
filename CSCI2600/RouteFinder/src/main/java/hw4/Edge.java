package hw4;

/**
 * <b> Edge </b> represents an immutable, directed, weighted edge between two Nodes in a Graph
 * It includes the two incident Nodes, and a weight 
 */

public class Edge<I extends Comparable<I>,V extends Comparable<V>> {
	private  Node<V,I> head;
	private  Node<V,I> tail;
	private  float weight;
	private I name;
	
	/** Abstract function:
	 * 	For some edge E that connects Nodes n1 and n2:
	 * 		E=<n1,n2> such that n1,n2 are in the same Graph
	 * 		
	 */
	
	/** Representation invariant
	 * 		head!=null
	 * 		tail!=null
	 * 		head.parent==tail.parent
	 */
	
	/**
	 * @param u Node that is at the start of this Edge
	 * @param v Node that is at the end of this Edge
	 * @param w Weight of this Edge
	 * @param G Graph that this edge is a part of
	 * @requires u!=null
	 * @requires v!=null
	 * @effects Constructs new Edge with head=u, tail=v, weight=w
	 */
	public Edge(Node<V,I> u, Node<V,I> v, float w, I label) {
		this.head=u;
		this.tail=v;
		this.weight=w;
		this.name=label;
		//checkRep();
		u.addOut(v);
		u.setMinEdge(v, this);
	}
	
	
	/**
	 * @return The head Node
	 */
	public Node<V,I> head() {
		return this.head;
	}
	
	
	/**
	 * @return The tail Node
	 */
	public Node<V,I> tail() {
		return this.tail;
	}
	
	
	/**
	 * @return The weight of the Edge
	 */
	public float weight() {
		return this.weight;
	}
	
	
	/**
	 * @return the name of the Edge
	 */
	public I name() {
		return this.name;
	}
	
	
	/**
	 * String representation of the Edge
	 * 
	 * @return A String representation of the Edge to display incident Nodes, direction, and weight
	 * 		Format:
	 * 		head.ID-name->tail.ID (weight)
	 */
	@Override
	public String toString() {
		StringBuilder output=new StringBuilder();
		output.append(head.name());
		output.append("-"+this.name()+"->");
		output.append(tail.name());
		output.append(" ("+weight+")");
		return output.toString();
	}
	
	/**
	 * @param other The Edge to be compared to
	 * @requires other!=null
	 * @returns 1 if this.name.compareTo(other.name)==1
	 * 					this.name.compareTo(other.name)==0 && this.head.compareTo(other.head)==1
	 * 					this.head.compareTo(other.head)==0 && this.tail.compareTo(other.tail)==1
	 * 					this.head.compareTo(other.head)==0 && this.tail.compareTo(other.tail)==0 && this.weight>other.weight
	 * @returns 0 if this.head.compareTo(other.head)==0 && this.tail.compareTo(other.tail)==0 && this.weight==other.weight
	 * @returns -1 otherwise
	 * */
	public int compareTo(Edge<I,V> other) {
		int byName=this.compareName(other);
		if(byName>0) {return 1;}
		else if(byName==0) {
			int test=this.head.compareName(other.head());
			if(test>0) {
				return 1;
			} else if(test==0) {
				int tailTest=this.tail.compareName(other.tail());
				if(tailTest>0) {
					return 1;
				} else if(tailTest==0) {
					if(this.weight>other.weight()) {return 1;}
					if(this.weight==other.weight()) {return 0;}
				}
			}
		}
		return -1;
	}
	
	
	/**
	 * @param other Edge to be compared to
	 * @requires other!=null
	 * @returns this.name().toString().compareTo(other.name().toString())
	 */
	public int compareName(Edge<I,V> other) {
		return this.name().toString().compareTo(other.name().toString());
	}
	
	
	@Override
	public int hashCode() {
		return this.name().hashCode();
	}
	
	@Override
	public boolean equals(Object o) {
		if(o instanceof Edge<?,?>) {
			if(((Edge<?,?>)o).name().equals(this.name()) && ((Edge<?,?>)o).weight()==(this.weight) && ((Edge<?,?>)o).head().name().equals(head.name()) && ((Edge<?,?>)o).tail().name().equals(tail.name())) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * @throws RuntimeException if RepInvar is violated
	 */
	/* Not called
	private void checkRep() throws RuntimeException{
		if(head==null || tail==null) {
			throw new RuntimeException("Error: Edges cannot connect null Nodes");
		}
		if((head.parent()==null && tail.parent()!=null) || (head.parent()!=null && tail.parent()==null)) {
			throw new RuntimeException("Error: head and tail are not in the same Graph");
		}
		if(head.parent()!=null && head.parent().compareTo(tail.parent())!=0) {
			throw new RuntimeException("Error: head and tail are not in the same Graph");
		}
	}
	*/
}
