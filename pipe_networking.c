#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake() {
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "1119", hints, &results);
  bind(sd, results->ai_addr, results->ai_addrlen);
  printf("waiting for client\n");
  listen(sd, 5);
  struct sockaddr_storage client_address;
  socklen_t sock_size = sizeof(client_address);
  int client = accept(sd, (struct sockaddr * ) &client_address, &sock_size);
  printf("client has connected\n");
  free(hints);
  freeaddrinfo(results);
  int f = fork();
  if (f) {
    while (1) {
      client = accept(sd, (struct sockaddr * ) &client_address, &sock_size);
      f = fork();
      if (!f) {
        return client;
      }
    }
  }
  else {
    return client;
  }
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  struct addrinfo * hints;
  struct addrinfo * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "1119", hints, &results);
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  connect(sd, results->ai_addr, results->ai_addrlen);
  printf("connected\n");
  return sd;
}
