#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//STRUCTS
/* Tree node */
typedef struct Node Node;
struct Node{
  char key;
  int pos;
  Node* left;
  Node* right;
};
void initNode(Node* n){
  n->key=' ';
  n->pos=-1;
  n->left=NULL;
  n->right=NULL;
}

/* Map stored as binary tree */
typedef struct{
  Node* root;
  int size;
}Map;
void initMap(Map* m){
  m->size=1;
  m->root=(Node*)malloc(sizeof(Node));
  initNode(m->root);
}
int insertMap(Node* ptr, char val, int pos){
  if(ptr->key==' '){
    ptr->key=val;
    ptr->pos=pos;
    return 0;
  }
  if(val<ptr->key){
    if(ptr->left==NULL){
      ptr->left = (Node*)malloc(sizeof(Node));
      initNode(ptr->left);
      ptr=ptr->left;
      ptr->key=val;
      ptr->pos=pos;
      return 0;
    }
    return insertMap(ptr->left, val, pos);
  }
  if(val>ptr->key){
    if(ptr->right==NULL){
      ptr->right = (Node*)malloc(sizeof(Node));
      initNode(ptr->right);
      ptr=ptr->right;
      ptr->key=val;
      ptr->pos=pos;
      return 0;
    }
    return insertMap(ptr->right, val, pos);
  }
  return 1;//The value already exists, so we need to offset the position by 1
}
/* Return register number for variable name */
int getMapPos(Node* ptr, char key){
  if(!ptr){return -1;}
  if(key<ptr->key){return getMapPos(ptr->left, key);}
  if(key>ptr->key){return getMapPos(ptr->right, key);}
  return ptr->pos;
}

//FUNCTION DEFINITIONS
/* Check if character is an operator */
int op_checker(char val){
	if(val=='+'||val=='-'||val=='/'||val=='*'||val=='%'){return 1;}
	return 0;
}

/* Remove extra spaces and returns actual size of new string */
size_t prepLine(char* string, size_t size, int* ops){
	int i, j;
	j=0;
	int checker=0;
	for(i=0;i<size;i++){
		if(op_checker(string[i])&&(j>0&&!op_checker(string[j-1]))){(*ops)++;}
		if(string[i]!=' '){
			string[j]=string[i];
			j++;
			if(string[i]==';'){checker=1; break;}
		}
	}
	if(!checker){fprintf(stderr, "Parsing error...\n"); return 0;}
	return j;
}

/* String printer */
void printbuff(char* string, size_t size){
	int i;
	for(i=0; i<size; i++){
		printf("%c", string[i]);
		if(string[i]==';'){break;}
	}
	printf("%c", '\n');
}

/* Power arithmetic */
int int_pow(int base, int exp)
{
    int result = 1;
    while (exp){
        if (exp & 1){result *= base;}
        exp /= 2;
        base *= base;
    }
    return result;
}

/* Check if integer is in an array */
//IN THIS CASE, THIS FUNCTION IS HARDCODED FOR AN ARRAY THAT STORES MULTIPLES OF 2
int pOfTwo(int tester){
	int i;
	int arr[16] = {1};
	for(i=0; i<16; i++){
		if(i>0){arr[i]=2*arr[i-1];}
		if(tester==arr[i]){return i;}
	}
	return 0;
}

