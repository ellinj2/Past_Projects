# RouteFinder

Takes in a file storing locations as "name,ID,x-coordinate,y-coordinate" and a file storing paths as "start ID,end ID" and builds a weighted, undirected Graph using paths as Edges and locations as Vertices. Then uses Dijkstra's algorithm to find and print the shortest path between two user-input buildings. Originally designed in the context of Rensselaer Polytechnic Institute campus.

## Subfolders
- **data**: holds the two input files, as well as designed test cases that are run via src/test/java/hw7/CampusPathsTest.java
- **src**: holds all relevant Java files
