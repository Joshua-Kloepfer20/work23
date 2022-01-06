#include "pipe_networking.h"


int main() {

  int sd;
  sd = client_handshake();
  while (1) {
        char input[BUFFER_SIZE];
        printf("input a string: ");
        fgets(input, 200, stdin);
        write(sd, input, strlen(input));
        char output[BUFFER_SIZE];
        read(sd, output, BUFFER_SIZE);
        printf("output: %s\n", output);
  }
}
