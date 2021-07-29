#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>

#define BUF_SIZE 1

int main(int len, char*argv[]){
    int from, to;
    int rbytes,wbytes;
    char buffer[BUF_SIZE];
    int arr[26],i,count=0;
    char ch = 'a';
	float x = 0;

    if(len != 2){
        perror("Num of arguments");
    }
    for(i=0; i<26; i++)
        arr[i]=0;
    from = open(argv[1],O_RDONLY);
    if(from == -1){
        perror("could not open file 1");
        exit(1);
    }
    while((rbytes = read (from, &buffer, BUF_SIZE)) > 0){
        if((buffer[0]<='z'&&buffer[0]>='a')||(buffer[0]<='Z'&&buffer[0]>='A')){
            count++;
            if(islower(buffer[0])!=0)
                arr[buffer[0]-'a']++;
                else
                    arr[buffer[0]-'A']++;
        }
    }
    for(i=0;i<26;i++){
        if(arr[i]>0){
			x=(float)arr[i]*100/count;
        printf("%c - %.3g%\n",(char)((int)ch+i),x);
}
    }
}
