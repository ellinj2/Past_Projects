#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER 1024
#define MAX_CLIENTS 100

// Structs go here... Probably a TCP_Client struct
typedef struct Client Client;

struct Client{
	char* protocol;
	char* buffer;
	struct sockaddr_in* address;
	int fd;
	socklen_t length;
	char* name;
	int login_number;
	int active;
};

// Globals go here... Probably a global TCP_Client tracker
int active_count = 0;
int tcpfd;
int udpfd;
Client** active_users;
static const char INVALID_USERID[] = "ERROR Invalid userid\n";
static const char ALREADY_CONNECTED[] = "ERROR Already connected\n";
static const char UNKNOWN_USERID[] = "ERROR Unknown userid\n";
static const char INVALID_MSGLEN[] = "ERROR Invalid msglen\n";
// static const char INVALID_SEND_FORMAT[] = "ERROR: Invalid SEND format\n";
static const char INVALID_COMMAND[] = "ERROR Command not recognized\n";
static const char UDP_LOGIN[] = "ERROR LOGIN not supported over UDP\n";
static const char UDP_SEND[] = "ERROR SEND not supported over UDP\n";
// static const char UDP_LOGOUT[] = "ERROR: LOGOUT not supported over UDP\n";

// Prototypes
void clean(char* buffer);
int Client_Sort(const void* v1, const void* v2);
char* strAdd(char* str1, char* str2);
char* substring(char* input, int start, int end);

void BROADCAST(Client* client);
void LOGIN(Client* client);
void LOGOUT(Client* client);
void SEND(Client* client);
void* TCP_Client(void* client);
void UDP_Client(Client* client);
void WHO(Client* client);

int max(int x, int y){
	if (x > y){
		return x;
	}
	return y;
}

