#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

void write(std::vector<std::vector<char>> grid, std::ofstream& out_file){
	/*writes the grid to the out_file character by character, line by line*/
	for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			out_file<<grid[i][j];
		}
		out_file<<std::endl;
	}
}

std::vector<std::vector<char>> dilate(std::vector<std::vector<char>> grid, char init){
	/*Runs the dilation function, adding new "init" characters in a plus around any current "init" characters*/
	std::vector<std::vector<char>> copy = grid;//Copying input grid for output
	for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			//Check to make sure the image needs expanding here
			if(grid[i][j] == init){
				//Making sure it's not going beyond vector size
				if(i+1 != grid.size()){
					copy[i+1][j] = init;
				}
				//Making sure it's not going beyond vector size
				if(i != 0){
					copy[i-1][j] = init;
				}
				//Making sure it's not going beyond vector size
				if(j+1 != grid[i].size()){
					copy[i][j+1] = init;
				}
				//Making sure it's not going beyond vector size
				if(j != 0){
					copy[i][j-1] = init;
				}
			}
		}
	}
	return copy;
}

std::vector<std::vector<char>> erode(std::vector<std::vector<char>> grid, char init, char outit){
	/*Runs the erosion function, removing "init" characters in a plus around any current "init" character as long as it's not removing from the center*/
	std::vector<std::vector<char>> copy = grid; //Copying input grid for output
	for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			if(grid[i][j] == init){
				unsigned int count = 0;
				//Making sure it's not going beyond vector size
				if(i+1 != grid.size() and grid[i+1][j] == init){
					count++;
				}
				//Making sure it's not going beyond vector size
				if(i != 0 and grid[i-1][j] == init){
					count++;
				}
				//Making sure it's not going beyond vector size
				if(j+1 != grid[i].size() and grid[i][j+1] == init){
					count++;
				}
				//Making sure it's not going beyond vector size
				if(j != 0 and grid[i][j-1] == init){
					count++;
				}
				if(1 <= count and count <= 3){
					copy[i][j] = outit;
				}
			}
		}
	}
	return copy;
}

std::vector<std::vector<char>> close(std::vector<std::vector<char>> grid, char init, char outit){
	/*Runs the closing function, which dilates then erodes*/
	std::vector<std::vector<char>> copy = grid; //Copying input grid for output
	std::vector<std::vector<char>> dilated = dilate(copy, init);
	return erode(dilated, init, outit);
}

std::vector<std::vector<char>> open(std::vector<std::vector<char>> grid, char init, char outit){
	/*Runs the opening function, which erodes then dilates*/
	std::vector<std::vector<char>> copy = grid; //Copying input grid for output
	std::vector<std::vector<char>> eroded = erode(copy, init, outit);
	return dilate(eroded, init);
}

std::vector<std::vector<char>> replace(std::vector<std::vector<char>> grid, char init, char outit){
	/*Runs the replacing function, which replaces all "init" characters with "outit" characters*/
	std::vector<std::vector<char>> copy = grid; //Copying input grid for output
	for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			if(grid[i][j] == init){
				copy[i][j] = outit;
			}
		}
	}
	return copy;
}

int main(int argc, char** argv){
	std::string func = argv[3]; //Pulls down the function CLA
	char outit;
	char init = argv[4][0]; //Pulls down the "init" CLA
	if(argc == 6){
		outit = argv[5][0]; //Pulls down the "outit" CLA (if it exists)
	}
	std::ifstream file_in (argv[1]); //Pulls down the input file CLA
	//Generate error if input file can't be opened
	if(!file_in.good()){
		std::cerr<<"Can't open the file: "<< argv[1] <<std::endl;
		exit(1);
	}
	std::ofstream output(argv[2]); //Pulls down output file CLA
	//Generate error if output file can't be opened
	if(!output.good()){
		std::cerr<<"Can't open the file: "<<argv[2]<<std::endl;
		exit(1);
	}
	std::vector<std::vector<char>> grid;
	std::string temp;//Temporary string to pull out of input file to put into grid
	while (file_in >> temp)
	{
		std::vector<char> temp_row(temp.begin(), temp.end());
		grid.push_back(temp_row);
	}
	//Begin function calls...
	if(func == "replace"){
		write(replace(grid, init, outit), output);
	}
	else if(func == "dilation"){
		write(dilate(grid, init), output);
	}
	else if(func == "opening"){
		write(open(grid, init, outit), output);
	}
	else if(func == "closing"){
		write(close(grid, init, outit), output);
	}
	else if(func == "erosion"){
		write(erode(grid, init, outit), output);
	}
	return 0;
}