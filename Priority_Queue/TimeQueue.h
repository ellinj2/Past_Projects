#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <iostream>

typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{
	friend class Job;
public:
	//CONSTRUCTOR
	TimeQueue();


	//ACCESSOR
	std::ostream& printHeap(std::ostream& out);
	
	//MODIFIER
	Job* pop();
	void push(Job* job);
	void remove_from_index(tq_hook spot);
	const Job* top();

private:
	tq_hook hook;
	std::vector<Job*> heap;

	void sort();
	void percup(tq_hook spot);
};

#endif
