#include "UrgentQueue.h"
#include "Job.h"


std::ostream& UrgentQueue::printHeap(std::ostream& out){
	out<<"UQ ";
	operator<<(out, heap);
	return out;
}

UrgentQueue::UrgentQueue(){
	hook=0;
	heap={};
}

Job* UrgentQueue::pop(){
	if(heap.size()<1){std::cerr<<"ERROR IN UrgentQueue::pop(): Heap cannot be popped"<<std::endl; exit(1);}
	Job* output = heap[0];
	if(heap.size()==1){
		heap.pop_back();
		return output;
	}
	heap[0] = heap[heap.size()-1];
	heap[heap.size()-1]=output;
	heap.pop_back();
    if(heap.size()>0){this->sort();}
	return output;
}

void UrgentQueue::sort(){
	uq_hook i=(heap.size()-1)/2;
	while(i>=0){
		Job* temp=heap[i];
		unsigned int target, right, left;
  		while(2*i+1<int(heap.size())){
    		left=2*i+1;
    		right=left+1;
	    	if(right<heap.size() && heap[right]->getPriority()>heap[left]->getPriority()){target=right;}
	    	else{target=left;}

	    	if(heap[target]->getPriority()>temp->getPriority()){
	    		heap[i]=heap[target];
    			heap[i]->urgent_hook=i;
    			i=target;
    		}
    		else{break;}
		}
		heap[i]=temp;
		temp->urgent_hook=i;
		i--;
	}
	for(unsigned int i=(heap.size()-1)/2+1; i<heap.size(); i++){
		heap[i]->urgent_hook=i;
	}
}

void UrgentQueue::percup(uq_hook spot){
    Job* temp=heap[spot];
    while(spot>0 && heap[(spot-1)/2]->getPriority()<temp->getPriority()){
      heap[(spot-1)/2]->urgent_hook=spot;
      heap[spot]=heap[(spot-1)/2];
      spot--;
      spot /= 2;
    }
    heap[spot]=temp;
    temp->urgent_hook=spot;
}

void UrgentQueue::push(Job* job){
	heap.push_back(job);
	job->priority_ptr=this;
	this->percup(heap.size()-1);
}

void UrgentQueue::remove_from_index(uq_hook spot){
	Job* ptr = heap[spot];
    heap[spot]=heap[heap.size()-1];
   	heap[heap.size()-1]=ptr;
    heap.pop_back();
    if(heap.size()>0){this->sort();}
}

const Job* UrgentQueue::top(){
	Job* returner=heap[0];
	this->remove_from_index(0);
	return returner;
}