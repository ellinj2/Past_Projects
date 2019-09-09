#ifndef table_h_
#define table_h_

template <class T> class Table{
	public:
		//TYPEDEF
		typedef unsigned int size_type;

		//CONSTRUCTOS, OPERATORS, AND DESTRUCTORS
		Table() {this -> create();}
		Table(Table<T>& t){this -> create(t);}
		Table(size_type arows, size_type acols, T val=T()){this -> create(arows, acols, val);}
		Table<T>& operator=(Table& t);
		~Table(){this -> destroy();}

		//MEMBER FUNCTIONS AND OTHER OPERATORS
		void push_back_row(std::vector<T>& row);
		void push_back_column(std::vector<T>& col);
		void push_back_rows(Table<T>& t);
		void push_back_columns(Table<T>& t);
		void pop_back_row();
		void pop_back_column();
		void set(size_type r, size_type c, T val);
		void print() const;

		//MEMBER VARIABLE RETURNS
		T* operator[](size_type i);//NO LONGER NEEDED DUE TO POINTER ARITHMETIC
		T get(size_type r, size_type c);
		size_type numRows(){return rows;}
		size_type numColumns(){return columns;}
		T** getValues(){return values;}

	private:
		//PRIVATE MEMBER FUNCTIONS
		void create();
		void create(Table<T>& t);
		void create(size_type r, size_type c, T val);
		void destroy();
		void push_back_row(T* row);

		//MEMBER VARIABLES
		size_type rows;
		size_type columns;
		T** values;
};

//Create empty Table
template <class T> void Table<T>::create(){
	rows = columns = 0;
}

//Create copy Table
template <class T> void Table<T>::create(Table<T>& t){
	rows=t.numRows();
	columns=t.numColumns();
	values = new T*[rows];
	//ASSIGN VALUES
	for(size_type i=0; i<rows; i++){
		*(values+i) = new T[columns];
		for(size_type j=0; j<columns; j++){
			*(*(values+i)+j) = t.get(i, j);
		}
	}
}

//Create populated Table
template <class T> void Table<T>::create(size_type arows, size_type acols, T val){
	rows = arows;
	columns = acols;
	values = new T*[rows];
	//ASSIGN VALUES
	if(rows!=0){
		for(unsigned int i=0; i<rows; i++){
			if(columns!=0){
				*(values+i) = new T[columns];
				for(unsigned int j=0; j<columns; j++){
					*(*(values+i)+j) = val;
				}
			}
		}
	}
}

//Destructor
template <class T> void Table<T>::destroy(){
	if(rows!=0 && columns!=0){
		for(unsigned int i=0; i<rows; i++){
			delete [] *(values+i);
		}
	}
	delete [] values;
}

//Copy Table
template <class T> Table<T>& Table<T>::operator=(Table<T>& t){
	if(this != &t){
		this->destroy();//CLEAR MEMORY USED BY THIS
		rows = t.numRows();
		columns = t.numColumns();
		values = new T*[rows];
		//REASSIGN VALUES
		if(rows>0){
			for(size_type i=0; i<rows; i++){
				if(columns>0){
					*(values+i) = new T[columns];
					for(size_type j=0; j<columns; j++){
						*(*(values+i)+j) = t.get(i,j);
					}
				}
			}
		}
	}
	return *this;
}

//Bracket access
template <class T> T* Table<T>::operator[](size_type i){
	if(i<rows){
		return *(values+i);
	}
	else{
		std::cerr<<"ERROR: Row index beyond available rows"<<std::endl;
		exit(1);
	}
}

//Get values
template <class T> T Table<T>::get(size_type r, size_type c){
	if(r<rows && c<columns){
		return *(*(values+r)+c);
	}
	else{
		if(r>rows){
			std::cerr<<"ERROR: In get; Row index is beyond available memory"<<std::endl;
			exit(1);
		}
		if(c>columns){
			std::cerr<<"ERROR: In get; Column index is beyond available memory"<<std::endl;
			exit(1);
		}
		return T();
	}
}

//Reassign index value
template <class T> void Table<T>::set(size_type r, size_type c, T val){
	if(r<rows && c<columns){
		*(*(values+r)+c)=val;
	}
	else{
		if(r>rows){
			std::cerr<<"ERROR: In set; Row index is beyond available memory"<<std::endl;
			exit(1);
		}
		if(c>columns){
			std::cerr<<"ERROR: In set; Column index is beyond available memory"<<std::endl;
			exit(1);
		}
	}
}

//Print each value in the table
template <class T> void Table<T>::print() const{
	for(unsigned int i=0; i<rows; i++){
		for(unsigned int j=0; j<columns; j++){
			std::cout<<*(*(values+i)+j)<<" ";
		}
		std::cout<<std::endl;
	}
}

