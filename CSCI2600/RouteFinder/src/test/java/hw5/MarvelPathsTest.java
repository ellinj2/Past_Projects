package hw5;

import org.junit.Test;
import static org.junit.Assert.*;

public class MarvelPathsTest{
	long startTime;
	long endTime;
	String result;
	
	Runtime rt=Runtime.getRuntime();
	
	@Test
	public void buildNewGraphTest(){
		startTime=System.currentTimeMillis();
		MarvelPaths mp=new MarvelPaths();
		mp.createNewGraph("data/marvel.csv");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		//Check size of V(G), E(G)
		MarvelPaths cp=new MarvelPaths();
		cp.createNewGraph("data/TestRun.csv");
		assertEquals(26, cp.getSize("N"));
		assertEquals(512, cp.getSize("E"));
		}
	
	@Test
	public void findPathTest(){
		rt.gc();
		MarvelPaths mp=new MarvelPaths();
		mp.createNewGraph("data/marvel.csv");
		MarvelPaths op=new MarvelPaths();
		op.createNewGraph("data/TestRun.csv");
		rt.gc();
		
		//No path test
		startTime=System.currentTimeMillis();
		result=op.findPath("DeadMan","Alpha");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "path from DeadMan to Alpha:\nno path found\n".compareTo(result));
		
		//Path == reverse path test
		startTime=System.currentTimeMillis();
		result=mp.findPath("SILVER SAMURAI/KENYU", "VISION ");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "path from SILVER SAMURAI/KENYU to VISION :\nSILVER SAMURAI/KENYU to BINARY/CAROL DANVERS via UX 174\nBINARY/CAROL DANVERS to VISION  via A 171\n".compareTo(result));	
		
		startTime=System.currentTimeMillis();
		result=mp.findPath("VISION ","SILVER SAMURAI/KENYU");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "path from VISION  to SILVER SAMURAI/KENYU:\nVISION  to BINARY/CAROL DANVERS via A 171\nBINARY/CAROL DANVERS to SILVER SAMURAI/KENYU via UX 174\n".compareTo(result));
		
		//A to A path test
		startTime=System.currentTimeMillis();
		result=mp.findPath("VISION ","VISION ");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "path from VISION  to VISION :\n".compareTo(result));
	
		//No character test		
		startTime=System.currentTimeMillis();
		result=mp.findPath("VISION","VISION");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "unknown character VISION\n".compareTo(result));
		
		startTime=System.currentTimeMillis();
		result=mp.findPath("VISION","VION");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "unknown character VISION\nunknown character VION\n".compareTo(result));
		
		//Simple test
		startTime=System.currentTimeMillis();
		result=op.findPath("Beta", "Zeta");
		endTime=System.currentTimeMillis();
		//Check time constraint
		assertTrue(endTime-startTime<=(long)60000);
		assertEquals(0, "path from Beta to Zeta:\nBeta to Zeta via London\n".compareTo(result));
	}
	
}
