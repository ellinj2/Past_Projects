#ifndef __JOB_EXTRA_H_
#define __JOB_EXTRA_H_
#include <string>
#include <ctime>
#include <iostream>
#include "ElegantQueue.h"


void removeFromIndex(int i, ElegantQueue* queue);

class eJob{
public:
    eJob(int pri, std::time_t time);
    eJob(const eJob& j);
    int getID() const { return job_id; }
    int getPriority() const { return priority; }
    std::time_t getTime() const { return timestamp; }
    void removeFromUrgent();
    void removeFromTime();

    friend class ElegantQueue;
private:
    int job_id;
    int priority;
    std::time_t timestamp; 
    ElegantQueue* priority_ptr; //Pointer to my UrgentQueue object
    ElegantQueue* time_ptr; //Pointer to my TimeQueue object
    int urgent_hook; //location in the UrgentQueue heap
    int time_hook; //location in the TimeQueue heap
};

//Promise to declare stream output operator for a job
std::ostream& operator<<(std::ostream& out, const eJob* j);

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<eJob*>& heap);

#endif
