#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>



int main(int argc, char* argv[]){
	if(argc!=4){fprintf(stderr, "Incorrect usage: Should be Method, algorithm, file\n"); return EXIT_FAILURE;}
	int associativity=atoi(argv[1]);
	if(associativity!=1 && associativity!=2 && associativity != 4){fprintf(stderr, "Incorrect method type\n"); return EXIT_FAILURE;}
	
	int i, j;
	char* algo=argv[2];
	int cacheSets=256/associativity;
	int hits=0;
	int misses=0;
	int accesses=0;

	printf("Cache size: %d\n", 256);
	printf("Cache associativity: %d\n", associativity);
	printf("Cache sets: %d\n", cacheSets);
	printf("Cache algorithm: %s\n", algo);

	FILE* f=fopen(argv[3], "r");
	if(!f){fprintf(stderr,"Couldn't open file\n");}
	size_t len;
	ssize_t read;

	uint32_t cache[cacheSets][associativity]; //e.g. 256x1, 128x2, 64x4
	for(i=0; i<cacheSets; i++){
		for(j=0; j<associativity; j++){
			cache[i][j]=0;
		}
	}

	char* input;
		while((read=getline(&input, &len, f))!=-1){
			accesses++;
			uint32_t raw_address=strtoul(input, NULL, 0);
			int memAccess=raw_address%cacheSets;

			//Go through each set at the index
			for(i=0; i<associativity; i++){
				//If found
				if(cache[memAccess][i]==raw_address){
					//Move everything down
					for(j=i; j<associativity-1; j++){
						cache[memAccess][j]=cache[memAccess][j+1];
					}
					cache[memAccess][associativity-1]=raw_address;
					printf("%" PRIu32 " (hit)\n", raw_address);
					hits++;
					break;
				}
			}
			//If value not found
			if(i==associativity){
				//Pop first value and move everything down
				for(i=0; i<associativity-1; i++){
					cache[memAccess][i]=cache[memAccess][i+1];
				}
				cache[memAccess][associativity-1]=raw_address;
				printf("%" PRIu32 "(miss)\n", raw_address);
				misses++;
			}
		}

	if(strcmp(algo, "LRU")==0){
		char* input;
		while((read=getline(&input, &len, f))!=-1){
			accesses++;
			uint32_t raw_address=strtoul(input, NULL, 0);
			int memAccess=raw_address%cacheSets;

			//Go through each set at the index
			for(i=0; i<associativity; i++){
				//If found
				if(cache[memAccess][i]==raw_address){
					//Move everything down
					for(j=i; j<associativity-1; j++){
						cache[memAccess][j]=cache[memAccess][j+1];
					}
					cache[memAccess][associativity-1]=raw_address;
					printf("%" PRIu32 " (hit)\n", raw_address);
					hits++;
					break;
				}
			}
			//If value not found
			if(i==associativity){
				//Pop first value and move everything down
				for(i=0; i<associativity-1; i++){
					cache[memAccess][i]=cache[memAccess][i+1];
				}
				cache[memAccess][associativity-1]=raw_address;
				printf("%" PRIu32 "(miss)\n", raw_address);
				misses++;
			}
		}
	}
	else if(strcmp(algo,"Belady")==0){
		//Run Belady instructions
		//If replacement needed, look ahead for any that could be replaced

		char* input;
		while((read=getline(&input, &len, f))!=-1){
			
		}
	}
	else{fprintf(stderr, "Incorrect algorithm type\n"); return EXIT_FAILURE;}

	printf("Cache accesses: %d\n",accesses);
	printf("Cache hits: %d\n", hits);
	printf("Cache misses: %d\n", misses);
	printf("Overall hit rate: %.6f\n", (float)hits/(float)accesses);

	fclose(f);

	return EXIT_SUCCESS;
}
