#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include "Course.h"

Course::Course(const std::vector<std::string>& input){
	//VALUES
	CRN = input[0];
	dept = input[1];
	num = input[2];
	name = input[3];
	day = input[4];
	time_in = input[5];
	time_out = input[6];
	room = input[7];
}
//Return CRN
const std::string& Course::getCRN() const {
	return CRN;
}
//Return department
const std::string& Course::getdept() const {
	return dept;
}
//Return course number
const std::string& Course::getnum() const {
	return num;
}
//Return course name
const std::string& Course::getname() const {
	return name;
}
//Return day by full word
std::string Course::getday() const {
	if(day == "M"){
		return "Monday";
	}
	if(day == "T"){
		return "Tuesday";
	}
	if(day == "W"){
		return "Wednesday";
	}
	if(day == "R"){
		return "Thursday";
	}
	if(day == "F"){
		return "Friday";
	}
	return "";
}
//Return start time
const std::string& Course::gettime_in() const {
	return time_in;
}
//Return end time
const std::string& Course::gettime_out() const {
	return time_out;
}
//Return room name
const std::string& Course::getroom() const {
	return room;
}
//Returns time in military standard for comparisons
const unsigned int Course::checktime() const{
	unsigned int hour = std::stoi(time_in.substr(0,2));
	unsigned int min = std::stoi(time_in.substr(3,5));
	if(time_in.substr(5,7) == "PM" && hour != 12){
		hour += 12;
	}
	std::cout<<name<<" at: "<<hour*100 + min<<std::endl;
	return hour*100 + min;
}

//Converts days to numbers for comparisons
int DaytoNum(const std::string& str){
	if(str == "Monday"){
		return 0;
	}
	if(str == "Tuesday"){
		return 1;
	}
	if(str == "Wednesday"){
		return 2;
	}
	if(str == "Thursday"){
		return 3;
	}
	if(str == "Friday"){
		return 4;
	}
	else{
		return 10;
	}
}
//Sort for department search
bool DeptSort(const Course& Course1, const Course& Course2){
	if(Course1.getnum() < Course2.getnum()){
		return true;
	}
	if(Course1.getnum() == Course2.getnum()){
		if(DaytoNum(Course1.getday()) < DaytoNum(Course2.getday())){
			return true;
		}
		if(DaytoNum(Course1.getday()) == DaytoNum(Course2.getday())){
			if(Course1.checktime() < Course2.checktime()){
				return true;
			}
		}
	}
	return false;
}
//Sort for room search
bool RoomSort(const Course& Course1, const Course& Course2){
	if(DaytoNum(Course1.getday()) < DaytoNum(Course2.getday())){
		return true;
	}
	if(DaytoNum(Course1.getday()) == DaytoNum(Course2.getday())){
			if(Course1.checktime() < Course2.checktime()){
				return true;
			}
			if(Course1.gettime_in() == Course2.gettime_in()){
				if(Course1.getnum() < Course2.getnum()){
					return true;
				}
				if(Course1.getnum() == Course2.getnum()){
					if(Course1.getdept() < Course2.getdept()){
						return true;
					}
				}
			}
		}
	return false;
}