#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    int fd, State;
    char buff[512];

    if ((fd = open("tmp", O_RDONLY)) < 0){
      printf("Cannot open\n");
      return 0;
    }

    while((State = read(fd, buff, 512) ) > 0) {
      write(STDOUT_FILENO, buff,  State);
    }

    close(fd);
}

