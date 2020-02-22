#include "classes.hpp"
#include <list>
#include <algorithm>

int mutation_rate;

void populate(std::list<dna*>& vec, int cap){
	for(int i=0; i<cap; i++){
		vec.push_back(new dna());
	}
}

void repopulate(std::list<dna*>& vec, dna* pool[5]){
	std::list<dna*>::iterator itr=vec.begin();
	for(int i=0; i<5; i++){itr++;}
	for(int i=0; i<5 && itr!=vec.end(); i++){
		for(int j=i; j<5 && itr!=vec.end(); j++){
			*itr=new dna(pool[i],pool[j]);
			itr++;
		}
	}
	if(itr!=vec.end()){
		while(itr!=vec.end()){
			*itr=new dna();
			itr++;
		}
	}
}

void print_gen(std::list<dna*>& generation, int num){
	std::cout<<"Generation "<<num<<", best scores: ";
	int i=0;
	for(std::list<dna*>::iterator itr=generation.begin(); i<5; i++,itr++){
		std::cout<<(*itr)->score();
		if(i!=4){std::cout<<", ";}
	}
	std::cout<<std::endl;
}


int main(int argc, char* argv[]){
	if(argc!=4){std::cerr<<"ERROR: Invalid command line arguments. Should be file.exe generation_size(int) mutation_rate(int 0-100) perfection_percent(0-100)"<<std::endl; return 1;}
	int generation_size=atoi(argv[1]);
	mutation_rate=atoi(argv[2]);
	float perfection_percent=((float)atoi(argv[3]))/100;
	srand(time(NULL));

	int genCount=1;

	std::list<dna*> generation;
	populate(generation, generation_size);
	generation.sort([](const dna* dna1, const dna* dna2){
		return dna1->score()>dna2->score();
	});
	std::list<dna*>::iterator itr=generation.begin();
	for(int run=0; run<199; run++){itr++;}
	std::cout<<"Worst initial dna sequence:"<<std::endl;
	(*itr)->print();
	std::cout<<std::endl<<std::endl;
	while((float)(*generation.begin())->score()<(float)(8*20)*perfection_percent){
		dna* pool[5];
		int i=0;
		for(std::list<dna*>::iterator itr=generation.begin(); itr!=generation.end(); i++, itr++){
			if(i<5){
				pool[i]=*itr;
			}
			else{
				delete *itr;
			}
		}
		repopulate(generation,pool);
		generation.sort([](const dna* dna1, const dna* dna2){
			return dna1->score()>dna2->score();
		});
		genCount++;
	}
	std::cout<<std::endl<<"It took "<<genCount<<" generations to reach "<<perfection_percent*100<<"%% perfection!"<<std::endl;
	(*generation.begin())->print();
	return 0;
}