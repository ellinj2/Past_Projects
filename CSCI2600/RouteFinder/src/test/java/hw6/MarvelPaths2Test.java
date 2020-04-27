package hw6;

import org.junit.Test;
import static org.junit.Assert.*;


public class MarvelPaths2Test{

	//long startTime;
	//long endTime;
	
	Runtime rt=Runtime.getRuntime();
	
	@Test
	public void constructorTest(){
		//startTime=System.currentTimeMillis();
		MarvelPaths2 mp=new MarvelPaths2();
		mp.createNewGraph("data/marvel.csv");
		assertEquals(6444,mp.getSize("N"));
		assertEquals(1140216,mp.getSize("E"));
		
		MarvelPaths2 np=new MarvelPaths2();
		np.createNewGraph("data/TestRun.csv");
		assertEquals(26,np.getSize("N"));
		assertEquals(588,np.getSize("E"));
		assertEquals(0,np.getSize("V"));
		//endTime=System.currentTimeMillis();
		//System.out.println("ConstructorTest: "+(endTime-startTime));
	}
	
	@Test
	public void smallPathTest() {
		//startTime=System.currentTimeMillis();
		rt.gc();
		MarvelPaths2 field=new MarvelPaths2();
		field.createNewGraph("data/TestRun.csv");
		rt.gc();
		assertEquals(0,field.findPath("Alpha","Young").compareTo("path from Alpha to Young:\nAlpha to Beta with weight 1.000\nBeta to Young with weight 1.000\ntotal cost: 2.000\n"));
		//endTime=System.currentTimeMillis();
		//System.out.println("smallPathsTest: "+(endTime-startTime));
	}
	
	@Test
	public void longPathTest() {
		//startTime=System.currentTimeMillis();
		rt.gc();
		MarvelPaths2 mu=new MarvelPaths2();
		mu.createNewGraph("data/marvel.csv");
		rt.gc();
		assertEquals(0,mu.findPath("VISION ","SILVER SAMURAI/KENYU").compareTo("path from VISION  to SILVER SAMURAI/KENYU:\n" + 
				"VISION  to BEAST/HENRY &HANK& P with weight 0.007\n" + 
				"BEAST/HENRY &HANK& P to CYCLOPS/SCOTT SUMMER with weight 0.003\n" + 
				"CYCLOPS/SCOTT SUMMER to WOLVERINE/LOGAN  with weight 0.004\n" + 
				"WOLVERINE/LOGAN  to SILVER SAMURAI/KENYU with weight 0.083\n" + 
				"total cost: 0.097\n"));
		assertEquals(0,mu.findPath("SILVER SAMURAI/KENYU","VISION ").compareTo("path from SILVER SAMURAI/KENYU to VISION :\n" + 
				"SILVER SAMURAI/KENYU to WOLVERINE/LOGAN  with weight 0.083\n" + 
				"WOLVERINE/LOGAN  to CYCLOPS/SCOTT SUMMER with weight 0.004\n" + 
				"CYCLOPS/SCOTT SUMMER to BEAST/HENRY &HANK& P with weight 0.003\n" + 
				"BEAST/HENRY &HANK& P to VISION  with weight 0.007\n" + 
				"total cost: 0.097\n"));
		assertEquals(0,mu.findPath("MASTER FOUR","3-D MAN/CHARLES CHAN").compareTo("path from MASTER FOUR to 3-D MAN/CHARLES CHAN:\n" + 
				"MASTER FOUR to KILLRAVEN/JONATHAN R with weight 1.000\n" + 
				"KILLRAVEN/JONATHAN R to HAWK with weight 0.071\n" + 
				"HAWK to CAPTAIN AMERICA with weight 0.003\n" + 
				"CAPTAIN AMERICA to JONES, RICHARD MILHO with weight 0.013\n" + 
				"JONES, RICHARD MILHO to 3-D MAN/CHARLES CHAN with weight 0.250\n" + 
				"total cost: 1.337\n"));
		//endTime=System.currentTimeMillis();
		//System.out.println("LongPathTest: "+(endTime-startTime));
	}
	
	@Test
	public void deadPaths() {
		rt.gc();
		MarvelPaths2 mu=new MarvelPaths2();
		mu.createNewGraph("data/TestRun.csv");
		rt.gc();
		assertEquals(0,mu.findPath("Al","Bal").compareTo("unknown character Al\nunknown character Bal\n"));
		assertEquals(0,mu.findPath("Alpha","DeadMan").compareTo("path from Alpha to DeadMan:\nno path found\n"));
		assertEquals(0,mu.findPath("Alpha","Alpha").compareTo("path from Alpha to Alpha:\ntotal cost: 0.000\n"));
	}
	
}

