package hw5;

import hw4.*;
import java.util.*;
import java.io.*;

public class MarvelParser {

	/** @param: filename The path to the "CSV" file that contains the <hero, book> pairs                                                                                                
        @param: data Graph to add Nodes and Edges to where each Node is a <i>here</i> and each Edge is a <i>book</i>
        @param nameToNode Map that maps each Node label to its respective Node to optimize runtime
        @modifies data, nameToNode
        @effects adds Nodes and Edges to data based on the CSV file. Maps each Node name to the Node in nameToNode
        @throws: IOException if file cannot be read of file not a CSV file                                                                                     
	 */
    public static void readData(String filename, Graph<String,String> data, Map<String, Node<String,String>> nameToNode) 
    		throws IOException {

    	BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line = null;

        Set<String> chars=new HashSet<String>();
        Map<String, Set<Node<String,String>>> charsInBooks=new HashMap<String, Set<Node<String,String>>>();
        
        while ((line = reader.readLine()) != null) {
             int i = line.indexOf("\",\"");
             /*if ((i == -1) || (line.charAt(0)!='\"') || (line.charAt(line.length()-1)!='\"')) {
            	 throw new IOException("File "+filename+" not a CSV (\"HERO\",\"BOOK\") file.");
             } */            
             String character = line.substring(1,i);
             String book = line.substring(i+3,line.length()-1);
             
             Node<String,String> char1=null;
             
             // Adds the character to the character set. If character already in, add has no effect.
             if(chars.add(character)) {
            	 char1=new Node<String,String>(character);
            	 nameToNode.put(character, char1);
            	 data.addNode(char1);
             } else {
            	 char1=nameToNode.get(character);
             }
             

             // Adds the character to the set for book
             Set<Node<String,String>> s = charsInBooks.get(book);
             if (s == null) {
               s = new HashSet<Node<String,String>>();
               charsInBooks.put(book,s);
             } else {
            	 for(Node<String,String> char2: s) {
            		 data.newEdge(char1, char2, 1, book);
            		 data.newEdge(char2, char1, 1, book);
            	 }
             }
             s.add(char1);
        }
    }

    public static void readData2(String filename, Graph<String,Float> data, Map<String, Node<String,Float>> nameToNode) 
    		throws IOException {

    	BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line = null;

        Set<String> chars=new HashSet<String>();
        Map<String, Set<Node<String,Float>>> charsInBooks=new HashMap<String, Set<Node<String,Float>>>();
        
        while ((line = reader.readLine()) != null) {
             int i = line.indexOf("\",\"");
             /*if ((i == -1) || (line.charAt(0)!='\"') || (line.charAt(line.length()-1)!='\"')) {
            	 throw new IOException("File "+filename+" not a CSV (\"HERO\",\"BOOK\") file.");
             } */            
             String character = line.substring(1,i);
             String book = line.substring(i+3,line.length()-1);
             
             Node<String,Float> char1=null;
             
             // Adds the character to the character set. If character already in, add has no effect.
             if(chars.add(character)) {
            	 char1=new Node<String,Float>(character);
            	 nameToNode.put(character, char1);
            	 data.addNode(char1);
             } else {
            	 char1=nameToNode.get(character);
             }
             

             // Adds the character to the set for book
             Set<Node<String,Float>> s = charsInBooks.get(book);
             if (s == null) {
               s = new HashSet<Node<String,Float>>();
               charsInBooks.put(book,s);
             } else {
            	 for(Node<String,Float> char2: s) {
            		 Edge<Float,String> e=char1.getMinEdge(char2);
            		 if(e==null) {
            			 data.newEdge(char1,char2,1,(Float)(float)1);
            			 data.newEdge(char2,char1,1,(Float)(float)1);
            		 } else {
            			 float invar=(float)Math.pow((float)Math.pow(e.weight(),-1)+1,-1);
            			 data.newEdge(char1,char2,invar,(Float)invar);
            			 data.newEdge(char2,char1,invar,(Float)invar);
            		 }
            	 }
             }
             s.add(char1);
        }
    }
    
    
    public static void main(String[] arg) {

    	String file = arg[0];
    	try {
    		Graph<String,String> temp=new Graph<String,String>("Tester");
    		Map<String, Node<String,String>> reference=new HashMap<String, Node<String,String>>();
    		readData(file,temp, reference);

    	} catch (IOException e) {
    		e.printStackTrace();
    	}

    }
}
