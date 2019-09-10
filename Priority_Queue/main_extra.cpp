#include <cassert>
#include <fstream> //For file I/O
#include <iostream> //For std::cerr
#include <string> //For parsing
#include <ctime> //For std::time_t
#include <list>
#include "ElegantQueue.h"
#include "Job_extra.h"

//Prints a heap represented as a vector to out
std::ostream& operator<<(std::ostream& out, const std::vector<eJob*>& heap){
    out << heap.size() << " jobs:" << std::endl;
    for(std::size_t i=0; i<heap.size(); i++){
        out << "\t" << heap[i];
    }
    return out;
}

void removeFromIndex(int i, ElegantQueue* queue){
    queue->sendToTop(i);
    queue->pop();
}

//Add a job to both queues
void AddToQueue(ElegantQueue& uq, ElegantQueue& tq, eJob* job){
    uq.push(job);
    tq.push(job);
}

//Remove the highest urgency Job from the queues
void GetNextUrgent(ElegantQueue& uq){
    eJob* tmp = uq.pop();
    tmp->removeFromTime();
}

//Remove the oldest Job from the queues
void GetNextTime(ElegantQueue& tq){
    eJob* tmp = tq.pop();
    tmp->removeFromUrgent();
}

int main(int argc, char** argv){
    if(argc != 3){
        std::cerr << "Correct usage is " << argv[0] << " [input file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream infile(argv[1]);
    if(!infile){
        std::cerr << "Could not open " << argv[1] << " for reading!";
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Could not open " << argv[2] << " for writing!";
        return -1;
    }

    /* "jobs" must be a list so that we don't reallocate, 
     * since that would COPY jobs. We will pass around pointers
     * instead of duplicating jobs when we want to interact with the queues. */
    std::list<eJob*> jobs; 
    ElegantQueue uq("UQ");
    ElegantQueue tq("TQ");

    std::string token;

    while(infile >> token){
        if(token == "add-job"){
            int priority;
            std::time_t timestamp;
            infile >> priority >> timestamp;
            jobs.push_back(new eJob(priority,timestamp));
            AddToQueue(uq,tq,jobs.back());
        }
        else if(token == "print-by-urgent"){
            uq.printHeap(outfile);
        }
        else if(token == "print-by-time"){
            tq.printHeap(outfile);
        }
        else if(token == "print-next-urgent"){
            const eJob* j = uq.top();
            outfile << j;
        }
        else if(token == "print-next-age"){
            const eJob* j = tq.top();
            outfile << j;
        }
        else if(token == "remove-next-urgent"){
            GetNextUrgent(uq);
        }
        else if(token == "remove-next-age"){
            GetNextTime(tq);
        }
        else{
            std::cerr << "Invalid/unexpected input token " << token << std::endl;
            return -1;
        }
    }

    //Make sure that we didn't copy jobs during any operations
    eJob validator(0,0);
    assert(validator.getID()-1 == int(jobs.size()));

    for(std::list<eJob*>::iterator it = jobs.begin(); it!=jobs.end(); it++){
        delete *it;
    }

    return 0;
}
