#include <cstdlib>
#include <iostream>
#include <vector>

class Course {
public:
	Course();
	Course(const std::vector<std::string>& input);

	//Accessors
	const std::string& getCRN() const;
	const std::string& getdept() const;
	const std::string& getname() const;
	const std::string& getnum() const;
	std::string getday() const;
	const std::string& gettime_in() const;
	const std::string& gettime_out() const;
	const std::string& getroom() const;
	const unsigned int checktime() const;

private:
	std::string CRN;
	std::string dept;
	std::string num;
	std::string name;
	std::string day;
	std::string time_in;
	std::string time_out;
	std::string room;
};

int DaytoNum(const std::string& str);

bool DeptSort(const Course& Course1, const Course& Course2);

bool RoomSort(const Course& Course1, const Course& Course2);