package hw4;

import java.util.*;

/**
 * <b> Graph </b> represents a mutable, weighted, directed, complex graph.
 * It includes a name as a String, a set of Nodes, and a list of edges
 *
 */

public class Graph<T extends Comparable<T>,U extends Comparable<U>> {
	private int size;
	private String ID;
	private LinkedList<Node<T,U>> N;
	private LinkedList<Edge<U,T>> E;
	private int maxID;
	
	/** Abstraction function:
	 * 	For some Graph G with a list of nodes N=<n1,n2,n3,...> and list of edges E=<e1,e2,e3,...>:
	 * 		G=<N,E> such that forall e=(n,m) in E, n,m in N
	 * 	
	 */
	
	/** Representation invariant:
	 * 		foreach u,v in N, u!=v
	 * 		size>=0
	 * 		size==N.size()
	 * 		E.size()==0 if N.size()==0
	 */
	
	/**
	 * @param name The ID of the Graph
	 * @requires name!=null
	 * @effects Constructs new Graph with ID=name, size=0, N={}, E={}
	 */
	public Graph(String name) {
		this.size=0;
		this.ID=name;
		this.maxID=0;
		this.N=new LinkedList<Node<T,U>>();
		this.E=new LinkedList<Edge<U,T>>();
		//checkRep();
	}
	
	/**
	 * @param name The ID of the Graph
	 * @param ns The Nodes in the Graph
	 * @param es The Edges in the Graph
	 * @requires name!=null
	 * @requires ns!=null
	 * @requires es!=null
	 * @effects Constructs new Graph with ID=name, N=ns, E=es, size=ns.size
	 */
	public Graph(String name, LinkedList<Node<T,U>> ns, LinkedList<Edge<U,T>> es) {
		this.size=ns.size();
		this.ID=name;
		this.N=ns;
		for(Node<T,U> n:ns) {
			n.setParent(this);
			if(n.ID()>this.maxID) {
				this.maxID=n.ID();
			}
		}
		this.E=es;
		//checkRep();
	}
	

	/**
	 * @param n Node to be added to Graph
	 * @requires n!=null, n not in this.N
	 * @modifies this.N, this.size
	 * @effects adds n to this.N. Increments this.size by 1
	 */
	public void addNode(Node<T,U> n) {
		this.N.add(n);
		this.size++;
		n.setID(this.size);
		n.setParent(this);
		this.maxID+=1;
		//checkRep();
	}

	
	public void forceID(Node<T,U>n, int val) {
		n.setID(val);
		if(val>this.maxID) {
			this.maxID=val;
		}
	}
	
	
	public int maxID() {
		return this.maxID;
	}
	
	
	/**
	 * @param e Edge to be added to Graph
	 * @requires e!=null, e.head and e.tail in this.N
	 * @modifies this.E, e.head, e.tail
	 * @effects adds e to this.E. Calls e.head.addOut(e.tail) and e.tail.addIn(e.head)
	 */
	public void addEdge(Edge<U,T> e) {
		//Trash the node if it was deemed unneeded for memory
		if(e.head()==null || e.tail()==null || e.name()==null) {e=null; return;}
		this.E.add(e);
		//checkRep();
	}
	

	public boolean newEdge(Node<T,U> u, Node<T,U> v, float w, U label) {
		Edge<U,T> result=u.getMinEdge(v);
		if(result==null) {
			this.addEdge(new Edge<U,T>(u,v,w,label));
			return true;
		}
		if(label.compareTo(result.name())<0) {
			this.addEdge(new Edge<U,T>(u,v,w,label));
			return true;
		}
		return false;
	}
	
	
	public boolean newEdge(Edge<U,T> e) {
		Edge<U,T> result=e.head().getMinEdge(e.tail());
		if(result==null) {
			this.addEdge(e);
			return true;
		}
		if(e.name().compareTo(result.name())<0) {
			this.addEdge(e);
			return true;
		}
		return false;
	}
	
