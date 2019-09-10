#include "Job_extra.h"

//Prints a job, given an output stream
std::ostream& operator<<(std::ostream& out, const eJob* j){
    char time_buff[80]; //C-style buffer for time printing
    std::time_t timestamp = j->getTime();
    struct tm* timeinfo = gmtime(&timestamp); //Needed for printing
    strftime(time_buff,80," time: %c %Z",timeinfo); //Converts timeinfo into a C-string

    out << "Job: \"" << j->getID();
    out << "\" priority: " << j->getPriority();
    out << time_buff << " (" << timestamp << ")"  << " "<<std::endl;
    return out;
}

//Removes a job from whichever UrgentQueue it belongs to
void eJob::removeFromUrgent() { 
    removeFromIndex(urgent_hook, priority_ptr); 
}

//Removes the job from whichever TimeQueue it belongs to
void eJob::removeFromTime() { 
    removeFromIndex(time_hook, time_ptr); 
}

//Constructor for the Job class
eJob::eJob(int pri, std::time_t time){
    //Static variable makes sure we don't re-use IDs
    static int idcount = 1; 

    //Auto-increment ID
    job_id=idcount++;

    priority=pri; 
    timestamp=time; 
}

eJob::eJob(const eJob& j){
    job_id = j.job_id*100; //Tamper-evident copy constructor~
    priority = j.priority;
    timestamp = j.timestamp;
}
