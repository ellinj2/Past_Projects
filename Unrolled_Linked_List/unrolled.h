#ifndef unrolled_h_
#define unrolled_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <ostream>

const unsigned int SIZE_OF_ARRAYS=6;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL), count(0) {}
  Node(const T& v){
    next_=NULL;
    prev_=NULL;
    array_[0]=v;
    count = 1;
  }

  // REPRESENTATION
  T* array_ = new T[SIZE_OF_ARRAYS]; //storing array in heap to confirm deletion
  Node<T>* next_;
  Node<T>* prev_;
  unsigned int count; //number of elements in array
  unsigned int index_=0; //index currently viewed by iterator
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL) : ptr_(p) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->array_[ptr_->index_];  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    //ITERATE THROUGH ARRAY UNTIL FINAL INDEX
    if(ptr_->index_<ptr_->count-1){
      ptr_->index_++;
    }
    //RESET INDEX VALUE AND MOVE TO NEXT NODE
    else{
      ptr_->index_=0;
      ptr_ = ptr_->next_;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    if(ptr_->index_<ptr_->count-1){
      ptr_->index_++;
      return *this;
    }
    else{
      ptr_->index_=0;
      list_iterator<T> temp(*this);
      ptr_ = ptr_->next_;
      return temp;  
    }
    
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    //MOVE TO PREVIOUS NODE IF AT FIRST INDEX
    if(ptr_->index_==0){
      ptr_ = ptr_->prev_;  
    }
    //DECREMENT INDEX IF IN THE MIDDLE OF THE ARRAY
    else{
      ptr_->index_--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if(ptr_->index_==0){
      ptr_ = ptr_->prev_;  
    }
    else{
      ptr_->index_--;
    }
    return *this;
    return temp;
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the count of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }
  void print(std::ostream& out);

  // read/write access to contents
  const T& front() const { return head_->array_[0];  }
  T& front() { return head_->array_[0]; }
  const T& back() const { return *(tail_->array_[tail_->count-1]); }
  T& back() { return tail_->array_[tail_->count-1]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
  unsigned int nodes=0;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  //ADD TO THE FRONT OF HEAD IF THERE'S ROOM
  if(head_->count < SIZE_OF_ARRAYS){
    //SHIFT EVERY VALUE ONE TO THE RIGHT
    for(unsigned int i=head_->count; i>0; i--){
      head_->array_[i] = head_->array_[i-1];
    }
    head_->array_[0]=v; //adds new value
    head_->count++;
  }
  //SPECIAL CASE IF THERE'S NO HEAD
  else if (!head_) {
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
    head_->count++;
    tail_->count++;
    nodes++;
  }
  //IF THE HEAD IS FULL, MAKE A NEW HEAD
  else{
    Node<T>* temp = new Node<T>(v);
    temp->next_ = head_;
    head_->prev_ = temp;
    head_ = temp;
  }
  size_++;
}

template <class T>
void UnrolledLL<T>::pop_front() {
  //MOVE EVERY ELEMENT ONE TO THE LEFT
  for(unsigned int counter=0; counter<head_->count-1; counter++){
    head_->array_[counter] = head_->array_[counter+1];
  }
  head_->count--;
  //DELETE THE HEAD IF NEEDED
  if(head_->count == 0){
    Node<T>* temp = head_;
    head_ = head_->next_;
    head_->prev_=0;
    nodes--;
    delete[] temp->array_;
    delete temp;
  }
  size_--;
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  // special case: initially empty list
  if (!tail_) {
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
    nodes++;
  } 
  else{
    //MAKE A NEW TAIL IF NEEDED
    if(tail_->count == SIZE_OF_ARRAYS){
      Node<T>* newp = new Node<T>(v);
      tail_->next_ = newp;
      newp->prev_ = tail_;
      tail_ = newp;
      nodes++;
      }
    //ADD THE NEW VALUE OTHERWISE
    else{
      tail_->array_[tail_->count] = v;
      tail_->count++;
      }
    }
    ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() {
  tail_->count--; //effectively shortens the array
  //DELETE TAIL IF NEEDED
  if(tail_->count == 0){
    Node<T>* temp=NULL;
    if(tail_->prev_){ //if the tail isn't the only node
      temp = tail_->prev_;
      nodes--;
    }
    delete[] tail_->array_;
    delete tail_;
    if(temp){
      tail_ = temp;
      if(nodes!=1){
        tail_->next_=0;
      }
    }
  }
  size_--;
}

template <class T> void UnrolledLL<T>::print(std::ostream& out){
  std::cout<<"UnrolledLL, size: "<<size_<<std::endl;
  if(size_>0){
    for(Node<T>* itr = head_; itr != 0;){
     std::cout<<"node:["<<itr->count<<"] ";
      unsigned int counter = 0;
      for(; counter != itr->count; counter++){
        std::cout<<itr->array_[counter]<<"  ";
      }
      std::cout<<std::endl;
      itr = itr->next_;
    }
  }
  else{
    std::cout<<"No nodes"<<std::endl;
  }
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  bool almostEnd = false; //checks if the element being erased is the last item, in which case iterator needs to move to new node
  if(size_>0){
    --size_;
    //CHECK IF NODE CAN HAVE VALUES REMOVED
    if(itr.ptr_->count > 0){
      unsigned int i = itr.ptr_->index_; //get the index of the iterator
      if(i<itr.ptr_->count-1){//check if the value is not the last one
        //MOVE EVERY VALUE ONE TO THE LEFT
        for(; i<itr.ptr_->count-1; i++){
          itr.ptr_->array_[i] = itr.ptr_->array_[i+1];
        }
        itr.ptr_->count--;
      }
      else{
        itr.ptr_->count--;
        //ONLY NEED TO CHECK IF IT WAS THE LAST VALUE IF THERE'S STILL VALUES LEFT
        if(itr.ptr_->count!=0){
          almostEnd=true;
        }
      }
    }
  }
  if(!almostEnd){
    //IF IT NEEDS TO BE ERASED
    if(itr.ptr_->count==0){
      //IF THE NODE IS IN THE MIDDLE
      if(itr!=head_ && itr!=tail_){
        //SET POINTERS FOR THE PREVIOUS AND NEXT NODES
        Node<T>* back = itr.ptr_->prev_;
        Node<T>* front = itr.ptr_->next_;
        //DELETE CURRENT NODE
        delete[] back->next_->array_;
        delete back->next_;
        back->next_ = front;
        front->prev_ = back;
        itr = front;
      }
      //SPECIAL CASE IF THE NODE IS THE HEAD
      else if(itr==head_){
        itr=itr.ptr_->next_;
        delete[] head_->array_;
        delete head_;
        head_ = itr.ptr_;
      }
      else if(itr==tail_){
        Node<T>* back=tail_->prev_;
        delete[] tail_->array_;
        delete tail_;
        tail_ = back;
        itr = tail_;
      }
    }
  }
  else{
    itr++;
  }
  return itr;
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  Node<T>* temp = NULL;
  ++size_ ;
  if(itr.ptr_->count<SIZE_OF_ARRAYS){
    unsigned int counter=0;
    for(; counter<itr.ptr_->count; counter++){
      if(itr.ptr_->array_[counter]==*itr){
        break;
      }
    }
    unsigned int end=SIZE_OF_ARRAYS-1;
    for(; end>counter; end--){
      itr.ptr_->array_[end] = itr.ptr_->array_[end-1];
    }
    itr.ptr_->array_[counter] = v;
    itr.ptr_->count++;
    temp = itr.ptr_;
  }
  else{
    unsigned int i=0;
    for(; i<SIZE_OF_ARRAYS; i++){
      if(itr.ptr_->array_[i]==*itr){
        break;
      }
    }
    unsigned int counter = itr.ptr_->count-(i+1);
    Node<T>* trial = new Node<T>;
    trial->count = counter+1;
    trial->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = trial;
    itr.ptr_->next_ = trial;
    counter--;
    std::cout<<itr.ptr_->array_[counter]<<std::endl;
    for(i=0; i<trial->count; i++){
      trial->array_[i] = itr.ptr_->array_[counter+i];
    }
    itr.ptr_->array_[counter] = v;
    itr.ptr_->count = itr.ptr_->count-counter-1;
    trial->index_ = 0;
    itr.ptr_->index_ = 0;
    temp = trial;
  }
  return temp;
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  nodes = 0;
  head_ = new Node<T>;
  nodes++;
  Node<T>* runner = old.head_;
  head_->count = runner->count;
  for(unsigned int i=0; i<runner->count; i++){
    head_->array_[i] = runner->array_[i];
  }
  tail_ = head_;
  Node<T>* ptr = head_;
  runner = runner->next_;
  while(runner){
    ptr->next_ = new Node<T>;
    nodes++;
    ptr->next_->prev_ = ptr;
    ptr = ptr->next_;
    ptr->count = runner->count;
    for(unsigned int i=0; i<runner->count; i++){
      ptr->array_[i] = runner->array_[i];
    }
    tail_ = ptr;
    ptr->next_ = NULL;
    runner = runner->next_;
  }
  
}

template <class T>
void UnrolledLL<T>::destroy_list() {
  std::cout<<std::endl;
  if(head_){
    Node<T>* destroyer = head_;
    while(destroyer!= tail_){
      destroyer = destroyer->next_;
      delete[] destroyer->prev_->array_;
      delete destroyer->prev_;
    }
    delete[] destroyer->array_;
    delete destroyer;
  }
}

#endif