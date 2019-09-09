#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Course.h"

std::vector<std::string> roomset(const std::vector<Course>& all_courses){
	/*Create set of all rooms*/
	std::vector<std::string> rooms;
	for(unsigned int i=0; i<all_courses.size(); i++){
		bool inrooms = false;
		for(unsigned int o=0; o<rooms.size(); o++){
			if(all_courses[i].getroom() == rooms[o]){
				inrooms = true;
			}		
		}
		if(!inrooms){
			rooms.push_back(all_courses[i].getroom());
		}
	}
	std::sort(rooms.begin(), rooms.end());
	return rooms;
}

std::vector<std::string> deptset(const std::vector<Course>& all_courses){
	/*Create set of all departments*/
	std::vector<std::string> depts;
	for(unsigned int i=0; i<all_courses.size(); i++){
		bool indepts = false;
		for(unsigned int j=0; j<depts.size(); j++){
			if(all_courses[i].getdept() == depts[j]){
				indepts = true;
			}
		}
		if(!indepts){
			depts.push_back(all_courses[i].getdept());
		}
	}
	std::sort(depts.begin(), depts.end());
	return depts;
}

std::vector<std::string> stringset(const std::vector<std::string>& all_strings){
	/*Create set for custom output*/
	std::vector<std::string> strings;
	for(unsigned int i=0; i<all_strings.size(); i++){
		bool instrings = false;
		for(unsigned int j=0; j<strings.size(); j++){
			if(all_strings[i] == strings[j]){
				instrings = true;
			}
		}
		if(!instrings){
			strings.push_back(all_strings[i]);
		}
	}
	std::sort(strings.begin(), strings.end());
	return strings;
}

void custom(const std::vector<Course>& all_courses, char**& argv, const int& argc){
	/*Returns the most popular departments by room*/
	std::ofstream out_file(argv[2]);
	if(!out_file.good()){
		std::cerr<<"ERROR: Can't open output file"<<std::endl;
		exit(1);
	}
	if(all_courses.size() == 0){
		out_file<<"No data available.";
		return;	
	}
	//Make list of all rooms
	std::vector<std::string> all_rooms = roomset(all_courses);
	//Make list of all departments
	std::vector<std::string> all_depts = deptset(all_courses);
	//Make list of departments by room
	std::vector<std::vector<std::string>> by_rooms;
	//Populate by_rooms
	for(unsigned int r=0; r<all_rooms.size(); r++){
		std::vector<std::string> current_room;
		for(unsigned int c=0; c<all_courses.size(); c++){
			if(all_courses[c].getroom() == all_rooms[r]){
				current_room.push_back(all_courses[c].getdept());
			}
		}
		std::sort(current_room.begin(), current_room.end());
		by_rooms.push_back(current_room);
	}
	//Do the big maths
	for(unsigned int i=0; i<by_rooms.size(); i++){//Go through each room
		unsigned int size = stringset(by_rooms[i]).size();//Number of individual departments in room
		if(size == 0){//Error check
			out_file<<"No departments were found for "<<all_rooms[i]<<std::endl;
			out_file<<"------------------------------"<<std::string(all_rooms[i].length(), '-')<<std::endl;
		}
		else{
			std::vector<std::string> nones; //Holds departments with no occurances
			if(size == 1){//Grammar check
				out_file<<"There is "<<size<<" department in "<<all_rooms[i]<<std::endl;
				std::string temp1(std::to_string(size).length(), '-');//Column break with padding
				std::string temp2(all_rooms[i].length(), '-');//Column break with padding
				out_file<<"---------"<<temp1<<"---------------"<<temp2<<std::endl;
			}
			else{//Same as before but with different grammar
				out_file<<"There are "<<size<<" departments in "<<all_rooms[i]<<std::endl;
				std::string temp1(std::to_string(size).length(), '-');
				std::string temp2(all_rooms[i].length(), '-');
				out_file<<"----------"<<temp1<<"---------------"<<temp2<<std::endl;
			}
			out_file<<"Department name"<<" | "<<"# of courses"<<std::endl; //Column headers
			//Create list of all counts
			std::vector<unsigned int> counts;
			for(unsigned int j=0; j<all_depts.size(); j++){
				counts.push_back(std::count(by_rooms[i].begin(), by_rooms[i].end(), all_depts[j]));
			}
			std::sort(counts.begin(), counts.end(), std::greater<int>());
			//Create list of departments that have already been written
			std::vector<std::string> written;
			for(unsigned int k=0; k<counts.size(); k++){
				for(unsigned int j=0; j<all_depts.size(); j++){//Go through every department
					for(unsigned int m=0; m<written.size(); m++){
						if(written.size()!=0){
						}
					}
					unsigned int count = std::count(by_rooms[i].begin(), by_rooms[i].end(), all_depts[j]);//Find how many times that department appears
					if(count == counts[k]){//If it exists, write it to file
						bool iswritten = false;//Flag for in written list
						for(unsigned int m=0; m<written.size(); m++){
							if(all_depts[j] == written[m]){
								iswritten = true;
							}
						}
						if(!iswritten){//Only if it doesn't already exist
							written.push_back(all_depts[j]);
							std::string temp1(15 - all_depts[j].length(), ' ');
							std::string temp2(10 - std::to_string(count).length(), ' ');
							out_file<<all_depts[j]<<temp1<<" | "<<count<<temp2<<std::endl;
							std::string temp3(std::to_string(size).length(), '-');
							std::string temp4(all_rooms[i].length(), '-');
							out_file<<"----------"<<temp3<<"---------------"<<temp4<<std::endl;
						}
					}
				}
				// else{//Add to list of non-existents
					// nones.push_back(all_depts[j]);
				// }
			}
			// if(nones.size()>0){//Write all non-existent departments
				// for(unsigned int j=0; j<nones.size(); j++){
					// std::string temp1(15 - all_depts[j].length(), ' ');
					// std::string temp2(9, ' ');
					// out_file<<all_depts[j]<<temp1<<" | "<<0<<temp2<<std::endl;
					// std::string temp3(std::to_string(size).length(), '-');
					// std::string temp4(all_rooms[i].length(), '-');
					// out_file<<"----------"<<temp3<<"---------------"<<temp4<<std::endl;
				// }
			// }
		}
		out_file<<std::endl;
	}
}

