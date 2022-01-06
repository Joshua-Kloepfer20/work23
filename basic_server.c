#include "pipe_networking.h"


int main() {

  int sd;
  sd = server_handshake();
  char input[BUFFER_SIZE];
  int x;
  while (x = read(sd, input, BUFFER_SIZE)) {
        input[x-1] = '\0';
        int i;
        for (i = 0; i < strlen(input); i++) {
            input[i] = input[i] + 1;
        }
        write(sd, input, BUFFER_SIZE);
    }
  return 0;
}