	/**
	 * @return The number of Nodes in the Graph
	 */
	public int size() {
		return this.size;
	}
	
	
	/**
	 * @return The ID of the Graph
	 */
	public String ID() {
		return this.ID;
	}
	
	
	/**
	 * @return An LinkedList of Graph.N sorted by name
	 */
	public LinkedList<Node<T,U>> N() {
		LinkedList<Node<T,U>> temp=new LinkedList<Node<T,U>>(this.N);
		Comparator<Node<T,U>> compareByName=(Node<T,U> o1, Node<T,U> o2)->o1.compareName(o2);
		Collections.sort(temp, compareByName);
		return temp;
	}
	
	
	/**
	 * @return An Array of Graph.E sorted by name
	 */
	public LinkedList<Edge<U,T>> E() {
		LinkedList<Edge<U,T>> temp=new LinkedList<Edge<U,T>>(this.E);
		Comparator<Edge<U,T>> compareByName=(Edge<U,T> o1, Edge<U,T> o2)->o1.compareName(o2);
		Collections.sort(temp,  compareByName);
		return temp;
	}
	
	
	/**
	 * @param n String value representing the name of the desired Node in this Graph
	 * @return The Node in the Graph with name n, null if n is not in the Graph
	 */
	public Node<T,U> retrieveNode(T n) {
		for(Node<T,U> item:this.N) {
			if(n.getClass().toString().equals(item.name().getClass().toString()) && n.toString().equals(item.name().toString())) {
				return item;
			}
		}
		return null;
	}
	
	
	/**
	 * @param n Integer ID of the desired Node
	 * @return the Node in the Graph with ID n, null if n is not in the Graph
	 */
	public Node<T,U> retrieveNodeID(int n) {
		for(Node<T,U> v:this.N) {
			if(v.ID()==n) {
				return v;
			}
		}
		return null;
	}
	
	
	/**
	 * @effects Node n for all n in this.N
	 * @modifies calls n.sortIns() and n.sortOuts()
	 */
	public void sortNodes() {
		for(Node<T,U> n:this.N) {
			n.sortIns();
			n.sortOuts();
		}
	}
	
	
	/**
<<<<<<< HEAD
	 * @effects this.E
	 * @modifies sorts this.E by e.name() for e in this.E
	 */
	public void sortEdges() {
		Comparator<Edge<U,T>> byName=(Edge<U,T> e1, Edge<U,T> e2)->e1.compareName(e2);
		Collections.sort(this.E, byName);
	}
	
	
	/**
=======
>>>>>>> 9e9c3e14fe67e9a787e405d6c1b35a9ca78c583f
	 * @param head Integer value representing the ID of the head node of the desired Edge in this Graph
	 * @param tail Integer value representing the ID of the tail node of the desired Edge in this Graph
	 * @param weight Integer value representing the weight of the desired Edge in this Graph
	 * @return The Edge in the Graph with head.ID==head, tail.ID==tail, weight==weight; null if no such edge exists in this Graph
	 */
	public Edge<U,T> retrieveEdge(T head, T tail, int weight, U name) {
		Edge<U,T> test=new Edge<U,T>(new Node<T,U>(head), new Node<T,U>(tail), weight, name);
		for(Edge<U,T> e:this.E) {
			if(!e.getClass().toString().equals(test.getClass().toString())) {continue;}
			if(test.compareTo(e)==0) {
				return e;
			}
		}
		return null;
	}
	
	
	/**
	 * @param e Edge to be removed
	 * @requires e is in this Graph
	 * @modifies this.E
	 * @effects removes e from this.E
	 */
	public void removeEdge(Edge<U,T> e) {
		this.E.remove(e);
	}
	
	
	/**
	 * @param head Integer value representing the ID of the head node of the desired Edge(s) in this Graph
	 * @param tail Integer value representing the ID of the tail node of the desired Edge(s) in this Graph
	 * @return Array of all Edges that connect head to tail sorted by weight
	 */
	public LinkedList<Edge<U,T>> findEdgesID(int head, int tail) {
		LinkedList<Edge<U,T>> temp=new LinkedList<Edge<U,T>>();
		for(Edge<U,T> e: this.E) {
			if(e.head().ID()==head && e.tail().ID()==tail) {
				temp.add(e);
			}
		}
		Comparator<Edge<U,T>> compareWeight=(Edge<U,T> e1, Edge<U,T> e2)->((Float)e1.weight()).compareTo((Float)e2.weight());
		Collections.sort(temp, compareWeight);
		return temp;
	}
	
	
	/**
	 * @param head String value representing the name of the head node of the desired Edge(s)
	 * @param tail String value representing the name of the tail node of the desired Edge(s)
	 * @return LinkedList of all Edges that connect head to tail sorted by weight
	 */
	public LinkedList<Edge<U,T>> findEdges(T head, T tail) {
		LinkedList<Edge<U,T>> temp=new LinkedList<Edge<U,T>>();
		for(Edge<U,T> e: this.E) {
			if(head.compareTo(e.head().name())==0 && tail.compareTo(e.tail().name())==0) {
				temp.add(e);
			}
		}
		Comparator<Edge<U,T>> compareWeight=(Edge<U,T> e1, Edge<U,T> e2)->((Float)e1.weight()).compareTo((Float)e2.weight());
		Collections.sort(temp, compareWeight);
		return temp;
	}
	