void by_dept(const std::vector<Course>& inputs, char**& argv, const int& argc){
	//Finish initializing the search parameters
	std::vector<Course> all_courses = inputs;
	if(argc != 5){
		return;
	}
	std::ofstream out_file(argv[2]);
	if(!out_file.good()){
		std::cerr<<"ERROR: Can't open output file"<<std::endl;
		exit(1);
	}
	if(inputs.size() == 0){
		out_file<<"No data available.";
		return;	
	}
	std::string dept = argv[4];
	//Do the big maths
	std::sort(all_courses.begin(), all_courses.end(), DeptSort);
	//Generate list of maximum lengths
	std::vector<int> max_lens;
	for(unsigned int i=0; i<5; i++){
		max_lens.push_back(0);
	}
	//Populate max lengths
	for(unsigned int i=0; i<all_courses.size(); i++){
		if(all_courses[i].getnum().size() > max_lens[0]){
			max_lens[0] = all_courses[i].getnum().size();
		}
		if(all_courses[i].getname().size() > max_lens[1]){
			max_lens[1] = all_courses[i].getname().size();
		}
		if(all_courses[i].getday().size() > max_lens[2]){
			max_lens[2] = all_courses[i].getday().size();
		}
		if(all_courses[i].gettime_in().size() > max_lens[3]){
			max_lens[3] = all_courses[i].gettime_in().size();
		}
		if(all_courses[i].gettime_out().size() > max_lens[4]){
			max_lens[4] = all_courses[i].gettime_out().size();
		}
	}
	//Write desired department
	out_file<<"Dept "<<dept<<std::endl;
	//Create column heads
	std::string datatypes[5] = {"Coursenum", "Class Title", "Day", "Start Time", "End Time"};
	//Reset max lengths
	for(unsigned int i=0; i < 5; i++){
		if(datatypes[i].length() > max_lens[i]){
			max_lens[i] = datatypes[i].length();
		}
	}
	//Write column headers with padding
	for(unsigned int i=0; i<5; i++) {
		out_file<<datatypes[i];
		if(datatypes[i].length() != max_lens[i]){
			std::string pad(max_lens[i] - datatypes[i].length(), ' ');
			out_file<<pad;
		}
		if(i != 4){
			out_file<<"  ";
		}
	}
	//Write column breaks with padding
	out_file<<std::endl;
	for(unsigned int i=0; i<5; i++){
		std::string bar(max_lens[i], '-');
		out_file<<bar;
		if(i!=4){
			out_file<<"  ";
		}
	}
	//Write course info with padding
	out_file<<std::endl;
	for(unsigned int i=0; i<all_courses.size(); i++){
		std::string info[5] = {all_courses[i].getnum(), all_courses[i].getname(), all_courses[i].getday(), all_courses[i].gettime_in(), all_courses[i].gettime_out()};
		for(unsigned int j=0; j<5; j++){
			out_file<<info[j];
			if(max_lens[j] - info[j].size() != 0){
				std::string pad(max_lens[j] - info[j].size(), ' ');
				out_file<<pad;
			}
			if(j!=4){
				out_file<<"  ";
			}
		}
		out_file<<std::endl;
	}
	out_file<<all_courses.size()<<" entries"<<std::endl<<std::endl;
}

