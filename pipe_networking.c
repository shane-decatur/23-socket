#include "pipe_networking.h"


/*=========================
  server_setup
  args:

  creates the WKP (upstream) and opens it, waiting for a
  connection.

  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
// int server_setup() {
//
//   mkfifo(WKP,0644);
//   int from_client = open(WKP, O_RDONLY);
//   remove(WKP);
//
//   return from_client;
// }
//
//
// /*=========================
//   server_connect
//   args: int from_client
//
//   handles the subserver portion of the 3 way handshake
//
//   returns the file descriptor for the downstream pipe.
//   =========================*/
// int server_connect(int from_client) {
//
//   char *buffer = calloc(HANDSHAKE_BUFFER_SIZE,1);
//   read(from_client, buffer, HANDSHAKE_BUFFER_SIZE);
//
//   int to_client = open(buffer, O_WRONLY);
//
//   write(to_client,ACK,HANDSHAKE_BUFFER_SIZE);
//   read(from_client,ACK,HANDSHAKE_BUFFER_SIZE);
//
//   return to_client;
// }


/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake() {

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, 9845, hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);
  listen(sd,5);

  struct sockaddr_storage client_address;
  socklen_t sock_size = sizeof(client_address);

  int client = accept(sd, struct sockaddr *) &client_address, &sock_size);

  free(hints)
  freeaddrinfo(results);



  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

  int f = fork();
  if (f){
    while (1){
      client = accept(sd,(struct sockaddr *)&client_address, &sock_size);
      f = fork();
      if (!f){
        return client;
      }
    }
  }
  else{
      return client;
  }

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake() {

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, 9845, hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);

  free(hints)
  freeaddrinfo(results);

  return sd;
}