	public LinkedList<Edge<U,T>> findEdges(Node<T,U> head, Node<T,U> tail) {
		LinkedList<Edge<U,T>> temp=new LinkedList<Edge<U,T>>();
		for(Edge<U,T> e: this.E) {
			if(e.head().compareName(head)==0 && e.tail().compareName(tail)==0) {
				temp.add(e);
			}
		}
		Comparator<Edge<U,T>> compareByName=(Edge<U,T> o1, Edge<U,T> o2)->o1.compareName(o2);
		Collections.sort(temp,  compareByName);
		return temp;
	}
	
	
	/**
	 * @param n Node that starts all shortest paths
	 * @requires n!=null, n in this Graph
	 * @return Array of integers with distances from n calculated by edge weights in the path
	 */
	public float[] ShortestDistances(Node<T,U> n) {
		float[] distance=new float[this.N.size()];
		for(int i=0; i<distance.length; i++) {
			distance[i]=Integer.MAX_VALUE;
		}
		distance[n.ID()-1]=0;
		LinkedList<Node<T,U>> queue=new LinkedList<Node<T,U>>();
		queue.add(n);
		while(queue.size()>0) {
			Node<T,U> v=queue.removeFirst();
			for(Edge<U,T> e:this.E) {
				if(e.head().compareName(v)==0) {
					if(distance[v.ID()-1]+e.weight()<distance[e.tail().ID()-1]) {
						distance[e.tail().ID()-1]=distance[v.ID()-1]+e.weight();
						queue.add(e.tail());
					}
				}
			}
		}
		return distance;
	}
	
	
	/**
	 * Prints the return value from ShortestDistances (Dijkstra's) from Node n
	 * @param n name of starting Node
	 * @throws RuntimeException if n not in this Graph
	*/
	public String dijkstraString(T n) {
		Node<T,U> v=this.retrieveNode(n);
		if(v==null) {throw new RuntimeException("Error: The Node with ID "+n+" does not exist in this Graph");}
		else {
			StringBuilder output=new StringBuilder();
			float[] runner=this.ShortestDistances(this.retrieveNode(n));
			for(int i=0; i<runner.length; i++) {
				if(runner[i]==0) {
					output.append("From Node "+n+" ("+(i+1)+"):\n");
					break;
				}
			}
			for(int i=0; i<runner.length; i++) {
				if(runner[i]!=0) {
					Node<T,U> u=this.retrieveNodeID(i+1);
					output.append("Node "+u.name()+" ("+(i+1)+"): "+runner[i]);
					if(i<runner.length-1) {output.append("\n");}
				}
			}
			return output.toString();
		}
	}

	
	/**
	 * This function is designed to help the maxFlow function
	 * 
	 * @param s Node that starts the BFS
	 * @param t Node that ends the BFS
	 * @param repGraph float[][] that tracks weights between two Nodes
	 * @requires s,t in this.N
	 * @returns Node[] containing the parents of each node in the s,t-path. If no parent, then null.
	 */
	private Map<Node<T,U>,Node<T,U>> helperBFS(Node<T,U> s, Node<T,U> t, float[][] repGraph) {
			Map<Node<T,U>, Node<T,U>> parent=new HashMap<Node<T,U>, Node<T,U>>();
			boolean[] visited=new boolean[this.size];
			for(int i=0; i<this.size; i++) {
				visited[i]=false;
			}
			
			LinkedList<Node<T,U>> queue=new LinkedList<Node<T,U>>();
			queue.add(s);
			parent.put(s, null);
			while(queue.size()>0) {
				s=queue.removeFirst();
				visited[s.ID()-1]=true;
				for(Node<T,U> n:s.outNeighborhood()) {
					if(visited[n.ID()-1]==false && repGraph[s.ID()-1][n.ID()-1]>0) {
						queue.add(n);
						parent.put(n,s);
					}
				}
			}

			return parent;
	}

	
	/**
	 * @param s Node at the beginning of the search
	 * @param t Node at the end of the search
	 * @requires s,t in this.N
	 * @return the maximum amount of "information" that can be pushed from s to t; i.e. the max flow from s to t
	 */
	public float maxFlow(Node<T,U> s, Node<T,U> t) {
		//Gross abuse of memory
		float[][] flows=new float[this.N.size()][this.N.size()];
		for(int i=0;i<flows.length;i++) {
			for(int j=0;j<flows[i].length;j++) {
				flows[i][j]=0;
			}
		}
		//Set the capacities of each edge. If multiple edges exist between edges, take the maximum weight
		for(Edge<U,T> e:E) {
			flows[e.head().ID()-1][e.tail().ID()-1]=Math.max(e.weight(), flows[e.head().ID()-1][e.tail().ID()-1]);
		}
		
		Map<Node<T,U>,Node<T,U>> parent=this.helperBFS(s, t, flows);
		Node<T,U> u,v;
		float max_flow=0;
		while(parent.get(t)!=null) {
			float path_flow=Integer.MAX_VALUE;
			for(v=t; v.compareTo(s)!=0; v=parent.get(v)) {
				u=parent.get(v);
				path_flow=Math.min(path_flow, flows[u.ID()-1][v.ID()-1]);
			}
			for(v=t; v.compareTo(s)!=0; v=parent.get(v)) {
				u=parent.get(v);
				flows[u.ID()-1][v.ID()-1]-=path_flow;
				flows[v.ID()-1][u.ID()-1]+=path_flow;
			}
			max_flow+=path_flow;
			parent=this.helperBFS(s, t, flows);
		}
		return max_flow;
	}

	
	/**
	 * @return int[][] representing the Adjacency matrix, with the indices being the ID-1 of each Node
	 */
	public int[][] adjacencyMatrix(){
		int[][] A=new int[this.size][];
		for(int i=0; i<this.size; i++) {
			A[i]=new int[this.size];
			for(int j=0; j<this.size; j++) {
				A[i][j]=0;
			}
		}
		for(Node<T,U> u: this.N) {
			for(Node<T,U> v: u.outNeighborhood()) {
				if(A[u.ID()-1][v.ID()-1]==0) { //Catch repeated Nodes
					for(Edge<U,T> e: this.findEdgesID(u.ID(), v.ID())) {
						A[u.ID()-1][v.ID()-1]+=e.weight();
					}
				}
			}
		}
		return A;
	}
	
