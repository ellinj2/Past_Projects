/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

// Node::~Node(){
// 	delete left;
// 	delete right;
// }

//COPY EACH NODE FROM AN OLD TREE TO THE CURRENT TREE
Node* Rope::copyNode(Node* input, Node* OG){
	if(input==NULL){return NULL;}
	Node* newNode = new Node;
	newNode->weight=input->weight;
	newNode->value=input->value;
	newNode->left = copyNode(input->left, newNode);
	newNode->right = copyNode(input->right, newNode);
	newNode->parent=OG;
	return newNode;
}

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	if (ptr_->right != NULL) { // find the leftmost child of the right node
		ptr_ = ptr_->right;
		while (ptr_->left != NULL) { ptr_ = ptr_->left; }
	} else { // go upwards along right branches... stop after the first left
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
		ptr_ = ptr_->parent;
	}
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	if(!root){return rope_iterator(NULL);}
	rope_iterator itr(root);
	while(itr.ptr_->left){itr.ptr_=itr.ptr_->left;}
	return itr;
}

//RESETS THE WEIGHT FOR EACH NODE
int Rope::setWeight(Node* ptr){
	if(!ptr){return 0;}
	if(is_leaf(ptr)){ptr->weight=ptr->value.length(); return ptr->weight;}
	ptr->weight=0;
	ptr->weight+=setWeight(ptr->left);
	if(ptr->left){
		Node* adder=ptr->left;
		while(adder){
			adder=adder->right;
			ptr->weight+=setWeight(adder);
		}
	}
	return ptr->weight;
}

Rope::Rope(){
	root = NULL;
	size_=0;
}
//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root=p;
	size_=0;
	if(root){
		root->weight=p->weight;
		rope_iterator itr;
		for(itr=begin(); itr!=end(); itr++){
			if(is_leaf(itr.ptr_)){size_+=itr.ptr_->weight;}
		}
	}
}

//RECURSIVE DESTRUCTOR
void Rope::destroy(Node* ptr){
	if(!ptr){return;}
	destroy(ptr->right);
	destroy(ptr->left);
	delete ptr;
}

Rope::~Rope(){
	if(!root){return;}
	if(root->parent){
		if(root->parent->right==root){root->parent->right=NULL;}
		if(root->parent->left==root){root->parent->left=NULL;}
		root->parent=NULL;
	}
	this->destroy(root);
	root=NULL;
}

Rope::Rope(const Rope& r){
	root= this->copyNode(r.root, NULL);
	size_=r.size_;
}

Rope& Rope::operator= (const Rope& r){
	this->destroy(root);
	root= this->copyNode(r.root, NULL);
	size_=r.size_;
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	if(i<0){return false;}
	Node* ptr=root;
	while(!is_leaf(ptr)){
		if(i<ptr->weight){ptr=ptr->left;}
		else{
			i-=ptr->weight;
			ptr=ptr->right;
		}
	}
	if(ptr->weight>i){
		c=ptr->value[i];
		return true;
	}
	return false;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	Node* newr = new Node;
	newr->left=root;
	newr->left->parent=newr;
	newr->right=r.expose_root();
	newr->right->parent=newr;
	root=newr;
	root->weight=setWeight(root);
	size_+=r.size();
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	s="";
	for(; i<=j; i++){
		char c;
		if(index(i, c)){
			s+=c;
		}
		else{return false;}
	}
	return true;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	delete rhs.root;
	if(i<=0){//COPY ENTIRE ROOT
		rhs.root=root;
		root=NULL;
		rhs.root->weight=setWeight(rhs.root);
		size_=0;
		for(rope_iterator itr=rhs.begin(); itr!=rhs.end(); itr++){
			if(is_leaf(itr.ptr_)){rhs.size_+=itr.ptr_->weight;}
		}
		return *this;
	}
	
	if(i>size_){return *this;}//TOO BIG TO ADD
	Node* ptr=root;//TRACK CURRENT
	int j=i;//SET HOLDER FOR INDEX
	//FIND NECESSARY LEAF
	while(!is_leaf(ptr)){
		if(i<ptr->weight){ptr=ptr->left;}
		else{
			i-=ptr->weight;
			ptr=ptr->right;
		}
	}
	j-=i;//SET TO 0 INDEX FOR THE LEAF NODE
	int found=ptr->weight;
	
	//SPLIT NODE IF NEEDED
	if(i!=0){
		Node* newPtr = new Node;
		newPtr->left = new Node;
		newPtr->right = new Node;
		newPtr->left->value="";
		for(int k=0; k<i; k++){
			newPtr->left->value+=ptr->value[k];
		}
		for(unsigned int k=i; k<ptr->value.length(); k++){
			newPtr->right->value+=ptr->value[k];
		}
		newPtr->left->parent=newPtr;
		newPtr->right->parent=newPtr;
		newPtr->parent=ptr->parent;
		if(ptr->parent->left==ptr){ptr->parent->left=newPtr;}
		else{ptr->parent->right=newPtr;}
		delete ptr;
		ptr=newPtr->right;
		root->weight=setWeight(root);
	}

	if(!rhs.root){rhs.root=new Node;} //Create root for new tree
	bool rtn=false; //Check if leaf is on right of parent
	if(ptr->parent->right==ptr){
		rtn=true;
		rhs.root->left=ptr;
		ptr->parent->right=NULL;
		rhs.root->left->parent=rhs.root;
		root->weight=setWeight(root); //Reset weights for main tree
	}

	//Main split
	bool onLeft=false;
	Node* rightFinder=root;
	while(!rightFinder->right){rightFinder=rightFinder->left;}
	if(j<rightFinder->weight){onLeft=true;}
	Node* jPtr=root;
	while(j>0){
		if(j<jPtr->weight){jPtr=jPtr->left;}
		else{
			j-=jPtr->weight;
			jPtr=jPtr->right;
		}
	}
	//OPERATIONS IF THE NODE WAS ON THE RIGHT
	if(rtn){
		j+=found;
		if(onLeft){root->left=jPtr->left;}
		rhs.root->right=jPtr;
		if(jPtr->parent->right==jPtr){jPtr->parent->right=NULL;}
		else{jPtr->left=NULL;}
		rhs.root->right->parent=rhs.root;
	}
	else{
		rhs.root->left=jPtr;
		if(jPtr->parent->right==jPtr){jPtr->parent->right=NULL;}
		else{jPtr->left=NULL;}
		jPtr->parent=rhs.root;
	}


	root->weight=setWeight(root);
	rhs.root->weight=setWeight(rhs.root);
	size_=0;
	for(rope_iterator itr=begin(); itr!=end(); itr++){
		if(is_leaf(itr.ptr_)){size_+=itr.ptr_->weight;}
	}
	for(rope_iterator itr=rhs.begin(); itr!=rhs.end(); itr++){
		if(is_leaf(itr.ptr_)){rhs.size_+=itr.ptr_->weight;}
	}
	return *this;
}
