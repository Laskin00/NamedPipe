/*#include <sys/types.h>
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
}*/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

 struct ringbuff{
 		int pos;
 		int read;
    void *head;
    void *tail;
 		char begin[0];
 };

 int main(int argc, char * argv[]){

 	int mempos = shm_open( "tmp", O_CREAT | O_RDWR, S_IRWXO );

 	if( mempos == -1 )
 	{
 		perror("Can't open file");
 		return 0;
 	}

 	int res;
 	res = ftruncate( mempos, 4096 );
 	if( res == -1 ){
 		perror("truncating");
 		return 0;
 	}

 	struct ringbuff* rb = mmap( NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mempos, 0 );
 	if( rb == NULL )
 	{
 		perror("mmapping");
 		return 0;
 	}

 	rb->pos = 0;
  rb->read = 0;
  rb->head = rb->begin;
  rb->tail= rb->begin;

 	char buff [512];
  int i = 0;
 	while(1){
 		fgets(buff, 1, stdin);
    i++;
    if(i == 511){
      system("./read");
    }
 		memcpy( rb->begin + rb->pos, buff, strlen(buff) + 1);
 		rb->pos += strlen(buff);
 	}
 	return 0;
 }

