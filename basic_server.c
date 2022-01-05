#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  char input[BUFFER_SIZE];
  int x;
  while (x = read(from_client, input, BUFFER_SIZE)) {
        input[x-1] = '\0';
        int i;
        for (i = 0; i < strlen(input); i++) {
            input[i] = input[i] + 1;
        }
        write(to_client, input, BUFFER_SIZE);
    }
  return 0;
}
