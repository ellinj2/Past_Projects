package hw4;

import static org.junit.Assert.*;
import org.junit.Test;

import java.util.Iterator;
import java.util.Collections;

public class GraphWrapperTest{
	
	@Test
	public void testConstructor() {
		GraphWrapper gw=new GraphWrapper();
		assertEquals(0, gw.graph.ID().compareTo("Tester"));
		assertEquals(0, gw.graph.size());
	}
	
	@Test
	public void testAddNode() {
		GraphWrapper gw=new GraphWrapper();
		gw.addNode("Node 1");
		assertEquals(1, gw.graph.size());
	}
	
	@Test
	public void testAddEdge() {
		GraphWrapper gw=new GraphWrapper();
		gw.addNode("a");
		gw.addNode("b");
		gw.addEdge("a", "b", "e1");
		Edge<String,String> retVal=gw.graph.retrieveEdge("a", "b", 1, "e1");
		assertEquals("a", retVal.head().name());
		assertEquals("b", retVal.tail().name());
		assertEquals("e1", retVal.name());
		assertEquals(1, retVal.weight(),0.001);
	}
	
	@Test
	public void testListNodes() {
		GraphWrapper gw=new GraphWrapper();
		assertEquals(Collections.emptyIterator(), gw.listNodes());
		gw.addNode("This");
		gw.addNode("is");
		gw.addNode("a");
		gw.addNode("test");
		Iterator<String> retVal=gw.listNodes();
		assertEquals("This", retVal.next());
		assertEquals("a", retVal.next());
		assertEquals("is", retVal.next());
		assertEquals("test", retVal.next());
		assertEquals(false, retVal.hasNext());
	}
	
	@Test
	public void testListChildren() {
		GraphWrapper gw=new GraphWrapper();
		gw.addNode("1");
		Iterator<String> test=gw.listChildren("1");
		assertFalse(test.hasNext());
		test=gw.listChildren("DeadNode");
		assertFalse(test.hasNext());
		gw.addNode("2");
		gw.addNode("3");
		gw.addEdge("1", "2", "e1");
		gw.addEdge("1", "3", "e2");
		gw.addEdge("1", "1", "e3");
		gw.addEdge("1", "2", "e4");
		Iterator<String> retVal=gw.listChildren("1");
		assertEquals("1(e3)", retVal.next());
		assertEquals("2(e1)", retVal.next());
		assertEquals("2(e4)", retVal.next());
		assertEquals("3(e2)", retVal.next());
		assertEquals(false, retVal.hasNext());
	}
	
	
}

