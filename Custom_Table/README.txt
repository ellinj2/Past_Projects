HOMEWORK 3: RESIZABLE TABLE


NAME:  < Jesse Ellin >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ohad Nir
Zak Kubli
Xavier Marshall
Prof. Holzbauer
Adam G. (submitty forum) >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 >



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1)

set: O(1)

numRows: O(1)

numColumns: O(1)

push_back_row: O(n*m*m)

push_back_column: O(n*m*m)

pop_back_row: O(n*m*m)

pop_back_column: O(n*m*m)

print: O(n*m)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

I started with the built-in g++ debugger. Once the code was essentially running, I ran it through gdb to find any hidden issues and try to figure out where memory leaks were occuring. After a while, I resorted to using DrMemory with line tagging to track every single memory error.

I wrote functions to test the copy constructor when passed a Table of a different data type, assigning a value to an index of a different data type, passing a row to push_back_row that didn't have enough columns, a row that has too many columns, passing a column to push_back_column that didn't have enough columns, and a column that had too many columns. I also implemented a function to test cases where row count is 0 and/or where column count is 0.


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

I implemented both aspects of the extra credit.

multi-row: O(n*n*m*m)

multi-column: O(n*m*m)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

