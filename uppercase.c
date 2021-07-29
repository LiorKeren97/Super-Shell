#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>

#define BUF_SIZE 1
int main(int len, char*argv[]){
    int from, to;
    int rbytes,wbytes;
    char buffer[BUF_SIZE];

    if (len != 3){
        perror("Number of Argumments is not vailed");
        exit(1);
   }
   /* Open input file for reading */
    from = open(argv[1],O_RDONLY);
    if(from == -1){
        perror("could not open file 1");
        exit(1);
    }
    /* Open output file for writing. if the file does not exist - create it */
    to = open(argv[2], O_WRONLY | O_CREAT|O_APPEND |O_TRUNC, 0644);
    if(to == -1){
        perror("could not create file"); 
         exit(1); 
    }
    /* while there somthing to read */
	while((rbytes = read (from, &buffer, BUF_SIZE)) > 0){
        if(islower(buffer[0]))
           buffer[0]=toupper(buffer[0]);
 	    wbytes = write (to, &buffer, rbytes);
	 /* read from input file */
         if(wbytes != rbytes){
		/* Write error */ 
        perror("write"); 
		exit(1);
       }
    }

    close(from);
    close(to);
}