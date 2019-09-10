#include "TimeQueue.h"
#include "Job.h"


std::ostream& TimeQueue::printHeap(std::ostream& out){
    out<<"TQ ";
    operator<<(out, heap);
    return out;
}

TimeQueue::TimeQueue(){
    hook=0;
    heap={};
}


Job* TimeQueue::pop(){
    if(heap.size()==0){std::cerr<<"ERROR IN TimeQueue::pop(): Heap cannot be popped"<<std::endl; exit(1);}
    Job* output = heap[0];
    if(heap.size()==1){
        heap.pop_back();
        return output;
    }
    Job* replacer = heap[heap.size()-1];
    heap[0] = heap[heap.size()-1];
    replacer->time_ptr=0;
    heap[heap.size()-1]=output;
    heap.pop_back();
    if(heap.size()>0){this->sort();}
    return output;
}

void TimeQueue::sort(){
    tq_hook i=(heap.size()-1)/2;
    while(i>=0){
        Job* temp=heap[i];
        unsigned int target, right, left;
        while(2*i+1<int(heap.size())){
            left=2*i+1;
            right=left+1;
            if(right<heap.size() && heap[right]->getTime()<heap[left]->getTime()){target=right;}
            else{target=left;}

            if(heap[target]->getTime()<temp->getTime()){
                heap[i]=heap[target];
                heap[i]->time_hook=i;
                i=target;
            }
            else{break;}
        }
        heap[i]=temp;
        temp->time_hook=i;
        i--;
    }
    for(unsigned int i=(heap.size()-1)/2+1; i<heap.size(); i++){
        heap[i]->time_hook=i;
    }
}

void TimeQueue::percup(tq_hook spot){
    Job* temp=heap[spot];
    while(spot>=1 && heap[(spot-1)/2]->getTime()>temp->getTime()){
      Job* replacer=heap[(spot-1)/2];
      replacer->time_hook=spot;
      heap[spot]=heap[(spot-1)/2];
      spot--;
      spot /= 2;
    }
    heap[spot]=temp;
    temp->time_hook=spot;
}

void TimeQueue::push(Job* job){
    heap.push_back(job);
    job->time_ptr=this;
    this->percup(heap.size()-1);
}

void TimeQueue::remove_from_index(tq_hook spot){
    Job* ptr = heap[spot];
    heap[spot]=heap[heap.size()-1];
    heap[heap.size()-1]=ptr;
    heap.pop_back();
    if(heap.size()>0){this->sort();}
}

const Job* TimeQueue::top(){
    Job* returner=heap[0];
    this->remove_from_index(0);
    return returner;
}