//Remove the last column
template <class T> void Table<T>::pop_back_column(){
	if(columns>1){
		T val = values[0][0];
		Table<T> temp(rows, columns -1, val);
		//COPY VALUES
		for(unsigned int i=0; i<rows; i++){
			for(unsigned int j=0; j<columns-1; j++){
				temp.set(i, j, *(*(values+i)+j));
			}
		}
		this -> operator=(temp);
	}
	else if(columns==1 && rows>0){
		for(size_type i=0; i<rows; i++){
			delete [] *(values+i);
		}
		columns--;
	}
	else{
		std::cerr<<"ERROR: In pop_back_column; Not enough columns to remove one"<<std::endl;
		exit(1);
	}
}

//Remove the last row
template <class T> void Table<T>::pop_back_row(){
	if(rows>1){
		Table<T> temp(rows -1, columns);
		//COPY VALUES
		for(unsigned int i=0; i<rows-1; i++){
			for(unsigned int j=0; j<columns; j++){
				temp.set(i, j, *(*(values+i)+j));
			}
		}
		this -> operator=(temp);
	}
	else if(rows==1){
		delete [] *values;
		rows--;
	}
	else{
		std::cerr<<"ERROR: In pop_back_row; Not enough rows to remove one"<<std::endl;
		exit(1);
	}
}

//Add column
template <class T> void Table<T>::push_back_column(std::vector<T>& col){
	if(col.size()==rows){
		Table<T> temp(rows, columns +1);
		//COPY VALUES
		for(unsigned int i=0; i<rows; i++){
			for(unsigned int j=0; j<columns; j++){
				temp.set(i, j, *(*(values+i)+j));
			}
			//ASSIGN NEW VALUE
			temp.set(i, columns, col[i]);
		}
		this -> operator=(temp);
	}
	else if(col.size()>rows){
		std::cerr<<"ERROR: In push_back_column; Too many rows in column"<<std::endl;
		exit(1);
	}
	else{
		std::cerr<<"ERROR: In push_back_column; Not enough rows in column"<<std::endl;
		exit(1);
	}
}

//Add all rows from a table as columns
template <class T> void Table<T>::push_back_columns(Table<T>& t){
	if(t.numRows()==rows){
		Table<T> temp(rows, columns+t.numColumns());
		//COPY VALUES
		for(size_type i=0; i<rows; i++){
			for(size_type j=0; j<columns; j++){
				temp.set(i,j,*(*(values+i)+j));
			}
			//ASSIGN NEW VALUES
			for(size_type j=0; j<t.numColumns(); j++){
				temp.set(i,columns+j,t.get(i,j));
			}
		}
	this->operator=(temp);
	}
	else{
		if(t.numRows()>rows){
			std::cerr<<"ERROR: In push_back_columns; Input table has too many rows"<<std::endl;
			exit(1);
		}
		if(t.numRows()<rows){
			std::cerr<<"ERROR: In push_back_columns; Input table doesn't have enough rows"<<std::endl;
			exit(1);
		}
	}
}

//Add row
template <class T> void Table<T>::push_back_row(std::vector<T>& row){
	if(row.size()==columns){
		Table<T> temp(rows +1, columns);
		//COPY VALUES
		for(unsigned int i=0; i<rows; i++){
			for(unsigned int j=0; j<columns; j++){
				temp.set(i, j, *(*(values+i)+j));
			}
		}
		this->operator=(temp);
		//ASSIGN NEW VALUES
		for(size_type i=0; i<columns; i++){
			this->set(rows-1, i, row[i]);
		}
	}
	else if(row.size()>columns){
		std::cerr<<"ERROR: In push_back_row; Too many columns in added row"<<std::endl;
		exit(1);
	}
	else{
		std::cerr<<"ERROR: In push_back_row; Not enough columns in added row"<<std::endl;
		exit(1);
	}
}

//Push back row for Table push back implementation
template <class T> void Table<T>::push_back_row(T* row){//Only gets called via push_back_rows, so no errors needed
	Table<T> temp(rows +1, columns);
		//COPY VALUES
		for(unsigned int i=0; i<rows; i++){
			for(unsigned int j=0; j<columns; j++){
				temp.set(i, j, *(*(values+i)+j));
			}
		}
		this->operator=(temp);
		//ASSIGN NEW VALUES
		for(size_type i=0; i<columns; i++){
			this->set(rows-1, i, *(row+i));
	}
}

//Add all rows from a table
template <class T> void Table<T>::push_back_rows(Table<T>& t){
	if(t.numColumns()==columns){
		//PUSH BACK EACH ROW IN t
		for(size_type i=0; i<t.numRows(); i++){
			this->push_back_row(*(t.getValues()+i));
		}
	}
	else{
		if(t.numColumns()>columns){
			std::cerr<<"ERROR: In push_back_rows; Input table has too many columns"<<std::endl;
			exit(1);
		}
		if(t.numColumns()<columns){
			std::cerr<<"ERROR: In push_back_rows; Input table doesn't have enough columns"<<std::endl;
			exit(1);
		}
	}
}

#endif