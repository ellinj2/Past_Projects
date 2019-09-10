HOMEWORK 8: ROPES


NAME:  < Jesse Ellin >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Xavier Marshall
Ohad Nir >

This code creates a custom Rope class similar to a standard Rope.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < Too many (maybe 30) >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Unbalanced rope: One massive left tree. No right nodes. Ever.

Copy Constructor: Balanced) O(m) Unbalanced) O(p*m)

Construct from Node*: Balanced) O(m) Unbalanced) O(p*m)

Index: Balanced) O(p) Unbalanced) O(p)

Report: Balanced) O(n) Unbalanced) O(n*p)

iterator operator++: Balanced) O(p) 2Unbalanced) O(p)

Split: Didn't finish implementing. Roughly Balanced) O(p) Unbalanced) O(p)

Concat: Balanced) O(1) Unbalanced) O(1)


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

Ton of drmemory and gdb. Some cout's as needed. Lots of diagramming from code and coding from diagramming. In StudentTests, I implemented splits that would split on a left leaf of a right tree, the right leaf of a left tree, left leaf of a left tree, and splitting in the middle of a leaf (didn't work too well...). I also tested indexing below 0 and about rope.size().


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
I couldn't get split() to work properly when the index is in the middle of a leaf node. The node split and it took the correct part of the split node, but it wouldn't take any of the rest of the rope...
