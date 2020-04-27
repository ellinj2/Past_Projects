package hw4;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.Rule;

public class EdgeTest {

	@Test
	public void testConstructor() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Node<String,String> three=new Node<String,String>("3",g);
		new Edge<String,String>(one,two, 3,"e1");
		new Edge<String,String>(three, one, 5,"e2");
		new Edge<String,String>(three, three, 2,"e3");
	}
	
	@Test
	public void testHeadsTails() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);	
		Edge<String,String> e1=new Edge<String,String>(one,two, 3,"e1");
		assertEquals(0, e1.head().compareTo(one));
		assertEquals(0, e1.tail().compareTo(two));
	}

	@Test
	public void testWeight() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two, 3,"e1");
		assertEquals(3, e1.weight(),0.001);
	}
	
	@Test
	public void testCompareTo() {
		assertEquals(1, (new Edge<String,String>(new Node<String,String>("1"), new Node<String,String>("1"), 1, "e1").compareTo(new Edge<String,String>(new Node<String,String>("1"), new Node<String,String>("1"), 1, "e0"))));
		assertEquals(-1, (new Edge<String,String>(new Node<String,String>("1"), new Node<String,String>("1"), 1, "e1").compareTo(new Edge<String,String>(new Node<String,String>("1"), new Node<String,String>("1"), 1, "e2"))));
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1",g);
		Node<String,String> n2=new Node<String,String>("2",g);
		Node<String,String> n3=new Node<String,String>("3",g);
		Edge<String,String> e1=new Edge<String,String>(n1,n2,2,"e1");
		Edge<String,String> e2=new Edge<String,String>(n2,n1,2,"e2");
		assertEquals(1,e2.compareTo(e1));
		assertEquals(0,e1.compareTo(e1));
		assertEquals(-1,e1.compareTo(e2));
		Edge<String,String> e3=new Edge<String,String>(n1,n1,2,"e3");
		assertEquals(1,e3.compareTo(e1));
		assertEquals(-1,e1.compareTo(e3));
		Edge<String,String> e4=new Edge<String,String>(n1,n2,1,"e4");
		assertEquals(-1,e1.compareTo(e4));
		assertEquals(1,e4.compareTo(e1));
		assertEquals(0,e1.compareTo(e1));
		Edge<String,String> t1=new Edge<String,String>(n1, n2, 1, "t");
		Edge<String,String> t2=new Edge<String,String>(n2, n1, 1, "t");
		Edge<String,String> t3=new Edge<String,String>(n1, n3, 1, "t");
		Edge<String,String> t4=new Edge<String,String>(n1,n2,2,"t");
		assertEquals(-1, t1.compareTo(t2));
		assertEquals(1, t2.compareTo(t1));
		assertEquals(-1, t1.compareTo(t3));
		assertEquals(1, t3.compareTo(t1));
		assertEquals(1,t4.compareTo(t1));
		assertEquals(-1,t1.compareTo(t4));
		assertEquals(0,t1.compareTo(new Edge<String,String>(n1,n2,1,"t")));
	}
	
	@Test
	public void testString() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two,1,"e1");
		assertEquals("1-e1->2 (1.0)",e1.toString());
	}
	
	// Used for local testing only
	/*
	@Rule
	public ExpectedException exceptionRule=ExpectedException.none();
	
	
	@Test
	public void testCheckRepNullHead() {
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: Edge<String,String>s cannot connect null Node<String,String>s");
		new Edge<String,String>(null, new Node<String,String>("1"), 1,"e1");
	}
	
	@Test
	public void testCheckRepNullTail() {
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: Edge<String,String>s cannot connect null Node<String,String>s");
		new Edge<String,String>(new Node<String,String>("1"), null, 1,"e1");
	}
	
	@Test
	public void testCheckRepNullHeadParent() {
		Node<String,String> one=new Node<String,String>("1");
		Graph<String,String> g=new Graph<String,String>("Test");
		g.addNode(new Node<String,String>("1"));
		Node<String,String> two=new Node<String,String>("2",g);
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: head and tail are not in the same Graph<String,String>");
		new Edge<String,String>(one,two,1,"e1");
	}
	
	@Test
	public void testCheckRepNullTailParent() {
		Node<String,String> one=new Node<String,String>("1");
		Graph<String,String> g=new Graph<String,String>("Test");
		g.addNode(new Node<String,String>("1"));
		Node<String,String> two=new Node<String,String>("2",g);
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: head and tail are not in the same Graph<String,String>");
		new Edge<String,String>(two,one,1,"e1");
	}
	
	@Test
	public void testMisMatchParent() {
		Node<String,String> one=new Node<String,String>("1",new Graph<String,String>("A"));
		Node<String,String> two=new Node<String,String>("1", new Graph<String,String>("B"));
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: head and tail are not in the same Graph<String,String>");
		new Edge<String,String>(one,two,1,"e1");
	}
	*/
}
