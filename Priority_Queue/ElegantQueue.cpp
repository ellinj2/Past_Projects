#include "ElegantQueue.h"
#include "Job_extra.h"


std::ostream& ElegantQueue::printHeap(std::ostream& out){
    out<<this->type<<" ";
    operator<<(out, heap);
    return out;
}

ElegantQueue::ElegantQueue(std::string key){
	if(key!="TQ" && key!="UQ"){std::cerr<<"ERROR IN ElegantQueue CONSTRUCTOR: Invalid type name"<<std::endl; exit(1);}
	heap={};
	type=type;
}

//ONLY CALLED AS AIDE, SO NO NEED TO REASSIGN HOOKS
void ElegantQueue::sendToTop(int i){
	eJob* temp=heap[i];
	heap[i]=heap[0];
	heap[0]=temp;
}

eJob* ElegantQueue::pop(){
    if(heap.size()==0){std::cerr<<"ERROR IN ElegantQueue::pop(): Heap cannot be popped"<<std::endl; exit(1);}
    eJob* output = heap[0];
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

void ElegantQueue::push(eJob* item){
	heap.push_back(item);
	if(type=="UQ"){item->priority_ptr=this;}
	else{item->time_ptr=this;}
    this->percTop();
}

void ElegantQueue::sort(){
	int i=(heap.size()-1)/2;
    while(i>=0){
        eJob* temp=heap[i];
        unsigned int target, right, left;
        while(2*i+1<int(heap.size())){
            left=2*i+1;
            right=left+1;
            if(right<heap.size()){
            	if(this->type=="TQ" && heap[right]->getTime()<heap[left]->getTime()){target=right;}
            	else if(this->type=="UQ" && heap[right]->getPriority()>heap[left]->getPriority()){target=right;}
            }
            else{target=left;}

            if((this->type=="TQ" && heap[target]->getTime()<temp->getTime())){
                heap[i]=heap[target];
                heap[i]->time_hook=i;
                i=target;
            }
            else if(this->type=="UQ" && heap[target]->getPriority()>temp->getPriority()){
            	heap[i]=heap[target];
            	heap[i]->urgent_hook=i;
            }
            else{break;}
        }
        if(this->type=="TQ"){temp->time_hook=i;}
        else{temp->urgent_hook=i;}
        heap[i]=temp;
        i--;
    }
}

void ElegantQueue::percTop(){
	int spot=heap.size()-1;
	eJob* temp = heap[spot];
    while(spot>=1){
    	if(this->type=="TQ" && heap[(spot-1)/2]->getTime()>temp->getTime()){
    		heap[(spot-1)/2]->time_hook=spot;
      		heap[spot]=heap[(spot-1)/2];
      		spot--;
      		spot /= 2;
      	}
    	else if(this->type=="UQ" && heap[(spot-1)/2]->getPriority()<temp->getPriority()){
    		heap[(spot-1)/2]->urgent_hook=spot;
    		heap[spot]=heap[(spot-1)/2];
    		spot--;
    		spot /= 2;
    	}
	}
    if(type=="TQ"){temp->time_hook=spot;}
    else{temp->urgent_hook=spot;}
    heap[spot]=temp;
}

const eJob* ElegantQueue::top(){
    eJob* returner=heap[0];
    heap[0]=heap[heap.size()-1];
    heap[heap.size()-1]=returner;
    this->pop();
    return returner;
}
