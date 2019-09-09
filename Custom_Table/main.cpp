// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "table.h"


// helper testing functions
void SimpleTest();
void StudentTests();
void stringTable();
void zeroTable();
// void differentTypeCopier();//Gets commented out
// void differentTypeAssignment();//Gets commented out
// void tooManyColumnsInNewRow();//Gets commented out
// void tooManyRowsInNewColumn();//Gets commented out
// void tooFewColumnsInNewRow();//Gets commented out
// void tooFewRowsInNewColumn();//Gets commented out
void zeroPushTable();
void BatchTest(const char* filename, int num);
void ExtraCreditTests();


int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    std::cout << "Simple test completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;    
    
    //
    // uncomment if you have implemented the extra credit features
    //
    ExtraCreditTests();
    //

 } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << std::endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}



void SimpleTest() {

  // create a table with dimensions 2x5, where all entries are '.'
  Table<char> t(2,5,'.');
  assert (t.get(0,0) == '.');
  assert (t.get(1,4) == '.');
  assert (t.get(1,2) == '.');
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;
  
  // intialize the values in the table
  t.set(0,0,'a');
  t.set(0,1,'b');
  t.set(0,2,'c');
  t.set(0,3,'d');
  t.set(0,4,'e');
  t.set(1,0,'f');
  t.set(1,1,'g');
  t.set(1,2,'h');
  t.set(1,3,'i');
  t.set(1,4,'j');
  assert (t.get(0,0) == 'a');
  assert (t.get(1,2) == 'h');
  assert (t.get(1,4) == 'j');
  t.print();
  std::cout << "set & get tests completed" << std::endl;

  // =======================================================  
  // 
  //     UNCOMMENT THE SECTIONS BELOW AS YOU 
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================  

  
  // add a row
  std::vector<char> new_row; 
  new_row.push_back('A');
  new_row.push_back('B');
  new_row.push_back('C');
  new_row.push_back('D');
  new_row.push_back('E');
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;
  

  
  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;
  

  
  // add a column
  std::vector<char> new_col;
  new_col.push_back('X');
  new_col.push_back('Y');
  new_col.push_back('Z');
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;
  


  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;


  
  // example of the copy constructor
  Table<char> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,'Q');
  assert (t.get(1,2) != another.get(1,2));
  std::vector<char> new_row2; 
  new_row2.push_back('A');
  new_row2.push_back('B');
  new_row2.push_back('C');
  new_row2.push_back('D');
  new_row2.push_back('E');
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;
  

  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.

}

void StudentTests() {
  std::cout<<std::endl<<std::endl<<"Beginning student tests..."<<std::endl<<std::endl;

  // =======================================================  
  // 
  // YOU SHOULD ADD YOUR OWN TEST CASES HERE
  //
  // be sure to rigorously test:
  //   * tables that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * destructor
  //   * invalid requests (comment out for final submission)
  //
  // =======================================================  

  std::cout<<"For integer table..."<<std::endl;
  // create a table with dimensions 2x5, where all entries are 0
  Table<int> t(2,5, 0);
  assert (t.get(0,0) == 0);
  assert (t.get(1,4) == 0);
  assert (t.get(1,2) == 0);
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;
  
  // intialize the values in the table
  t.set(0,0,1);
  t.set(0,1,2);
  t.set(0,2,3);
  t.set(0,3,4);
  t.set(0,4,5);
  t.set(1,0,6);
  t.set(1,1,7);
  t.set(1,2,8);
  t.set(1,3,9);
  t.set(1,4,0);
  assert (t.get(0,0) == 1);
  assert (t.get(1,2) == 8);
  assert (t.get(1,4) == 0);
  t.print();
  std::cout << "set & get tests completed" << std::endl;


  // add a row
  std::vector<int> new_row; 
  new_row.push_back(11);
  new_row.push_back(12);
  new_row.push_back(13);
  new_row.push_back(14);
  new_row.push_back(15);
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;
  

  
  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;
  

  
  // add a column
  std::vector<int> new_col;
  new_col.push_back(111);
  new_col.push_back(222);
  new_col.push_back(333);
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;
  


  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;


  
  // example of the copy constructor
  Table<int> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,159);
  assert (t.get(1,2) != another.get(1,2));
  std::vector<int> new_row2; 
  new_row2.push_back(99);
  new_row2.push_back(88);
  new_row2.push_back(77);
  new_row2.push_back(66);
  new_row2.push_back(55);
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;

  std::cout<<std::endl;

  stringTable();//TEST FOR A DIFFERENT DATA TYPE

  // differentTypeCopier();
  // differentTypeAssignment();
  // tooManyColumnsInNewRow();
  // tooManyRowsInNewColumn();
  // tooFewColumnsInNewRow();
  // tooFewRowsInNewColumn();
  zeroTable();

  zeroPushTable();

  std::cout<<std::endl;

  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.

}

