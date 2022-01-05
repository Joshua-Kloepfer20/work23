#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );
  while (1) {
        char input[BUFFER_SIZE];
        printf("input a string: ");
        fgets(input, 200, stdin);
        write(to_server, input, strlen(input));
        char output[BUFFER_SIZE];
        read(from_server, output, BUFFER_SIZE);
        printf("output: %s\n", output);
  }
}
