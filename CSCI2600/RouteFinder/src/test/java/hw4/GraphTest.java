package hw4;

import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.LinkedList;

import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.Rule;

public class GraphTest {

	@Test
	public void testOneArgConstructor() {
		new Graph<String,String>("This");
		new Graph<String,String>("Is");
		new Graph<String,String>("A");
		new Graph<String,String>("Test");
	}

	@Test
	public void testThreeArgConstructor() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Node<String,String> three=new Node<String,String>("3",g);
		LinkedList<Node<String,String>> ns=new LinkedList<Node<String,String>>(Arrays.asList(one,two,three));
		LinkedList<Edge<String,String>> es=new LinkedList<Edge<String,String>>(Arrays.asList(new Edge<String,String>(one,two,1,"e1"), new Edge<String,String>(one, three, 4,"e2"), new Edge<String,String>(three, two, 7,"e3")));
		new Graph<String,String>("Tester",ns,es);
	}
	
	@Test
	public void testRetrieveNode() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		assertEquals(0,g.retrieveNode("1").compareTo(one));
		Node<String,String> two=new Node<String,String>("B",g);
		assertEquals(0, g.retrieveNodeID(2).compareTo(two));
		assertEquals(null, g.retrieveNode("EmptyNode<String,String>"));
		assertEquals(null, g.retrieveNodeID(6));
	}
	
	@Test
	public void testRetrieveEdge() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two,3,"e1");
		g.addEdge(e1);
		assertEquals(0, e1.compareTo(g.retrieveEdge("1", "2", 3, "e1")));
	}
	
	@Test
	public void testaddNode() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> two=new Node<String,String>("2");
		g.addNode(two);
		assertEquals(two, g.retrieveNode("2"));
		assertEquals(null, g.retrieveNode("3"));
	}
	
	@Test
	public void testaddEdge() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two,1, "e1");
		g.addEdge(e1);
		assertEquals(0, e1.compareTo(g.retrieveEdge("1","2",1,"e1")));
		assertEquals(null,g.retrieveEdge("4", "1", 0, "e2"));
	}
	
	@Test
	public void testCompareTo() {
		Graph<String,String> g=new Graph<String,String>("Testa");
		Graph<String,String> h=new Graph<String,String>("Testb");
		assertEquals(1,h.compareTo(g));
		assertEquals(-1,g.compareTo(h));
		g.addNode(new Node<String,String>("1"));
		h.addNode(new Node<String,String>("1"));
		g.addNode(new Node<String,String>("2"));
		assertEquals(1, g.compareTo(h));
		h.addNode(new Node<String,String>("2"));
		assertEquals(-1,g.compareTo(h));
		g.addEdge(new Edge<String,String>(g.retrieveNode("1"),g.retrieveNode("2"),3, "e1"));
		h.addEdge(new Edge<String,String>(h.retrieveNode("1"),h.retrieveNode("2"),1, "e1"));
		assertEquals(1,g.compareTo(h));
		h.addEdge(new Edge<String,String>(h.retrieveNode("1"),h.retrieveNode("2"),4,"e2"));
		assertEquals(-1,g.compareTo(h));
		h.addEdge(new Edge<String,String>(h.retrieveNode("2"),h.retrieveNode("1"),7,"e3"));
		assertEquals(-1,g.compareTo(h));
		h.addNode(new Node<String,String>("3"));
		assertEquals(-1,g.compareTo(h));
		assertEquals(1,h.compareTo(g));
		Graph<String,String> a=new Graph<String,String>("Test");
		a.addNode(new Node<String,String>("1"));
		a.addNode(new Node<String,String>("2"));
		a.addNode(new Node<String,String>("3"));
		a.addNode(new Node<String,String>("4"));
		assertEquals(0, a.compareTo(a));
	}
	
	@Test
	public void testDijkstra() {
		Graph<String,String> g=new Graph<String,String>("Dijkstra Test");
		Node<String,String> one=new Node<String,String>("A",g);
		Node<String,String> two=new Node<String,String>("B",g);
		Node<String,String> three=new Node<String,String>("C",g);
		Node<String,String> four=new Node<String,String>("D",g);
		Node<String,String> five=new Node<String,String>("E",g);
		Node<String,String> six=new Node<String,String>("F",g);
		Node<String,String> seven=new Node<String,String>("G",g);
		g.addEdge(new Edge<String,String>(one,two,1,"e1"));
		g.addEdge(new Edge<String,String>(one,six,2,"e2"));
		g.addEdge(new Edge<String,String>(one,seven,7,"e3"));
		g.addEdge(new Edge<String,String>(two,three,2,"e4"));
		g.addEdge(new Edge<String,String>(six,five,1,"e5"));
		g.addEdge(new Edge<String,String>(six,seven,8,"e6"));
		g.addEdge(new Edge<String,String>(three,one,3,"e8"));
		g.addEdge(new Edge<String,String>(three,four,5,"e9"));
		g.addEdge(new Edge<String,String>(five,four,3,"e10"));
		g.addEdge(new Edge<String,String>(five,seven,1,"e11"));
		g.addEdge(new Edge<String,String>(seven,three,1,"e12"));
		g.addEdge(new Edge<String,String>(four,five,4,"e13"));
		float[] result=g.ShortestDistances(one);
		assertEquals((float)0,result[0], 0.0001);
		assertEquals(1, result[1], 0.0001);
		assertEquals(3, result[2],0.00001);
		assertEquals(6,result[3],0.0001);
		assertEquals(3,result[4],0.0001);
		assertEquals(2,result[5],0.0001);
		assertEquals(4,result[6],0.0001);
		String d1=g.dijkstraString("A");
		String d2=g.dijkstraString("B");
		assertEquals("From Node A (1):\nNode B (2): 1.0\nNode C (3): 3.0\nNode D (4): 6.0\nNode E (5): 3.0\nNode F (6): 2.0\nNode G (7): 4.0", d1);
		assertEquals("From Node B (2):\nNode A (1): 5.0\nNode C (3): 2.0\nNode D (4): 7.0\nNode E (5): 8.0\nNode F (6): 7.0\nNode G (7): 9.0", d2);
	}
	
	@Test
	public void testN() {
		Graph<String,String> g=new Graph<String,String>("Test");
		g.addNode(new Node<String,String>("3"));
		g.addNode(new Node<String,String>("1"));
		g.addNode(new Node<String,String>("2"));
		LinkedList<Node<String,String>> test=g.N();
		LinkedList<Node<String,String>> compare=new LinkedList<Node<String,String>>();
		compare.add(g.retrieveNode("1")); compare.add(g.retrieveNode("2")); compare.add(g.retrieveNode("3"));
		for(int i=0; i<3; i++) {
			assertEquals(0,test.get(i).compareTo(compare.get(i)));
		}
	}

	@Test
	public void testE() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two,1,"e1");
		Edge<String,String> e2=new Edge<String,String>(two,one,3,"e2");
		g.addEdge(e1);
		g.addEdge(e2);
		LinkedList<Edge<String,String>> test=g.E();
		assertEquals(0, test.get(0).compareTo(e1));
		assertEquals(0, test.get(1).compareTo(e2));
	}
	
	@Test
	public void testString() {
		Graph<String,String> g=new Graph<String,String>("Test");
		assertEquals("Data for Graph: Test\nSize: 0\n",g.toString());
		g.addNode(new Node<String,String>("1"));
		g.addNode(new Node<String,String>("2"));
		assertEquals("Data for Graph: Test\nSize: 2\nNodes: 1, 2",g.toString());
		g.addEdge(new Edge<String,String>(g.retrieveNode("1"),g.retrieveNode("2"),5,"e1"));
		g.addEdge(new Edge<String,String>(g.retrieveNode("2"),g.retrieveNode("1"),2,"e2"));
		assertEquals("Data for Graph: Test\nSize: 2\nNodes: 1, 2\n1-e1->2 (5.0)\n2-e2->1 (2.0)",g.toString());		
	}
	
	@Test
	public void testRemoveEdge() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e=new Edge<String,String>(one,two,3,"e1");
		g.addEdge(e);
		Edge<String,String> e2=new Edge<String,String>(two,one,2,"e2");
		g.addEdge(e2);
		g.removeEdge(e);
		assertEquals(e2, g.E().get(0));
	}
	
	@Test
	public void testFindEdges() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Edge<String,String> e1=new Edge<String,String>(one,two,1,"e1");
		Edge<String,String> e2=new Edge<String,String>(one,two,2,"e2");
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(new Edge<String,String>(one, new Node<String,String>("3",g), 5,"e3"));
		g.addEdge(new Edge<String,String>(new Node<String,String>("4",g), one, 3,"e4"));
		LinkedList<Edge<String,String>> res=g.findEdgesID(1, 2);
		assertEquals(res.get(0), e1);
		assertEquals(res.get(1),e2);
		LinkedList<Edge<String,String>> names=g.findEdges("1","2");
		assertEquals(names.get(0),e1);
		assertEquals(names.get(1),e2);
	}
	
	@Test
	public void testMaxFlow() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> one=new Node<String,String>("1",g);
		Node<String,String> two=new Node<String,String>("2",g);
		Node<String,String> three=new Node<String,String>("3",g);
		Node<String,String> four=new Node<String,String>("4",g);
		g.addEdge(new Edge<String,String>(one,two,1,"e1"));
		g.addEdge(new Edge<String,String>(one,three,2,"e2"));
		g.addEdge(new Edge<String,String>(two,four,2,"e3"));
		g.addEdge(new Edge<String,String>(three,four,1,"e4"));
		assertEquals(2,g.maxFlow(one, four),0.0001);
	}
	
	@Test
	public void testMassiveGraphFlow() {
		Graph<String,String> g=new Graph<String,String>("Test");
		LinkedList<Node<String,String>> s= new LinkedList<Node<String,String>>();
		for(int i=1; i<21; i++) {
			s.add(new Node<String,String>(Integer.toString(i),g));
		}
		g.addEdge(new Edge<String,String>(s.get(0),s.get(1),3,"e1"));
		g.addEdge(new Edge<String,String>(s.get(0),s.get(2),6,"e2"));
		g.addEdge(new Edge<String,String>(s.get(0),s.get(3),2,"e3"));
		g.addEdge(new Edge<String,String>(s.get(1),s.get(2),9,"e4"));
		g.addEdge(new Edge<String,String>(s.get(1),s.get(4),1,"e5"));
		g.addEdge(new Edge<String,String>(s.get(1),s.get(5),5,"e6"));
		g.addEdge(new Edge<String,String>(s.get(2),s.get(4),5,"e7"));
		g.addEdge(new Edge<String,String>(s.get(2),s.get(5),7,"e7"));
		g.addEdge(new Edge<String,String>(s.get(2),s.get(6),9,"e8"));
		g.addEdge(new Edge<String,String>(s.get(3),s.get(2),7,"e9"));
		g.addEdge(new Edge<String,String>(s.get(3),s.get(5),3,"e10"));
		g.addEdge(new Edge<String,String>(s.get(3),s.get(6),6,"e11"));
		g.addEdge(new Edge<String,String>(s.get(4),s.get(7),1,"e12"));
		g.addEdge(new Edge<String,String>(s.get(4),s.get(8),18,"e13"));
		g.addEdge(new Edge<String,String>(s.get(5),s.get(7),2,"e14"));
		g.addEdge(new Edge<String,String>(s.get(5),s.get(8),7,"e15"));
		g.addEdge(new Edge<String,String>(s.get(5),s.get(9),1,"e16"));
		g.addEdge(new Edge<String,String>(s.get(6),s.get(8),9,"e17"));
		g.addEdge(new Edge<String,String>(s.get(6),s.get(9),1,"e18"));
		g.addEdge(new Edge<String,String>(s.get(7),s.get(10),7,"e19"));
		g.addEdge(new Edge<String,String>(s.get(7),s.get(11),3,"e20"));
		g.addEdge(new Edge<String,String>(s.get(8),s.get(10),1,"e21"));
		g.addEdge(new Edge<String,String>(s.get(8),s.get(11),2,"e22"));
		g.addEdge(new Edge<String,String>(s.get(8),s.get(12),3,"e23"));
		g.addEdge(new Edge<String,String>(s.get(9),s.get(11),7,"e24"));
		g.addEdge(new Edge<String,String>(s.get(9),s.get(12),13,"e25"));
		g.addEdge(new Edge<String,String>(s.get(10),s.get(13),2,"e26"));
		g.addEdge(new Edge<String,String>(s.get(10),s.get(14),9,"e27"));
		g.addEdge(new Edge<String,String>(s.get(11),s.get(13),5,"e28"));
		g.addEdge(new Edge<String,String>(s.get(11),s.get(14),9,"e29"));
		g.addEdge(new Edge<String,String>(s.get(11),s.get(15),6,"e30"));
		g.addEdge(new Edge<String,String>(s.get(12),s.get(14),1,"e31"));
		g.addEdge(new Edge<String,String>(s.get(12),s.get(15),22,"e32"));
		g.addEdge(new Edge<String,String>(s.get(13),s.get(16),3,"e33"));
		g.addEdge(new Edge<String,String>(s.get(13),s.get(17),5,"e34"));
		g.addEdge(new Edge<String,String>(s.get(14),s.get(16),2,"e35"));
		g.addEdge(new Edge<String,String>(s.get(14),s.get(17),11,"e36"));
		g.addEdge(new Edge<String,String>(s.get(14),s.get(18),19,"e37"));
		g.addEdge(new Edge<String,String>(s.get(15),s.get(17),12,"e38"));
		g.addEdge(new Edge<String,String>(s.get(15),s.get(18),1,"e39"));
		g.addEdge(new Edge<String,String>(s.get(16),s.get(19),10,"e40"));
		g.addEdge(new Edge<String,String>(s.get(17),s.get(19),1,"e41"));
		g.addEdge(new Edge<String,String>(s.get(18),s.get(19),7,"e42"));
		float res=g.maxFlow(s.get(0), s.get(19));
		assertEquals(res,11,0.0001);
	}
	
	@Test
	public void testDiagonal() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1",g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Node<String,String> n4=new Node<String,String>("4", g);
		Edge<String,String> l1=new Edge<String,String>(n1,n1,2,"l1");
		Edge<String,String> e1=new Edge<String,String>(n1,n2,1,"e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,7,"e3");
		Edge<String,String> e3=new Edge<String,String>(n2,n3,4,"e3");
		Edge<String,String> e4=new Edge<String,String>(n2,n4,1,"e4");
		Edge<String,String> e5=new Edge<String,String>(n3,n1,2,"e5");
		Edge<String,String> e6=new Edge<String,String>(n3,n4,1,"e6");
		Edge<String,String> e7=new Edge<String,String>(n4,n3,3,"e7");
		Edge<String,String> l2=new Edge<String,String>(n4,n4,7,"l2");
		g.addEdge(l1);
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		g.addEdge(e5);
		g.addEdge(e6);
		g.addEdge(e7);
		g.addEdge(l2);
		double[][] D=g.diagonalMatrix();
		double[][] test=new double[4][4];
		test[0][0]=(double)1/10;
		test[0][1]=0;
		test[0][2]=0;
		test[0][3]=0;
		test[1][0]=0;
		test[1][1]=(double)1/5;
		test[1][2]=0;
		test[1][3]=0;
		test[2][0]=0;
		test[2][1]=0;
		test[2][2]=(double)1/3;
		test[2][3]=0;
		test[3][0]=0;
		test[3][1]=0;
		test[3][2]=0;
		test[3][3]=(double)1/10;
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				assertEquals(D[i][j], test[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testSimpleDiagonal() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1", g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Edge<String,String> e1=new Edge<String,String>(n1, n2, 3, "e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,1,"e2");
		Edge<String,String> e3=new Edge<String,String>(n2, n1, 4, "e3");
		Edge<String,String> e4=new Edge<String,String>(n2, n3, 8, "e4");
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		double[][] diag=g.simpleDiagonalMatrix();
		double[][] test=new double[3][3];
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				test[i][j]=0;
			}
		}
		test[0][0]=(double)1/4;
		test[1][1]=(double)1/12;
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				assertEquals(test[i][j], diag[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testAdjacency() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1",g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Node<String,String> n4=new Node<String,String>("4", g);
		Edge<String,String> l1=new Edge<String,String>(n1,n1,2,"l1");
		Edge<String,String> e1=new Edge<String,String>(n1,n2,1,"e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,7,"e3");
		Edge<String,String> e3=new Edge<String,String>(n2,n3,4,"e3");
		Edge<String,String> e4=new Edge<String,String>(n2,n4,1,"e4");
		Edge<String,String> e5=new Edge<String,String>(n3,n1,2,"e5");
		Edge<String,String> e6=new Edge<String,String>(n3,n4,1,"e6");
		Edge<String,String> e7=new Edge<String,String>(n4,n3,3,"e7");
		Edge<String,String> l2=new Edge<String,String>(n4,n4,7,"l2");
		g.addEdge(l1);
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		g.addEdge(e5);
		g.addEdge(e6);
		g.addEdge(e7);
		g.addEdge(l2);
		int[][] A=g.adjacencyMatrix();
		int[][] test=new int[4][4];
		test[0][0]=2;
		test[0][1]=1;
		test[0][2]=7;
		test[0][3]=0;
		test[1][0]=0;
		test[1][1]=0;
		test[1][2]=4;
		test[1][3]=1;
		test[2][0]=2;
		test[2][1]=0;
		test[2][2]=0;
		test[2][3]=1;
		test[3][0]=0;
		test[3][1]=0;
		test[3][2]=3;
		test[3][3]=7;
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				assertEquals(A[i][j], test[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testSimpleAdjacency() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1", g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Edge<String,String> e1=new Edge<String,String>(n1, n2, 3, "e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,1,"e2");
		Edge<String,String> e3=new Edge<String,String>(n2, n1, 4, "e3");
		Edge<String,String> e4=new Edge<String,String>(n2, n3, 8, "e4");
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		int[][] A=g.simpleAdjacencyMatrix();
		int[][] test=new int[3][3];
		for(int i=0; i<3; i++) {for(int j=0; j<3; j++) {test[i][j]=0;}}
		test[0][1]=3;
		test[0][2]=1;
		test[1][0]=4;
		test[1][2]=8;
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				assertEquals(test[i][j], A[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testTPM() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1",g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Node<String,String> n4=new Node<String,String>("4", g);
		Edge<String,String> l1=new Edge<String,String>(n1,n1,2,"l1");
		Edge<String,String> e1=new Edge<String,String>(n1,n2,1,"e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,7,"e3");
		Edge<String,String> e3=new Edge<String,String>(n2,n3,4,"e3");
		Edge<String,String> e4=new Edge<String,String>(n2,n4,1,"e4");
		Edge<String,String> e5=new Edge<String,String>(n3,n1,2,"e5");
		Edge<String,String> e6=new Edge<String,String>(n3,n4,1,"e6");
		Edge<String,String> e7=new Edge<String,String>(n4,n3,3,"e7");
		Edge<String,String> l2=new Edge<String,String>(n4,n4,7,"l2");
		g.addEdge(l1);
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		g.addEdge(e5);
		g.addEdge(e6);
		g.addEdge(e7);
		g.addEdge(l2);
		double[][] TPM=g.TPM();
		double[][] test=new double[4][4];
		test[0][0]=(double)1/5;
		test[0][1]=(double)0;
		test[0][2]=(double)1/5;
		test[0][3]=(double)0;
		test[1][0]=(double)1/5;
		test[1][1]=(double)0;
		test[1][2]=(double)0;
		test[1][3]=(double)0;
		test[2][0]=(double)7/3;
		test[2][1]=(double)4/3;
		test[2][2]=(double)0;
		test[2][3]=(double)1;
		test[3][0]=(double)0;
		test[3][1]=(double)1/10;
		test[3][2]=(double)1/10;
		test[3][3]=(double)7/10;
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				assertEquals(test[i][j], TPM[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testSimpleTPM() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1", g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Edge<String,String> e1=new Edge<String,String>(n1, n2, 3, "e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,1,"e2");
		Edge<String,String> e3=new Edge<String,String>(n2, n1, 4, "e3");
		Edge<String,String> e4=new Edge<String,String>(n2, n3, 8, "e4");
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		double[][] TPM=g.simpleTPM();
		double[][] test=new double[3][3];
		for(int i=0; i<3; i++) {for(int j=0; j<3; j++) {test[i][j]=0;}}
		test[0][1]=(double)1;
		test[1][0]=(double)1/4;
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				assertEquals(test[i][j], TPM[i][j], 0.0001);
			}
		}
	}
	
	@Test
	public void testPageRank() {
		Graph<String,String> g=new Graph<String,String>("Test");
		Node<String,String> n1=new Node<String,String>("1", g);
		Node<String,String> n2=new Node<String,String>("2", g);
		Node<String,String> n3=new Node<String,String>("3", g);
		Edge<String,String> e1=new Edge<String,String>(n1, n2, 3, "e1");
		Edge<String,String> e2=new Edge<String,String>(n1,n3,1,"e2");
		Edge<String,String> e3=new Edge<String,String>(n2, n1, 4, "e3");
		Edge<String,String> e4=new Edge<String,String>(n2, n3, 8, "e4");
		g.addEdge(e1);
		g.addEdge(e2);
		g.addEdge(e3);
		g.addEdge(e4);
		double[] PR=g.PageRank(0);
		for(int i=0; i<3; i++) {
			assertEquals((double)1/3, PR[i], 0.0001);
		}
		PR=g.PageRank(1);
		assertEquals((double)1/3, PR[0], 0.0001);
		assertEquals((double)1/12, PR[1], 0.0001);
		assertEquals((double)0, PR[2], 0.0001);
	}
	
	// Used for local testing only
	/*
	@Rule
	public ExpectedException exceptionRule=ExpectedException.none();
	
	@Test
	public void testCheckRepDup() {
		Graph<String,String> g=new Graph<String,String>("Test");
		g.addNode(new Node<String,String>("1"));
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: Graph<String,String> Test has a duplicate Node<String,String>");
		g.addNode(new Node<String,String>("1"));
	}
	
	@Test
	public void testCheckRepNodeless() {
		Graph<String,String> g=new Graph<String,String>("Test");
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: Graph<String,String> Test has Edge<String,String>s but no Node<String,String>s");
		g.addEdge(new Edge<String,String>(new Node<String,String>("1"), new Node<String,String>("2"), 2,"e1"));
	}
	
	@Test
	public void testDijkstraError() {
		Graph<String,String> g=new Graph<String,String>("Test");
		g.addNode(new Node<String,String>("1"));
		g.addNode(new Node<String,String>("2"));
		g.addNode(new Node<String,String>("3"));
		g.addEdge(new Edge<String,String>(g.retrieveNode("1"),g.retrieveNode("2"),3,"e1"));
		g.addEdge(new Edge<String,String>(g.retrieveNode("3"),g.retrieveNode("2"),1,"e2"));
		exceptionRule.expect(RuntimeException.class);
		exceptionRule.expectMessage("Error: The Node<String,String> with ID 4 does not exist in this Graph<String,String>");
		g.dijkstraString("4");
	}
	*/
}