//Runs the same tests for a table holding strings
void stringTable(){
  std::cout<<"For string table..."<<std::endl;
  // create a table with dimensions 2x5, where all entries are 0
  Table<std::string> t(2,5, "default");
  assert (t.get(0,0) == "default");
  assert (t.get(1,4) == "default");
  assert (t.get(1,2) == "default");
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;
  
  // intialize the values in the table
  t.set(0,0,"this");
  t.set(0,1,"table");
  t.set(0,2,"now");
  t.set(0,3,"stores");
  t.set(0,4,"strings");
  t.set(1,0,"isn't");
  t.set(1,1,"that");
  t.set(1,2,"just");
  t.set(1,3,"bloody");
  t.set(1,4,"wicked?!");
  assert (t.get(0,0) == "this");
  assert (t.get(1,2) == "just");
  assert (t.get(1,4) == "wicked?!");
  t.print();
  std::cout << "set & get tests completed" << std::endl;


  // add a row
  std::vector<std::string> new_row; 
  new_row.push_back("right?");
  new_row.push_back("it's");
  new_row.push_back("down");
  new_row.push_back("right");
  new_row.push_back("amazing!");
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;
  

  
  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;
  

  
  // add a column
  std::vector<std::string> new_col;
  new_col.push_back("ain't");
  new_col.push_back("that");
  new_col.push_back("neat?");
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;
  


  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;


  
  // example of the copy constructor
  Table<std::string> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,"whoops");
  assert (t.get(1,2) != another.get(1,2));
  std::vector<std::string> new_row2; 
  new_row2.push_back("might");
  new_row2.push_back("have");
  new_row2.push_back("broken");
  new_row2.push_back("something");
  new_row2.push_back("important...");
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;

}

//Try running the copy constructor on a table of a different data type
// void differentTypeCopier(){//Gets commented out
//   Table<int> i(2,5,0);
//   Table<char> c(i);
// }

//Try reassigning a value to a different data type
// void differentTypeAssignment(){
//   std::cout<<"For an assignment of a different type..."<<std::endl;
//   Table<int> t(2,5,0);

//   t.set(0,0,"hello");
// }

//Try pushing back a row with too many columns
// void tooManyColumnsInNewRow(){
//   std::cout<<"For a row with too many columns..."<<std::endl;
//   Table<int> t(2,5,0);

//   std::vector<int> new_row;
//   for(unsigned int i=0; i<6; i++){
//     new_row.push_back(i);
//   }
//   t.push_back_row(new_row);
// }

//Try pushing back a column with too many rows
// void tooManyRowsInNewColumn(){
//   std::cout<<"For a column with too many rows..."<<std::endl;
//   Table<int> t(2,5,0);

//   std::vector<int> new_column;
//   for(unsigned int i=0; i<3; i++){
//     new_column.push_back(i);
//   }
//   t.push_back_column(new_column);
// }

//Try pushing back a row without enough columns
// void tooFewColumnsInNewRow(){
//   std::cout<<"For a row without enough columns..."<<std::endl;
//   Table<int> t(2,5,0);

