HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Jesse Ellin >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ohad Nir
Zak Kubli >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



TESTING & DEBUGGING STRATEGY:
Using print statements to check if a function was being called, using gdb to check for incorrect values, and drmemory to check for various memory errors.  



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

push_front: O(1) if the size of the array is constant, O(n) if the array is size n. Array of size n differs from dslist and STL list because it needs to shift every item in the array instead of just adding a new node
pop_front: O(1) if the size of the array is constant, O(n) if the array is size n. Array of size n differs from dslist and STL list because it needs to shift every element in the array instead of just deleting a node
push_back: O(1)
pop_back: O(1)
print: O(m) for a list with m nodes if the size of the array is constant, O(m*n) if the array is size n. A constant size array differs from dslist and STL list because it only needs to worry about the number of nodes
erase: O(1) if the size of the array is constant, O(n) if the array is size n. A constant size array differs from dslist and STL list because it only needs to worry about the number of nodes
insert: O(1) if the size of the array is constant, O(n) if the array is size n. Array of size n differs from dslist and STL list because it needs to shift every element in the array instead of just adding a new node
copy_list: O(m) for a list with m nodes if the size of the array is constant, O(m*n) if the array is size n. A constant size array differs from dslist and STL list because it only needs to worry about the number of nodes
destroy_list: O(m) for a list with m nodes. A constant size array differs from dslist and STL list because it only needs to worry about the number of nodes and not the total number of values.

In the worst case, this data structure will require O(m*n) memory where m is the number of nodes and n is the size of the array.

*Not sure what the last two questions are asking. Also ran out of time*


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


