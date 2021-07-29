#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int len, char*argv[]){
        int to,count = atoi(argv[2]);


    if (len != 4){
        printf("Parameter Missing or Invalid.\n");
        exit(1);
   }

   /* Open output file for writing. if the file does not exist - create it */
    to = open(argv[3], O_WRONLY | O_CREAT|O_APPEND, 0644);
    if(to == -1){
        perror("could not create file"); 
         exit(1); 
    }
    while(count>0){
        if(write (to, argv[1],1)>0)
            count--;
            else{
                perror("write");
                exit(1);
            }
    }
}
