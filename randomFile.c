#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>

#define BUF_SIZE 1
int main(int len, char*argv[]){
    int x=atoi(argv[1]), to;
    int wbytes;
    char buffer[BUF_SIZE];

    if (len != 3){
        perror("Number of Argumments is not vailed");
        exit(1);
   }
    /* Open output file for writing. if the file does not exist - create it */
    to = open(argv[2], O_WRONLY | O_CREAT|O_APPEND |O_TRUNC, 0644);
    if(to == -1){
        perror("could not create file"); 
         exit(1); 
    }
    /* while x chars are not witten */
	while(x!=0){
        /*random upper and lower case letters*/
        buffer[0]=rand() % 26 + 65 + rand() % 2 * 32;
 	    wbytes = write (to, &buffer, 1);
         x--;
	    /*if fail to write*/
         if(wbytes != 1){
		/* Write error */ 
        perror("write"); 
		exit(1);
       }
    }
    close(to);
}