	/**
	 * <b>Note</b> avoids self-loops
	 * @return int[][] representing the Adjacency matrix, with the indices being the ID-1 of each Node
	 */
	public int[][] simpleAdjacencyMatrix() {
		int[][] A=new int[this.size][];
		for(int i=0; i<this.size; i++) {
			A[i]=new int[this.size];
			for(int j=0; j<this.size; j++) {
				A[i][j]=0;
			}
		}
		for(Node<T,U> u: this.N) {
			for(Node<T,U> v: u.outNeighborhood()) {
				if(v.compareTo(u)!=0 && A[u.ID()-1][v.ID()-1]==0) { //Catch self-loops and repeated Nodes
					for(Edge<U,T> e: this.findEdgesID(u.ID(), v.ID())) {
						A[u.ID()-1][v.ID()-1]+=e.weight();
					}
				}
			}
		}
		return A;
	}
	
	
	/**
	 * @return double[][] representing the inverse Diagonal matrix
	 */
	public double[][] diagonalMatrix(){
		double[][] D=new double[this.size][this.size];
		for(int i=0; i<this.size; i++) {
			for(int j=0; j<this.size; j++) {
				D[i][j]=0;
			}
		}
		for(Node<T,U> u: this.N) {
			int sum=0;
			for(Node<T,U> v: this.N) {
				LinkedList<Edge<U,T>> edges=this.findEdgesID(u.ID(), v.ID());
				for(Edge<U,T> e:edges) {
					sum+=e.weight();
				}
			}
			if(sum!=0) {
				D[u.ID()-1][u.ID()-1]=(double)1/sum;
			}
			else {
				D[u.ID()-1][u.ID()-1]=0;
			}
		}
		return D;
	}
	
	
	/**
	 * <b>Note</b> avoids self-loops
	 * @return double[][] representing the inverse Diagonal matrix of this Graph
	 */
	public double[][] simpleDiagonalMatrix(){
		double[][] D=new double[this.size][this.size];
		for(int i=0; i<this.size; i++) {
			for(int j=0; j<this.size; j++) {
				D[i][j]=0;
			}
		}
		for(Node<T,U> u: this.N) {
			int sum=0;
			for(Node<T,U> v: this.N) {
				if(u.ID()!=v.ID()) {//Avoid self-loops
					LinkedList<Edge<U,T>> edges=this.findEdgesID(u.ID(), v.ID());
					if(edges.size()>0) {
						for(Edge<U,T> e:edges) {
							sum+=e.weight();
						}
					}
				}
			}
			if(sum!=0) {
				D[u.ID()-1][u.ID()-1]=(double)1/sum;
			}
			else {
				D[u.ID()-1][u.ID()-1]=0;
			}
		}
		return D;
	}
	
	
	/**
	 * @return double[][] representing the Transition Probability Matrix
	 */
	public double[][] TPM(){
		int[][] A=this.adjacencyMatrix();
		double[][] D=this.diagonalMatrix();
		double[][] TPM=new double[this.size][this.size];
		for(int i=0; i<this.size; i++) {
			for(int j=0; j<this.size; j++) {
				TPM[i][j]=0;
				for(int k=0; k<this.size; k++) {
					TPM[i][j]+=A[i][k]*D[k][j];
				}
			}
		}
		for(int i=0; i<this.size; i++) {
			for(int j=i; j<this.size; j++) {
				if(i!=j) {
					double temp=TPM[i][j];
					TPM[i][j]=TPM[j][i];
					TPM[j][i]=temp;
				}
			}
		}
		return TPM;
	}
	
	
	/**
	 * <b>Note</b> avoids self-loops
	 * @return double[][] representing the Transition Probability Matrix of this Graph
	 */
	public double[][] simpleTPM(){
		int[][] A=this.simpleAdjacencyMatrix();
		double[][] D=this.simpleDiagonalMatrix();
		double[][] TPM=new double[this.size][this.size];
		for(int i=0; i<this.size; i++) {
			for(int j=0; j<this.size; j++) {
				TPM[i][j]=0;
				for(int k=0; k<this.size; k++) {
					TPM[i][j]+=A[i][k]*D[k][j];
				}
			}
		}
		for(int i=0; i<this.size; i++) {
			for(int j=i; j<this.size; j++) {
				double temp=TPM[i][j];
				TPM[i][j]=TPM[j][i];
				TPM[j][i]=temp;
			}
		}
		return TPM;
	}
	
	
	/**
	 * Returns the PageRank of each node as an array stored by the Node's ID - 1 (e.g. if node.ID==2, it will be in index 1)
	 * <b>NOTE</b>: This algorithm ignores self-loops
	 * 
	 * @param n Number of iterations of PageRank calculation
	 * @requires n>=0
	 * @return double[] Probability of success based on PageRank rules
	 */
	public double[] PageRank(int n) {
		double[][] TPM=this.simpleTPM();
		double[] PR=new double[this.size];
		for(int i=0; i<this.size; i++) {
			PR[i]=(double)1/this.size;
		}
		for(int i=0; i<n; i++) {
			double[] temp=new double[this.size];
			for(int j=0; j<this.size; j++) {temp[j]=PR[j]; PR[j]=0;}
			for(int j=0; j<this.size; j++) {
				for(int k=0; k<this.size; k++) {
					PR[j]+=TPM[j][k]*temp[k];
				}
			}
		}
		return PR;
	}
	
	
	/**
	 * Returns a String representation of this Graph
	 * 
	 * @modifies this.N, this.E
	 * @effects sorts this.N by Node.ID(), sorts this.E by Edge.head().ID() 
	 * @returns A String representation of this Graph, with nodes sorted by ID and with edges sorted by head ID
	 * 
	 * 		Format:
	 * 		Data for Graph: this.ID
	 * 		Size: this.size
	 * 		Edges:
	 * 		edge.head->edge.tail (edge.weight)
	 * 		for edge in this.E
	 */
	@Override
	public String toString() {
		StringBuilder output=new StringBuilder();
		output.append("Data for Graph: "+this.ID+"\n");
		output.append("Size: "+this.size+"\n");
		if(this.size()>0) {
			output.append("Nodes: ");
			Collections.sort(this.N, Comparator.comparingInt(obj->obj.ID()));
			int counter=0;
			for(Node<T,U> n: this.N) {
				output.append(n.ID());
				counter++;
				if(counter!=this.size()) {
					output.append(", ");
				}
			}
			counter=0;
			if(this.E.size()>0) {
				output.append("\n");
				Collections.sort(this.E, Comparator.comparingInt(obj->obj.head().ID()));
				for(Edge<U,T> e: this.E) {
					output.append(e.toString());
					counter++;
					if(counter!=this.E.size()) {
						output.append("\n");
					}
				}
			}
		}
		return output.toString();
	}
	
	
	/**
	 * @param other The Graph to be compared to
	 * @requires other!=null
	 * @return 1 if this.size>other.size
	 * 				this.size==other.size && sum(a.compareTo(b) forall a in this.N, b in other.N)>0
	 * 				this.size==other.size && sum(a.compareTo(b) forall a in this.N, b in other.N)==0 && sum(a.compareTo(b) forall a in this.E, b in other.E)>0
	 * 				this.size==other.size && sum(a.compareTo(b) forall a in this.N, b in other.N)==0 && sum(a.compareTo(b) forall a in this.E, b in other.E)==0 && this.ID>other.ID
	 * @return 0 if this.size==other.size && sum(a.compareTo(b) forall a in this.N, b in other.N)==0 && sum(a.compareTo(b) forall a in this.E, b in other.E)==0 && this.ID==other.ID
	 * @return -1 otherwise
	 */
	public int compareTo(Graph<T,U> other) {
		int sizeCompare=this.size-other.size();
		if(sizeCompare>0) {
			return 1;
		} else if(sizeCompare==0) {
			int thisEdgeSum=0;
			int otherEdgeSum=0;
			LinkedList<Edge<U,T>> thisOne=this.E();
			LinkedList<Edge<U,T>> otherOne=other.E();
			for(int i=0; i<thisOne.size() || i<otherOne.size(); i++) {
				if(i<thisOne.size()) {
					thisEdgeSum+= thisOne.get(i).weight();
				}
				if(i<otherOne.size()) {
					otherEdgeSum+=otherOne.get(i).weight();
				}
			}
			if(thisEdgeSum>otherEdgeSum) {
				return 1;
			} else if(thisEdgeSum==otherEdgeSum) {
				int IDCompare=this.ID.compareTo(other.ID());
				if(IDCompare>0){
					return 1;
				} else if(IDCompare==0) {
					return 0;
				}
				
			}
		}
		return -1;
	}
	
	
	/**
	 * @throws RuntimeException if RepInvar is violated
	 */
	/*Never gets called
	private void checkRep() throws RuntimeException{
		Node[] test=this.N();
		for(int i=0; i<test.length-1;i++){
			if(test[i].hashCode()==test[i+1].hashCode()) {
				throw new RuntimeException("Error: Graph " + this.ID+" has a duplicate Node");
			}
		}
		if(N.size()==0 && E.size()!=0) {
			throw new RuntimeException("Error: Graph "+this.ID+" has Edges but no Nodes");
		}
	}
	*/
}
