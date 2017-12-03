#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    int fd, State;
    char buff[512];


    mkfifo("tmp", 0666);

    if((fd = open("tmp", O_WRONLY)) < 0){
      printf("Cannot open\n");
      return 0;
    }


    while((State = read(STDIN_FILENO, buff, 512) ) > 0) {
      write(fd, buff, strlen(buff));
    }
    close(fd);
}