void by_room(const std::vector<Course>& all_courses, char**& argv, const int& argc){
	//Finish initializing the search parameters
	std::string room;
	if(argc == 5){
		room = argv[4];
	}
	std::ofstream out_file(argv[2]);
	if(!out_file.good()){
		std::cerr<<"ERROR: Can't open output file"<<std::endl;
		exit(1);
	}
	if(all_courses.size() == 0){
		out_file<<"No data available.";
		return;	
	}
	//Make list of all rooms
	std::vector<std::string> all_rooms = roomset(all_courses);
	//Sort courses into respective rooms
	std::vector<std::vector<Course>> by_rooms; //list of lists of Courses. lists are associated to room indexed in set->vector all_rooms
	for(unsigned int r=0; r<all_rooms.size(); r++){
		std::vector<Course> current_room;
		for(unsigned int c=0; c<all_courses.size(); c++){
			//Add the course to the room indexed if course.name is the same as the room indexed
			if(all_courses[c].getroom() == all_rooms[r]){
				current_room.push_back(all_courses[c]);
			}
		}
		std::sort(current_room.begin(), current_room.end(), RoomSort);
		by_rooms.push_back(current_room);
	}
	//Do the big maths
	for(unsigned int i=0; i<by_rooms.size(); i++){//Go through each room
		//Generate vector with maximum lengths for data strings (list of lists of integers. ints are lengths, lists are datatypes)
		std::vector<int> max_lens;
		for(unsigned int z=0; z<6; z++){
				max_lens.push_back(0);
		}
		//Populate values for max_lens
		for(unsigned int u=0; u<by_rooms[i].size(); u++){//Go through each course
			if(by_rooms[i][u].getdept().size()>max_lens[0]){
				max_lens[0] = by_rooms[i][u].getdept().size();
			}
			if(by_rooms[i][u].getnum().size()>max_lens[1]){
				max_lens[1] = by_rooms[i][u].getnum().size();
			}
			if(by_rooms[i][u].getname().size()>max_lens[2]){
				max_lens[2] = by_rooms[i][u].getname().size();
			}
			if(by_rooms[i][u].getday().size()>max_lens[3]){
				max_lens[3] = by_rooms[i][u].getday().size();
			}
			if(by_rooms[i][u].gettime_in().size()>max_lens[4]){
				max_lens[4] = by_rooms[i][u].gettime_in().size();
			}
			if(by_rooms[i][u].gettime_out().size()>max_lens[5]){
				max_lens[5] = by_rooms[i][u].gettime_out().size();
			}
		}
		//Write the name of the room
		out_file<<"Room "<<all_rooms[i]<<std::endl;
		//Set max lengths for column names
		std::vector<std::string> datatypes = {"Dept", "Coursenum", "Class Title", "Day", "Start Time", "End Time"};
		for(unsigned int j=0; j<datatypes.size(); j++){
			if(datatypes[j].length() > max_lens[j]){
				max_lens[j] = datatypes[j].length();
			}
		}
		//Write column names with padding
		for(unsigned int j=0; j<datatypes.size(); j++){
			out_file<<datatypes[j];
			if(max_lens[j] - datatypes[j].size() != 0){
				std::string temp(max_lens[j] - datatypes[j].length(), ' ');
				out_file<<temp;
			}
			if(j!=datatypes.size()-1){
				out_file<<"  ";
			}
		}
		//Write column break with padding
		out_file<<std::endl;
		for(unsigned int j=0; j<max_lens.size(); j++){
			std::string temp(max_lens[j], '-');
			out_file<<temp;
			if(j!=max_lens.size()-1){
				out_file<<"  ";
			}
		}
		//Write information for each course with padding
		out_file<<std::endl;
		std::string pad[6] ={"", "", "", "", "", ""};
		for(unsigned int j=0; j<by_rooms[i].size(); j++){
			Course cur = by_rooms[i][j];
			std::string info[6] = {cur.getdept(), cur.getnum(), cur.getname(), cur.getday(), cur.gettime_in(), cur.gettime_out()};
			for(unsigned int k=0; k<6; k++){
				out_file<<info[k];
				if(info[k].length() != max_lens[k]){//Checks for padding
					std::string temp(max_lens[k] - info[k].length(), ' ');
					out_file<<temp;
				}
				if(k!=5){
					out_file<<"  ";
				}
			}
			out_file<<std::endl;
		}
		out_file<<by_rooms[i].size()<<" entries"<<std::endl<<std::endl;;
	}
}

