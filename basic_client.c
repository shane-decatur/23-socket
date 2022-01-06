#include "pipe_networking.h"


int main() {

  int sd;

  sd = client_handshake();

  while(1){
    char *line = calloc(BUFFER_SIZE,1);
    printf("input message: ");
    fgets(line, BUFFER_SIZE, stdin);
    write(sd,line,BUFFER_SIZE);

    read(sd,line,BUFFER_SIZE);
    printf("your message but loud: %s",line);
  }

}
