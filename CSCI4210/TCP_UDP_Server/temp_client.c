#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

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

int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  /* create TCP client socket (endpoint) */
  int sd = socket( PF_INET, SOCK_STREAM, 0 );

  if ( sd == -1 )
  {
    perror( "socket() failed" );
    exit( EXIT_FAILURE );
  }

#if 0
  struct hostent * hp = gethostbyname( "localhost" );  /* 127.0.0.1 */
  struct hostent * hp = gethostbyname( "127.0.0.1" );
  struct hostent * hp = gethostbyname( "128.113.126.29" );
#endif

  /*
   * Note: gethostbyname is deprecated, newer way is to use getaddrinfo, looks very different!
   * You can read the man page if you're curious.
   * In CSCI-4220 (Net Prog) you might see getaddrinfo().
   */
  struct hostent * hp = gethostbyname( "127.0.0.1" );
  //struct hostent * hp = gethostbyname( "linux04.cs.rpi.edu" );

  if ( hp == NULL )
  {
    fprintf( stderr, "ERROR: gethostbyname() failed\n" );
    return EXIT_FAILURE;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  memcpy( (void *)&server.sin_addr, (void *)hp->h_addr, hp->h_length );
  unsigned short port = 8213;
  if(argc > 1){
    port = atoi(argv[1]);
  }
  server.sin_port = htons( port );

  printf( "server address is %s\n", inet_ntoa( server.sin_addr ) );

  #if 0
  char* tmp = inet_ntoa(server.sin_addr);
  printf( "server address is %s\n", inet_ntoa( server.sin_addr ) );
  struct hostent* hp2 = gethostbyname("128.113.126.24");
  struct sockaddr_in sai2;
  memcpy( (void *)&sai2.sin_addr, (void *)hp2->h_addr, hp2->h_length );
  char* tmp2 = inet_ntoa(sai2.sin_addr);
  printf("tmp: %s, tmp2: %s\n",tmp,tmp2);
  return 0;
  #endif

  printf( "connecting to server.....\n" );
  if ( connect( sd, (struct sockaddr *)&server, sizeof( server ) ) == -1 )
  {
    perror( "connect() failed" );
    return EXIT_FAILURE;
  }


  /* The implementation of the application layer protocol is below... */
  char msg[BUFFER_SIZE];
  printf("Send message to server: ");
  read(0, msg, BUFFER_SIZE);

  while(1){
    if(strcmp(substring(msg, 0, 4), "EXIT") == 0){
      printf("Leaving server\n");
      break;
    }
    int n = write( sd, msg, strlen( msg ) );    /* or send()/recv() */

    if ( n < strlen( msg ) )
    {
      perror( "write() failed" );
      return EXIT_FAILURE;
    }


    char buffer[ BUFFER_SIZE ];
    n = read( sd, buffer, BUFFER_SIZE - 1 );    /* BLOCKING */

    if ( n == -1 )
    {
      perror( "read() failed" );
      return EXIT_FAILURE;
    }
    else if ( n == 0 )
    {
      printf( "Rcvd no data; also, server socket was closed\n" );
    }
    else  /* n > 0 */
    {
      buffer[n] = '\0';    /* assume we rcvd text-based data */
      printf( "Rcvd from server: %s\n", buffer );
    }
    printf("Send message to server: ");
    read(0, msg, BUFFER_SIZE);
  }

  // sleep(5);
  close( sd );

  return EXIT_SUCCESS;
}