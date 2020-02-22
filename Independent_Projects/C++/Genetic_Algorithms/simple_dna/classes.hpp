/*

Basic genetic algorithm to produce the best dna (most "ACGT" sequences)

*/
extern int mutation_rate;

#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <time.h>

class genome;
class dna;

char purines[4]={'A','C','G','T'};

char randBase(const char bases[]){
	int val=rand()%4;
	return bases[val];
}

class genome{
private:
	char bases[8];
	dna* parent;

	void copy_genes(genome& source){
		for(int i=0; i<8; i++){
			this->bases[i]=source.get_bases()[i];
		}
	}

public:

	genome(){
		this->parent=NULL;
		for(int i=0; i<8; i++){
			this->bases[i]=randBase(purines);
		}
	}

	genome(dna* par){
		this->parent=par;
		for(int i=0; i<8; i++){
			this->bases[i]=randBase(purines);
		}
	}

	genome(genome& mom, genome& dad, dna* par){
		int randint=rand()%2;
		if(randint==1){
			this->copy_genes(mom);
		}
		else{
			this->copy_genes(dad);
		}
		this->mutate();
		this->parent=par;
	}

	void mutate(){
		for(int i=0; i<8; i++){
			int val=rand()%100;
			if(val<=mutation_rate){
				this->bases[i]=randBase(purines);
				return;
			}
		}
	}

	int score(){
		int result=0;
		for(int i=0; i<8; i++){
			if(this->bases[i]==purines[i%4]){
				result++;
			}
		}
		return result;
	}

	char* get_bases(){
		return &(this->bases[0]);
	}

	void print(){
		for(int i=0; i<8; i++){
			std::cout<<this->bases[i];
		}
		std::cout<<" "<<this->score()<<std::endl;
	}

};


class dna{
private:
	genome* sequence;


public:
	dna(){
		this->sequence=new genome[20];
		for(int i=0; i<20; i++){
			this->sequence[i]=genome(this);
		}
	}

	dna(dna* mom, dna* dad){
		this->sequence=new genome[20];
		for(int i=0; i<20; i++){
			this->sequence[i]=genome((*mom)[i], (*dad)[i], this);
		}
	}

	int score()const{
		int result=0;
		for(int i=0; i<20; i++){
			result+=this->sequence[i].score();
		}
		return result;
	}

	genome& operator[](int i){
		return this->sequence[i];
	}

	void print(){
		for(int i=0; i<20; i++){
			std::cout<<"Genome "<<i+1<<": ";
			this->sequence[i].print();
		}
	}

	~dna(){
		delete this->sequence;
	}

};


