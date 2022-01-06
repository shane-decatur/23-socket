#include "pipe_networking.h"


int main() {

  int sd;

  sd = server_handshake();

  char *line = calloc(BUFFER_SIZE,1);

  while (read(sd,line,BUFFER_SIZE)){

    int i = 0;
    for (i = 0; i < strlen(line); i++) {
				if (line[i] >= 97 && line[i] <= 122) line[i] -= 32;
		}

    write(sd,line,BUFFER_SIZE);
  }

  return 0;
}
