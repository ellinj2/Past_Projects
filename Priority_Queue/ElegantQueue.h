#ifndef __ElegantQueue_H_
#define __ElegantQueue_H_

#include <vector>
#include <string>
#include <iostream>
#include <ctime>


class eJob; //Extra-credit job announcer

std::ostream& operator<<(std::ostream& out, const std::vector<eJob*>& heap);

class ElegantQueue{
	friend class eJob;
public:
	ElegantQueue(std::string key);

	std::ostream& printHeap(std::ostream& out);


	eJob* pop();
	void push(eJob* item);
	void sendToTop(int i);
	const eJob* top();

private:
	std::vector<eJob*> heap;
	std::string type;

	void sort();
	void percTop();
};

#endif
