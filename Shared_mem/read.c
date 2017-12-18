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
    int begin[0];
};

int main(){
    int mempos = shm_open("some_memory", O_RDONLY, 1);
     if(mempos == -1){
 		    perror("Oppening tmp");
 		    return 0;
     }

    struct ringbuff* rb = mmap( NULL, 4096, PROT_READ, MAP_SHARED, mempos, 0 );

    if(rb == MAP_FAILED){
        perror("mmaping");
        return -1;
    }
    int i = 0;

    while(1){
      if(i == rb->pos){
        sleep(1);
      }

      printf("%d", rb->begin[i]);
      i++;
      i%=511;
    }

    return 0;
}