//   std::vector<int> new_row;
//   for(unsigned int i=0; i<4; i++){
//     new_row.push_back(i);
//   }
//   t.push_back_row(new_row);
// }

//Try pushing back a column without enough rows
// void tooFewRowsInColumn(){
//   std::cout<<"For a column without enough rows..."<<std::endl;
//   Table<int> t(2,5,0);

//   std::vector<int> new_column;
//   for(unsigned int i=0; i<1; i++){
//     new_column.push_back(i);
//   }
//   t.push_back_column(new_column);
// }

void zeroTable(){
  std::cout<<"For a Table with 0 rows and 0 columns, pushing back a row with 0 columns..."<<std::endl;
  Table<int> test(0,0,0);
  std::vector<int> input;
  input.push_back(1);
  input.pop_back();
  test.push_back_row(input);
  test.print();
  std::cout<<"Table with zero rows and zero columns can have a vector of size 0 pushed back. Makes sense..."<<std::endl;
}

void zeroPushTable(){
  std::cout<<"For a Table with one 0 value, pushing back the other an instance of that value with equal count of the other..."<<std::endl;
  std::cout<<"(that sort of makes sense...)"<<std::endl;
  Table<int> test(0,5,0);
  test.print();
  std::vector<int> row;
  for(unsigned int i=1; i<6; i++){
    row.push_back(i);
  }
  test.push_back_row(row);
  test.print();
  std::cout<<"Able to push back row of equal column count"<<std::endl;
  for(unsigned int i=0; i<4; i++){
    test.push_back_row(row);
  }
  //SET COLUMNS TO 0
  for(unsigned int i=0; i<5; i++){
    test.pop_back_column();
  }
  test.push_back_column(row);
  test.print();
  std::cout<<"Able to push back column of equal row count"<<std::endl;
}

void ExtraCreditTests() {

  // =======================================================  
  // 
  //            UNCOMMENT THIS SECTION IF YOU 
  //      COMPLETE THE EXTRA CREDIT IMPLEMENTATION
  //
  // =======================================================  

  
  Table<char> x(2,5,'x');
  assert (x.numRows() == 2);
  assert (x.numColumns() == 5);
  x.set(0,0,'.');
  x.set(1,4,'X');
  x.print();

  Table<char> y(4,5,'y');
  y.set(0,0,'.');
  y.set(3,4,'Y');
  x.push_back_rows(y);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 5);
  x.print();
  
  Table<char> z(6,2,'z');
  z.set(0,0,'.');
  z.set(5,1,'Z');
  x.push_back_columns(z);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 7);
  x.print();

  assert (x.get(0,0) == '.');
  assert (x.get(1,0) == 'x');
  assert (x.get(0,1) == 'x');
  assert (x.get(1,4) == 'X');

  assert (x.get(2,0) == '.');
  assert (x.get(2,1) == 'y');
  assert (x.get(3,0) == 'y');
  assert (x.get(5,4) == 'Y');

  assert (x.get(0,5) == '.');
  assert (x.get(1,5) == 'z');
  assert (x.get(0,6) == 'z');
  assert (x.get(5,6) == 'Z');

  std::cout << "extra credit tests completed" << std::endl;
  
}



// Batch test will repeatedly load & process a file with Table
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int i,j,num;

    // create the initial table
    istr >> token >> i >> j >> c;
    assert (token == "create");
    // note: here we explicitly allocate memory for the Table object
    Table<char> *table = new Table<char>(i,j,c);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "set") {
        istr >> i >> j >> c;
        table->set(i,j,c);	
      } else if (token == "get") {
        istr >> i >> j >> c;
        char c2 = table->get(i,j);
        assert (c == c2);
      } else if (token == "push_back_row") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_row(tmp);
      } else if (token == "push_back_column") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_column(tmp);
      } else if (token == "pop_back_row") {
        table->pop_back_row();
      } else if (token == "pop_back_column") {
        table->pop_back_column();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    if (iters == 0)
      table->print();

    // Because the Table memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete table;
  }
}