int main(int argc, char* argv[]){
	if(argc!=2){fprintf(stderr, "Incorrect argument format >> Should be [executable] [input]\n"); return EXIT_FAILURE;}
	FILE* fp;
	char* buffer = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen(argv[1], "r");
	if(fp==NULL){fprintf(stderr, "File could not be opened\n"); return EXIT_FAILURE;}
	//Trakc register values
	Map registers;
	initMap(&registers);
	int rcount = 0; //Count registers
	int tcount = 0; //Count temporaries
	int lcount = 0; //Count loops
	int initOpcount=0; //Track original opcount
	while((read = getline(&buffer, &len, fp)) != -1){
		//Prepare line for parsing
		int opcount = 0; //Count operands
		if(!islower(buffer[0])){fprintf(stderr, "Parsing error...\n"); return EXIT_FAILURE;}
		printf("# ");
		printbuff(buffer, len);
		len = prepLine(buffer, len, &opcount); //Remove spaces, check if semicolon found, and count operands
		if(initOpcount-opcount<=0){initOpcount=opcount;}
		if(buffer[1]!='=' || !len){fprintf(stderr, "Parsing error...\n"); return EXIT_FAILURE;}
		/* Parse line */
		//Assign registers
		int i;
		for(i=0; i<len; i++){
			if(islower(buffer[i])){
				int found = insertMap(registers.root, buffer[i], rcount);
				if(!found){rcount++;}
			}	
		}
		insertMap(registers.root, buffer[0], rcount);
		/* Conversions! */
		int tchecker = 0; //Check if the previous operation was stored in a temporary register
		for(i=2; i<len; i++){
			while(!(isdigit(buffer[i])||islower(buffer[i]))){i++;} //Only continue for actual values
			// printf("%c: ", buffer[i]);
			// printf("%d\t",opcount);
			/* Convert integer representation to actual integer */
			if(isdigit(buffer[i])){
				//Check if assignment is necessary
				int checker=0;
				int placer = i;
				if(buffer[i-1]=='=' || buffer[i-2]=='='){
					checker=1;
				}
				//Build value
				char* holder = (char*)malloc(sizeof(char));
				int val=0;
				*holder = buffer[i];
				val+=atoi(holder);
				while(isdigit(buffer[i++])){
					val*=10;
					*holder = buffer[i];
					val+=atoi(holder);
				}
				i--; //Bring i back
				val/=10;
				//Load if necessary
				if(checker){
					printf("li $s%d,", getMapPos(registers.root, buffer[0]));
					if(buffer[placer-1]=='-'){printf("-");}
					printf("%d\n",val);
				}
			}
			/* Catch assignment issue */
			if(initOpcount==1&&buffer[i+2]==';'){break;}
			
			if(isdigit(buffer[i+1])||islower(buffer[i+1])){i--;} //Weird bug patch
			/* Register algebra */
			/* Register copy */
			if(opcount==0){i=i;} //Place holder just in case
			else{
				int type=0;
				int tempchecker=0; //For addition and subtraction purposes
				if(buffer[i+1]=='+' || (buffer[i+1]=='-'&&!islower(buffer[i+2]))){
					printf("add"); type=0;
					if(isdigit(buffer[i+2])){printf("i");} //addi
					printf(" ");
				}
				else if(buffer[i+1]=='-'&&islower(buffer[i+2])){printf("sub "); type=1;} //Subtraction
				else if(buffer[i+1]=='*'){if(islower(buffer[i+2])){printf("mult ");} type=2;} //Multiplication
				else if(buffer[i+1]=='/'){if(islower(buffer[i+2])){printf("div ");} type=3;} //Division, return lo
				else if(buffer[i+1]=='%'){if(islower(buffer[i+2])){printf("div ");} type=4;} //Mod, return hi
				if(type<2){
					int offsetter = 1; //offsetter for t register
					if(opcount==1){printf("$s%d,", getMapPos(registers.root, buffer[0]));}
					else{printf("$t%d,", tcount%10); tcount++; tempchecker=1; offsetter++;}
					if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
					else{printf("$t%d,", (tcount-offsetter)%10);}
					tchecker=tempchecker; //Copy tempchecker to higher order checker
				}
				else if(islower(buffer[i+2])){
					if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
					else{printf("$t%d,", (tcount-1)%10);}
				}
				if(islower(buffer[i+2])){
					printf("$s%d\n", getMapPos(registers.root, buffer[i+2]));
					if(type==2 || type==3){
						if(opcount==1){printf("mflo $s%d\n", rcount-1);}
						else{printf("mflo $t%d\n", tcount%10); tcount++; tchecker=1;}
					}
					else if(type==4){
						if(opcount==1){printf("mfhi $s%d\n", rcount-1);}
						else{printf("mfhi $t%d\n", tcount%10); tchecker=1;}
					}
				}
				else{
					char* holder = (char*)malloc(sizeof(char));
					int val=0;
					//Account for negative operands
					char place_holder=buffer[i+2];
					int j;
					if(place_holder=='-'){j=i+3;}
					else{j = i+2;}
					*holder = buffer[j];
					val+=atoi(holder);
					while(isdigit(buffer[j++])){
						val*=10;
						*holder = buffer[j];
						val+=atoi(holder);
					}
					val/=10;
					if(type>1){
						/* Multiplication */
						if(type==2){
							if(val==0){
								if(opcount==1){printf("li $s%d,0\n", getMapPos(registers.root, buffer[0]));}
								else{printf("li $t%d,0\n", tcount%10); tcount++;}
							}
							else if(val==1){
								printf("move $t%d,", tcount%10); tcount++; tempchecker=1;
								if(!tchecker){printf("$s%d\n", getMapPos(registers.root, buffer[i]));}
								else{printf("$t%d\n", (tcount-1)%10);}
								tchecker=tempchecker;
								if(buffer[i+2]=='-'){
									if(opcount==1){
										printf("sub $s%d,$zero,", getMapPos(registers.root, buffer[0]));
										if(!tchecker){printf("$s%d\n", getMapPos(registers.root, buffer[i]));}
										else{printf("$t%d\n", (tcount-1)%10);}
									}
									else{
										printf("sub $t%d,$zero,", (tcount+1)%10);
										if(!tchecker){printf("$s%d\n", getMapPos(registers.root, buffer[i]));}
										else{printf("$t%d\n", (tcount-1)%10);}
									}
								}
								else if(opcount==1){
									printf("move $s%d,$t%d\n", getMapPos(registers.root,buffer[0]), (tcount-1)%10);
								}
							}
							else{
								int j, first;
								first=1; //Check if first iteration
								for(j=15; j>=0; j--){
									int temp=val/int_pow(2,j);
									if(temp==1){
										if(j>0){
											if(!tchecker){printf("sll $t0,$s%d,%d\n", getMapPos(registers.root, buffer[i]), j);}
											else{printf("sll $t1,$t0,%d\n", j);}
											tcount++;
											if(first){printf("move $t1,$t0\n"); first=0;}
											else{printf("add $t1,$t1,$t0\n");}
										}
										else{printf("add $t1,$t1,$s0\n");}
									}
									val%=int_pow(2,j);
								}
								if(opcount==1){
									if(place_holder=='-'){printf("sub $s%d,$zero,$t1\n", getMapPos(registers.root, buffer[0]));}
									else{printf("move $s%d,$t1\n", getMapPos(registers.root, buffer[0]));}
								}
								else{
									if(place_holder=='-'){printf("sub $t%d,$zero,$t1\n", tcount%10); tchecker=1;}
									else{printf("move $t%d,$t1\n", tcount%10); tchecker=1;}	
								}
							}
						}
						/* division and modular */
						else{
							if(val==1){
								if(buffer[i+2]=='-'){
									if(opcount==1){printf("sub $s%d,$zero,", getMapPos(registers.root, buffer[0]));}
									else{printf("sub $t%d,$zero", tcount%10);}
									if(!tchecker){printf("$s%d\n", getMapPos(registers.root, buffer[i]));}
									else{printf("$t%d\n", tcount%10);}
								}
								else{
									if(opcount==1){printf("move $s%d,", getMapPos(registers.root, buffer[0]));}
									else{printf("move $t%d,", tcount%10); tempchecker=1; tcount++;}
									if(!tchecker){printf("$s%d\n", getMapPos(registers.root, buffer[i]));}
									else{printf("$t%d\n", tcount%10);}
									tchecker=tempchecker;
								}
							}
							else{
								int pcheck = pOfTwo(val);
								if(pcheck){
									printf("bltz ");
									if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
									else{printf("$t%d,", (tcount-1)%10);}
									printf("L%d\n", lcount);
									lcount++;
									int potPow=pOfTwo(val);
									if(potPow){
									printf("srl ");
										if(opcount==1){printf("$s%d,", getMapPos(registers.root, buffer[0]));}
										else{tcount++; printf("$t%d,", tcount%10);}
										if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
										else{printf("$t%d,", (tcount-1)%10);}
										printf("%d\n", potPow);
										if(buffer[i+2]=='-'){
											if(opcount==1){printf("sub $s%d,$zero,$s%d\n", getMapPos(registers.root, buffer[0]), getMapPos(registers.root, buffer[0]));}
											else{printf("sub $t%d,$zero,$t%d\n", (tcount-1)%10, (tcount-1)%10);}
										}
										printf("j L%d\n", lcount);
									}
									printf("L%d:\n", lcount-1);
									if(buffer[i+2]=='-'){printf("li $t%d,-%d\n", tcount%10, val); tcount++;}
									else{printf("li $t%d,%d\n", tcount%10, val); tcount++;}
									printf("div ");
									if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
									else{printf("$t%d,", (tcount-2)%10);}
									printf("$t%d\n", (tcount-1)%10);
									printf("mflo ");
									if(opcount==1){printf("$s%d\n", getMapPos(registers.root, buffer[0]));}
									else{printf("$t%d\n", tcount%10);tcount++;}
									printf("L%d:\n", lcount);
									lcount++;
								}
								else{
									printf("li $t%d,", tcount%10); tcount++;
									if(buffer[i+2]=='-'){printf("-");}
									printf("%d\n",val);
									printf("div ");
									if(!tchecker){printf("$s%d,", getMapPos(registers.root, buffer[i]));}
									else{printf("$t%d,",(tcount-1)%10);}
									printf("$t%d\n",(tcount-1)%10);
									if(type==3){printf("mflo ");}
									else if(type==4){printf("mfhi ");}
									if(opcount==1){printf("$s%d\n", getMapPos(registers.root, buffer[0]));}
									else{printf("$t%d\n", tcount%10); tcount++; tchecker=1;}
								}
							}
						}
					}
					/* Addition and subtraction */
					else{
						if(buffer[i+1]=='-'){printf("-");}
						printf("%d\n", val);
					}
				}
			}
			opcount--;
			/* Break case */
			if(buffer[i+3]==';'||buffer[i+4]==';'){break;}
		}
	}
	fclose(fp);
	if(buffer){free(buffer);}
	return EXIT_SUCCESS;
}