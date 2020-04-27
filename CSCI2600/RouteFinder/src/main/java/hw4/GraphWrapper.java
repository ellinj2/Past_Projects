package hw4;

import java.util.Iterator;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;

public class GraphWrapper{
	public Graph<String,String> graph;
	
	public GraphWrapper() {
		graph=new Graph<String,String>("Tester");
	}
	
	public void addNode(String nodeData) {
		graph.addNode(new Node<String,String>(nodeData));
	}
	
	public void addEdge(String parentNode, String childNode, String edgeLabel) {
		Node<String,String> n1=graph.retrieveNode(parentNode);
		Node<String,String> n2=graph.retrieveNode(childNode);
		graph.addEdge(new Edge<String,String>(n1,n2,1,edgeLabel));
	}
		
	public Iterator<String> listNodes(){
		LinkedList<Node<String,String>> nodes=graph.N();
		if(nodes.size()==0) {return Collections.emptyIterator();}
		String[] names=new String[nodes.size()];
		for(int i=0; i<nodes.size(); i++) {
			names[i]=nodes.get(i).name();
		}
		return Arrays.stream(names).iterator();
	}
	
	public Iterator<String> listChildren(String parentNode){
		Node<String,String> n1=graph.retrieveNode(parentNode);
		if(n1==null) {return Collections.emptyIterator();}
		LinkedList<Node<String,String>> children=n1.outNeighborhood();
		LinkedList<String> names=new LinkedList<String>();
		for(int i=0; i<children.size(); i++) {
			if(i>0 && children.get(i).name().compareTo(children.get(i-1).name())==0) {continue;}
			LinkedList<Edge<String,String>> edges=graph.findEdges(parentNode, children.get(i).name());
			Comparator<Edge<String,String>> byName=(Edge<String,String> e1, Edge<String,String> e2)->e1.compareName(e2);
			Collections.sort(edges, byName);
			for(Edge<String,String> e:edges) {
				names.add(new String(children.get(i).name()+"("+e.name()+")"));
			}
		}
		return names.listIterator();
	}
}




