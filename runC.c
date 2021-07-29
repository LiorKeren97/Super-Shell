#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main(int len, char *argv[]){
    int pid = getpid(),wid,status,flag=0;
    char *arr[3]={"gcc",argv[1],NULL};
    /* check id number of argumments is legal */
    if(len!=2){
        perror("Number of Argumments is not vailed");
		exit(1);
    }
    pid = fork();
    if(pid == 0){//Is child 
        execv("/bin/gcc",arr); // a.out created
        perror("execv");
        exit(1);
    }
    wait();
    pid = fork();
    if(pid == 0){
        execv("./a.out",NULL);
        perror("execv");
        exit(1);
    }
    wait();
    arr[0]="rm";
    arr[1]="a.out";
    pid = fork();
    if(pid == 0){
        execv("/bin/rm",arr);
        perror("execv");
        exit(1);
    }
}
