package hw4;

import static org.junit.Assert.*;
import java.util.*;

import org.junit.Test;

public class NodeTest {

	//Some generic values for placeholders
	private Graph<String,String> g=new Graph<String,String>("Tester");
	Node<String,String> one=new Node<String,String>("1",g);
	Node<String,String> two=new Node<String,String>("2",g);
	Node<String,String> three=new Node<String,String>("3",g);
	Node<String,String> four=new Node<String,String>("4",g);
	Node<String,String> five=new Node<String,String>("5",g);

	@Test
	public void testTwoArgConstructor() {
		Graph<String,String> G=new Graph<String,String>("Runner");
		new Node<String,String>("1",G);
		new Node<String,String>("2",G);
		new Node<String,String>("3",G);
	}
	
	@Test
	public void testEquals() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		assertEquals(0, one.compareTo(new Node<String,String>("1", new Graph<String,String>("b"))));
		assertEquals(1, (new Node<String,String>("2",g)).compareTo(one));
		Graph<String,String> test=new Graph<String,String>("b");
		test.addNode(new Node<String,String>("1"));
		test.addNode(new Node<String,String>("2"));
		assertEquals(-1, (new Node<String,String>("2", new Graph<String,String>("a")).compareTo(new Node<String,String>("3", test))));
	}
	
	@Test
	public void testAdding() {
		Graph<String,String> home=new Graph<String,String>("Root");
		Node<String,String> t1=new Node<String,String>("1",home);
		Node<String,String> t2=new Node<String,String>("2",home);
		Node<String,String> t3=new Node<String,String>("3",home);
		t1.addIn(t2);
		t2.addIn(t3);
		t1.addOut(t3);
		t2.addOut(t2);
	}
	
	@Test
	public void testDegree() {
		Graph<String,String> n=new Graph<String,String>("");
		Node<String,String> a=new Node<String,String>("1",n);
		Node<String,String> b=new Node<String,String>("2",n);
		a.addOut(b);
		assertEquals(1,a.outDegree());
		assertEquals(1,b.inDegree());
		assertEquals(0,a.inDegree());
		assertEquals(0,b.outDegree());
	}
	
	@Test
	public void testID() {
		assertEquals(1, (new Node<String,String>("Test",new Graph<String,String>("Trash"))).ID());
	}
	
	@Test
	public void testName() {
		assertEquals("Alpha", (new Node<String,String>("Alpha")).name());
	}
	
	@Test
	public void testInNeighborhood() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Node<String,String> three=new Node<String,String>("3",g);
		one.addIn(two);
		one.addIn(three);
		LinkedList<Node<String,String>> test=one.inNeighborhood();
		LinkedList<Node<String,String>> check=new LinkedList<Node<String,String>>();
		check.add(two); check.add(three);
		for(int i=0; i<2; i++) {
			assertEquals(0,test.get(i).compareTo(check.get(i)));
		}
	}
	
	@Test
	public void testOutNeighborhood() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Node<String,String> three=new Node<String,String>("3",g);
		one.addOut(two);
		one.addOut(three);
		LinkedList<Node<String,String>> test=one.outNeighborhood();
		LinkedList<Node<String,String>> check=new LinkedList<Node<String,String>>();
		check.add(two); check.add(three);
		for(int i=0; i<2; i++) {
			assertEquals(0,test.get(i).compareTo(check.get(i)));
		}
	}
	
	@Test
	public void testHashCode() {
		Node<String,String> one=new Node<String,String>("1");
		assertEquals("1".hashCode(),one.hashCode());
		one=new Node<String,String>("1", new Graph<String,String>("Test"));
		assertEquals("1".hashCode(),one.hashCode());
	}
	
	@Test
	public void testString() {
		Node<String,String> scrap=new Node<String,String>("Loner");
		assertEquals("Data from Node: Loner", scrap.toString());
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		assertEquals("Data from Node: 1, Node #1 in Graph: Test", one.toString());
		Node<String,String> two=new Node<String,String>("2",g);
		one.addOut(two);
		assertEquals("Data from Node: 1, Node #1 in Graph: Test\nOut Degree: 1\nOut Neighborhood: 2",one.toString());
		assertEquals("Data from Node: 2, Node #2 in Graph: Test\nIn Degree: 1\nIn Neighborhood: 1", two.toString());
		Node<String,String> three=new Node<String,String>("3",g);
		one.addOut(three);
		two.addIn(three);
		assertEquals("Data from Node: 1, Node #1 in Graph: Test\nOut Degree: 2\nOut Neighborhood: 2, 3",one.toString());
		assertEquals("Data from Node: 2, Node #2 in Graph: Test\nIn Degree: 2\nIn Neighborhood: 1, 3", two.toString());
	}
	
	@Test
	public void testParent() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1", g);
		assertEquals(0, g.compareTo(one.parent()));
	}
	
}