int main(int argc, char **argv){
	setvbuf(stdout, NULL, _IONBF, 0);

	fd_set readfds;
	int maxfdp1;

	unsigned short PORT;
	
	#ifdef DEBUG_MODE
		// MANUALLY FORCE PORT NUMBER
		printf("Debugging: Allowing OS to set port number\n");
		PORT = 8213;
	#else
		if (argc < 2){
			perror("ERROR: Invalid usage\nUSAGE: ./a.out <port number>\n");
			exit(1);
		}
		PORT = atoi(argv[1]);
	#endif

	active_users = calloc(MAX_CLIENTS, sizeof(Client*));
	for(int user = 0; user < MAX_CLIENTS; user++){
		active_users[user] = NULL;
	}

	tcpfd = socket(PF_INET, SOCK_STREAM, 0);
	if (tcpfd < 0){
		perror("socket() failed\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server;

	server.sin_family = PF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	server.sin_port = htons(PORT);
	int tolen = sizeof(server);

	if (bind(tcpfd, (struct sockaddr *) &server, tolen) < 0){
		perror("TCP bind() failed");
		exit(EXIT_FAILURE);
	}

	listen(tcpfd, MAX_CLIENTS);

	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(udpfd, (struct sockaddr *) &server, tolen) < 0){
		perror("UDP bind() failed");
		exit(EXIT_FAILURE);
	}

	maxfdp1 = max(tcpfd, udpfd) + 1;

	printf("MAIN: Started server\n");
	printf("MAIN: Listening for TCP connections on port: %d\n", PORT);
	printf("MAIN: Listening for UDP datagrams on port: %d\n", PORT);

	while(1){
		FD_ZERO(&readfds);
		FD_SET(tcpfd, &readfds);
		FD_SET(udpfd, &readfds);
		
		#ifdef DEBUG_MODE
			struct timeval timeout;
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;
			int ready = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
			if (ready == 0){
				printf("Still waiting...\n");
				continue;
			}
		#else
			select(maxfdp1, &readfds, NULL, NULL, NULL);
		#endif

		// Activity on TCP?
		if (FD_ISSET(tcpfd, &readfds)){
			Client* incoming = calloc(1, sizeof(Client));
			incoming -> buffer = calloc(MAX_BUFFER, sizeof(char));
			incoming -> login_number = -1;
			incoming -> active = 0;
			incoming -> address = calloc(1, sizeof(struct sockaddr_in*));
			incoming -> length = sizeof(*(incoming -> address));
			incoming -> protocol = "TCP";
			incoming -> fd = accept(tcpfd, (struct sockaddr*)incoming -> address, &(incoming -> length));
			printf("MAIN: Rcvd incoming TCP connection from: %s\n", inet_ntoa((struct in_addr)incoming -> address->sin_addr));
			int rc = 0;
			pthread_t child_thread;
			rc = pthread_create(&child_thread, NULL, TCP_Client, (void*) incoming);
			if (rc != 0){
				perror("ERROR: Couldn't create thread\n");
			}
		}

		// Activity on UDP?
		if (FD_ISSET(udpfd, &readfds)){
			Client* incoming = calloc(1, sizeof(Client));
			incoming -> buffer = calloc(MAX_BUFFER, sizeof(char));
			incoming -> login_number = -1;
			incoming -> address = calloc(1, sizeof(struct sockaddr_in *));
			incoming -> length = sizeof(*(incoming -> address));
			incoming -> protocol = "UDP";
			incoming -> fd = udpfd;
			UDP_Client(incoming);
		}

	}

	free(active_users);
	printf("MAIN: Terminating server\n");
	return EXIT_SUCCESS;
}



void clean(char* buffer){
	int shift = 0;
	int maxLen = strlen(buffer);
	for(int i = 0; i < strlen(buffer); i++){
		if(*(buffer + i) == '\\'){
			if(*(buffer + i + 1) == 'n'){
				*(buffer + i) = '\n';
				shift = 1;
			}
			else if(*(buffer + i + 1) == 't'){
				*(buffer + i + 1) = '\t';
				shift = 1;
			}
			else if(*(buffer + i + 1) == '0'){
				*(buffer + i + 1) = '\0';
				shift = 1;
			}
		}
		// Shift the rest of the string down
		if (shift == 1){
			for (int j = i + 1; j < strlen(buffer) - 1; j++){
				*(buffer + j) = *(buffer + j + 1);
			}
			maxLen -= 1;
			shift = 0;
		}
	}
	buffer[maxLen] = '\0';
}

int Client_Sort(const void* v1, const void* v2){
	return strcmp(* (char **)v1, * (char **)v2);
}

char* strAdd(char* str1, char* str2){
	char* output = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
	output[0] = '\0';
	strcat(output, str1);
	strcat(output, str2);
	output[strlen(str1)+strlen(str2)] = '\0';

	return output;
}

char* substring(char* input, int start, int end){
	if(end == -1){
		end = strlen(input);
	}
	char* output = calloc(end-start, sizeof(char));
	for(int i=0; i < (end - start); i++){
		*(output + i) = *(input + start + i);
	}
	return output;
}



void BROADCAST(Client* client){
	if (strcmp(client -> name, "UDP-client") != 0){
		printf("CHILD %ld: Rcvd BROADCAST request\n", pthread_self());
		send(client -> fd, "OK!\n", 4, 0);
	} else {
		printf("MAIN: Rcvd BROADCAST request\n");
	}

	//SUPER INEFFICIENT
	int i, msg_start;
	msg_start = i = 10;
	while(msg_start < strlen(client -> buffer) && *((client -> buffer) + msg_start) != '\n'){msg_start++;}
	char* msglen_str = substring(client -> buffer, i, msg_start);
	int msg_len = atoi(msglen_str);
	if (msg_len < 1 || msg_len > 990){
		sendto(client -> fd, INVALID_MSGLEN, strlen(INVALID_MSGLEN), 0, (struct sockaddr*)client -> address, client -> length);
		printf("MAIN: Sent ERROR (invalid msglen)\n");
		return;
	}

	char* message = "FROM ";
	message = strAdd(message, client -> name);
	message = strAdd(message, " ");
	message = strAdd(message, msglen_str);
	message = strAdd(message, " ");
	message = strAdd(message, substring(client -> buffer, msg_start + 1, msg_start + 1 + msg_len + 1));
	if(message[strlen(message) - 1] != '\n'){
		message = strAdd(message, "\n");
	}

	for(i = 0; i < MAX_CLIENTS; i++){
		if(active_users[i] != NULL && active_users[i] -> active == 1 && active_users[i] -> name != NULL){
			send(active_users[i] -> fd, message, strlen(message), 0);
		}
	}
}

void LOGIN(Client* client){
	int i;
	client -> name = substring(client -> buffer, 6, -1);
	for(i = 0; i < strlen(client -> name); i++){
		if(client -> name[i] == '\n'){
			client -> name[i] = '\0';
			break;
		}
	}
	printf(" %s\n", client -> name);
	if(strlen(client -> name) < 4 || strlen(client -> name) > 16){
		send(client -> fd, INVALID_USERID, strlen(INVALID_USERID), 0);
		printf("CHILD %ld: Sent ERROR (Invalid userid)\n", pthread_self());
		return;
	}
	int candidate = -1;
	for(i = 0; i < MAX_CLIENTS; i++){
		if(active_users[i] != NULL && strcmp(client -> name, active_users[i] -> name) == 0 && active_users[i] -> active == 1){
			send(client -> fd, ALREADY_CONNECTED, strlen(ALREADY_CONNECTED), 0);
			printf("CHILD %ld: Sent ERROR (Already connected)\n", pthread_self());
			return;
		}
		if(active_users[i] == NULL || (active_users[i] -> active == 0 && strcmp(active_users[i] -> name, client -> name) == 0)){
			candidate = i;
			break;
		}
	}
	if(active_users[candidate] == NULL){
		active_users[candidate] = client;
		client -> login_number = candidate;
		client -> active = 1;
	}
	else{
		active_users[candidate] -> active = 1;
		client -> active = 1;
		client -> login_number = candidate;
	}
	active_count++;
	send(client -> fd, "OK!\n", 4, 0);
}

void LOGOUT(Client* client){
	send(client -> fd, "OK!\n", 4, 0);
	client -> active = 0;
	active_count--;
}

void SEND(Client* client){
	/*
	* STILL NEED TO IMPLEMENT WEIRD FORMAT ERROR
	*/
	char* recipient = calloc(16, sizeof(char));
	char* message = calloc(MAX_BUFFER, sizeof(char));
	int i, msg_start;
	// Copy over recipient name
	for(i = 5; i < 16 && (client -> buffer)[i] != ' '; i++){
		*(recipient + i - 5) = *((client -> buffer) + i);
	}
	printf("CHILD %ld: Rcvd SEND request to userid %s\n", pthread_self(), recipient);
	// Find message start
	msg_start = i + 1;
	while(msg_start < strlen(client -> buffer) && *((client -> buffer) + msg_start) != '\n'){msg_start++;}
	char* msglen_str = substring(client -> buffer, i + 1, msg_start);
	int msglen = atoi(msglen_str);
	if (msglen < 1 || msglen > 990){
		send(client -> fd, INVALID_MSGLEN, strlen(INVALID_MSGLEN), 0);
		printf("CHILD %ld: Sent ERROR (Invalid msglen)\n", pthread_self());
		return;
	}
	for(i = 0; i < MAX_CLIENTS; i++){
		if(active_users[i] != NULL && active_users[i] -> active == 1 && strcmp(active_users[i] -> name, recipient) == 0){
			break;
		}
	}
	// No such recipient
	if (i == MAX_CLIENTS){
		send(client -> fd, UNKNOWN_USERID, strlen(UNKNOWN_USERID), 0);
		printf("CHILD %ld: Sent ERROR (Unknown userid)\n", pthread_self());
		return;
	}

	send(client -> fd, "OK!\n", 4, 0);
	message = "FROM ";
	message = strAdd(message, client -> name);
	message = strAdd(message, " ");
	message = strAdd(message, msglen_str);
	message = strAdd(message, " ");
	message = strAdd(message, substring(client -> buffer, msg_start + 1, msg_start + 1 + msglen + 1));
	if(message[strlen(message) - 1] != '\n'){
		message = strAdd(message, "\n");
	}
	send(active_users[i] -> fd, message, strlen(message), 0);
	free(message);
}

void* TCP_Client(void* args){
	Client* client = (Client*) args;

	int safe_fd = client -> fd;
	int rd;
	while(1){
		client -> fd = safe_fd;
		bzero(client -> buffer, MAX_BUFFER);
		rd = read(client -> fd, client -> buffer, MAX_BUFFER);
		if(rd == 0){
			printf("CHILD %ld: Client disconnected\n", pthread_self());
			if(client -> login_number != -1 && client -> active == active_users[client -> login_number] -> active){
				active_users[client -> login_number] = NULL;
			}
			free(client -> buffer);
			free(client -> name);
			close(client -> fd);
			break;
		}
		client -> buffer[rd-1] = '\0';
		clean(client -> buffer);
		
		if(strcmp(substring(client -> buffer, 0, 5), "LOGIN") == 0){
			printf("CHILD %ld: Rcvd LOGIN request for userid", pthread_self());
			LOGIN(client);
		}
		else if(strcmp(substring(client -> buffer, 0, 6), "LOGOUT") == 0){
			printf("CHILD %ld: Rcvd LOGOUT request\n", pthread_self());
			LOGOUT(client);
		}
		else if(strcmp(substring(client -> buffer, 0, 3), "WHO") == 0){
			printf("CHILD %ld: Rcvd WHO request\n", pthread_self());
			WHO(client);
		}
		else if(strcmp(substring(client -> buffer, 0, 4), "SEND") == 0){
			SEND(client);
		}
		else if(strcmp(substring(client -> buffer, 0, 9), "BROADCAST") == 0){
			BROADCAST(client);
		}
		else{
			send(client -> fd, INVALID_COMMAND, strlen(INVALID_COMMAND), 0);
		}
	}
	pthread_exit(NULL);
}

void UDP_Client(Client* client){
	bzero(client -> buffer, MAX_BUFFER);
	recvfrom(client -> fd, client -> buffer, MAX_BUFFER, 0, (struct sockaddr*)client -> address, &(client -> length));
	clean(client -> buffer);
	printf("MAIN: Rcvd incoming UDP datagram from: %s\n", inet_ntoa((struct in_addr)client -> address->sin_addr));
	if(strcmp(substring(client -> buffer, 0, 5), "LOGIN") == 0){
		sendto(client -> fd, UDP_LOGIN, strlen(UDP_LOGIN), 0, (struct sockaddr*)client -> address, client -> length);
		printf("MAIN: Sent ERROR (LOGIN not supported by UDP)\n");
	}
	else if(strcmp(substring(client -> buffer, 0, 6), "LOGOUT") == 0){
		sendto(client -> fd, "OK!\n", 4, 0, (struct sockaddr*)client -> address, client -> length);
	}
	else if(strcmp(substring(client -> buffer, 0, 3), "WHO") == 0){
		printf("MAIN: Rcvd WHO request\n");
		WHO(client);
	}
	else if(strcmp(substring(client -> buffer, 0, 4), "SEND") == 0){
		sendto(client -> fd, UDP_SEND, strlen(UDP_SEND), 0, (struct sockaddr*)client -> address, client -> length);
		printf("MAIN: Sent ERROR (SEND not supported by UDP)\n");
	}
	else if(strcmp(substring(client -> buffer, 0, 9), "BROADCAST") == 0){
		BROADCAST(client);
	}
	else{
		sendto(client -> fd, INVALID_COMMAND, strlen(INVALID_COMMAND), 0, (struct sockaddr*)client -> address, client -> length);
		printf("MAIN: Sent ERROR (Invalid command)\n");
	}
}

void WHO(Client* client){
	char* message = calloc(1024, sizeof(char));
	message = "OK!\n";
	char** online = calloc(active_count, sizeof(char*));
	int pos = 0;
	for(int i = 0; i < MAX_CLIENTS; i++){
		if(active_users[i] != NULL && active_users[i] -> name != NULL && active_users[i] -> active == 1){
			online[pos] = active_users[i] -> name; pos++;
		}
	}
	qsort(online, pos, sizeof(char*), Client_Sort);
	for(int i = 0; i < active_count; i++){
		message = strAdd(message, online[i]);
		message = strAdd(message, "\n");
	}
	if(online != NULL){
		free(online);
	}
	if(strcmp(client -> protocol, "UDP") == 0){
		sendto(client -> fd, message, MAX_BUFFER, 0, (struct sockaddr*)client -> address, client -> length);
		return;
	}
	send(client -> fd, message, strlen(message), 0);
}
