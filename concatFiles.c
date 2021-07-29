#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 1

int main(int len, char*argv[]){
    int from,from2,to;
    int rbytes,rbytes2,wbytes;
    char buffer[BUF_SIZE],buffer2[BUF_SIZE];

    if (len != 4){
        perror("Number of Argumments is not vailed");
        exit(1);
   }
   /* Open input file for reading */
    from = open(argv[1],O_RDONLY);
    if(from == -1){
        perror("could not open file 1");
        exit(1);
    }

       /* Open input file for reading */
    from2 = open(argv[1],O_RDONLY);
    if(from2 == -1){
        perror("could not open file 1");
        exit(1);
    }
    read (from2, &buffer2, BUF_SIZE);
    
    /* Open output file for writing. if the file does not exist - create it */
    to = open(argv[3], O_WRONLY | O_CREAT|O_APPEND |O_TRUNC, 0644);
    if(to == -1){
        perror("could not create file"); 
         exit(1); 
    }
    /* while there somthing to read */
	while((rbytes = read (from, &buffer, BUF_SIZE)) > 0){
        //if(read (from2, &buffer2, BUF_SIZE) > 0 && buffer[0]!='\n')
 	     wbytes = write (to, &buffer, rbytes);
	 /* read from input file */
         if(wbytes != rbytes){
		/* Write error */ 
        perror("write"); 
		exit(1);
       }
    }


    close(from);
    close(from2);
    from = open(argv[2],O_RDONLY);
    if(from == -1){
        perror("could not open file 2");
        exit(1);
    }
    while((rbytes = read (from, &buffer, BUF_SIZE)) > 0){
 	wbytes = write (to, &buffer, rbytes);
	 /* read from input file */
      if(wbytes != rbytes){
		/* Write error */ perror("write"); 
		exit(1);
       }
    }
    close(from);
    close(to);
}
