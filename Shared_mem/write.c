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

int main(int argc, char * argv[]){
    int mempos = shm_open( "some_memory", O_CREAT | O_RDWR, S_IRWXU );

    if( mempos == -1 ){
        perror("Can't open file");
 		return 0;
 	}

 	int res;

 	res = ftruncate( mempos, 4096 );

 	if( res == -1 ){
 		perror("truncating");
 		return 0;
 	}

 	struct ringbuff* rb = mmap( NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mempos, 0);
 	if( rb == NULL ){
 		perror("mmapping");
 		return 0;
 	}

  rb->pos = 0;

    int i = 0;
    int seed = 0;

 	while(1){
        rb->begin[i] = seed;
        i++;

          i%=511;

          if(i % 128 == 0)
            sleep(1);
         seed++;
 	}
 	return 0;
 }

