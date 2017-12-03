int main(){
    int fd, State;
    char buff[500];

    if ((fd = open("tmp", O_RDONLY)) < 0){
      printf("Cannot open\n");
      return 0;
    }

    while((State = read(fd, buff, 500) ) > 0) {
      write(STDOUT_FILENO, buff,  State);
    }

    close(fd);
}