void data_mine(const std::vector<Course>& all_courses, char**& argv, const int& argc){
	/*Does the main data management for the program*/
	//Setup CLAs
	if(argc < 4){
		std::cerr<<"ERROR: Not enough CLAs"<<std::endl;
		exit(1);
	}
	std::string searching(argv[3]);
	if(searching == "room"){
		//Populate file for room search
		by_room(all_courses, argv, argc);
	}
	else if(searching == "dept"){
		by_dept(all_courses, argv, argc);
	}
	else if(searching == "custom"){
		custom(all_courses, argv, argc);
	}
}

int main(int argc, char** argv){
	//Setup future vars
	std::ifstream file_in (argv[1]);
	if(!file_in.good()){
		std::cerr<<"ERROR: Can't open input file"<<std::endl;
		exit(1);
	}
	std::string searching(argv[3]);
	//Set up operations
	std::vector<Course> all_courses;
	std::string temp_str;
	bool good = true;//Check if it's the end of the file while reading
	while(!file_in.eof()){
		//Creates info vector for current course line
		std::vector<std::string> current_course;
		for(unsigned int i=0; i<8; i++){
			file_in >> temp_str;
			if(i == 0 && file_in.eof()){//Checks if it's the end of the file while reading
				good = false;
				break;
			}
			current_course.push_back(temp_str);
		}
		if(!good){//For security
			break;
		}
		if(current_course[4].size()>1){//Checks if there are multiple days
			if(argc == 5){//Checks if there's a specific search parameter
				std::string search(argv[4]);
				//Check if the course is valid and splits it across days
				if((searching == "room" && current_course[7] == search) or (searching == "dept" && current_course[1] == search)){
					std::vector<std::string> split_course;
					split_course = current_course;
					split_course[4] = current_course[4][1];
					current_course[4] = current_course[4][0];
					all_courses.push_back(Course(split_course));
				}
			}
			//Splits anyway
			else{
				std::vector<std::string> split_course;
				split_course = current_course;
				split_course[4] = current_course[4][1];
				current_course[4] = current_course[4][0];
				all_courses.push_back(Course(split_course));
			}
		}
		//Adds course to list if a specific search is passed
		if(argc == 5){
			if(searching == "room" && current_course[7] == argv[4]){
				all_courses.push_back(Course(current_course));
			}
			else if(searching == "dept" && current_course[1] == argv[4]){
				all_courses.push_back(Course(current_course));
			}
		}
		//Adds course anyway
		else{
			all_courses.push_back(Course(current_course));
		}
	}
	//Do the hard maths
	data_mine(all_courses, argv, argc);
	return 0;
}