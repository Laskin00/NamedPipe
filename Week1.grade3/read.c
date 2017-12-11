/*#include <fcntl.h>
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
*/

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

int main(){
    int mempos = shm_open( "tmp", O_RDONLY, 1);
     if( mempos == -1 ){
 		    perror("Oppening tmp");
 		    return 0;
     }

    struct ringbuff* rb = mmap( NULL, 4096, PROT_READ, MAP_SHARED, mempos, 0 );
    
    if(rb == NULL ){
        perror("mmaping");
        return -1;
    }

    printf("%s\n", rb->begin);

    return 0;
}
