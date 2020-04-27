package hw7;

import hw4.*;
import java.util.*;


//View
public class PathDisplay{
	private PathWay campus;
	
	public PathDisplay(PathWay p) {
		this.campus=p;
	}
	
	/*
	public void displayText(String s) {
		System.out.println(s);
	}
	*/
	
	public String listNodes() {
		String name;
		int ID;
		StringBuilder output=new StringBuilder();
		for(Node<String,Float> n:this.campus.listNodes()) {
			if(n.name().contains("Intersection")) {
				continue;
			} else {name=n.name();}
			ID=n.ID();
			output.append(name+","+ID+"\n");
		}
		return output.toString();
	}
	
	public String findPath(Object start, Object end) {
		Node<String,Float> head=this.campus.findNode(start);
		Node<String,Float> tail=this.campus.findNode(end);
		boolean dead=false;
		
		StringBuilder output=new StringBuilder();
		if(head==null || head.name().contains("Intersection")) {
			output.append("Unknown building: ["+start+"]\n");
			dead=true;
		}
		if((tail==null || tail.name().contains("Intersection")) && !start.equals(end)) {
			output.append("Unknown building: ["+end+"]\n");
			dead=true;
		}
		if(dead) {
			return output.toString();
		}
		
		if(start.equals(end)) {
			output.append("Path from "+head.name()+" to "+tail.name()+":\nTotal distance: 0.000 pixel units.\n");
			return output.toString();
		}
		
		Map<Node<String,Float>,Edge<Float,String>> result=this.campus.Dijkstra(head,tail);
		Edge<Float,String> e=result.get(tail);
		if(e==null) {
			output.append("There is no path from "+head.name()+" to "+tail.name()+".\n");
			return output.toString();
		}
		float totalCost=0;
		//Build path from end to start
		LinkedList<Edge<Float,String>> path=new LinkedList<Edge<Float,String>>();
		while(e!=null) {
			totalCost+=e.weight();
			path.add(e);
			e=result.get(e.head());
		}
		//Print path
		output.append("Path from "+head.name()+" to "+tail.name()+":\n");
		while(path.size()>0) {
			e=path.removeLast();
			output.append("\tWalk "+this.campus.EdgeDirection(e)+" to ("+e.tail().name()+")\n");
		}
		output.append("Total distance: "+String.format("%.3f",totalCost)+" pixel units.\n");
		return output.toString();
	}
	
	
}
