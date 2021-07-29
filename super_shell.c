#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>


char **passwords;
char **comands_to_lock;
int alreadylocked = 0, arrayindex = 1;
int lockCMD(char* cmd, char* pass);
int unlockCMD(char* cmd, char* pass);
bool islocked(char* cmd);
bool flag=true;

/* converting commands to integers for switch case */
int my_hash(char str[]){
    if(strcmp(str,"concatFiles")==0)
        return 0;
    if(strcmp(str,"runC")==0)
        return 1;
    if(strcmp(str,"distABC")==0)
        return 2;
    if(strcmp(str,"putLetter")==0)
        return 3;
    if(strcmp(str,"randomFile")==0)
        return 4;
    if(strcmp(str,"lowercase")==0)
        return 5;
    if(strcmp(str,"uppercase")==0)
        return 6;
    if (strcmp(str, "lockCMD") == 0)
        return 7;
    if (strcmp(str, "unlockCMD") == 0)
        return 8;
    if (strcmp(str, "byebye") == 0)
        return 9;
    
    return -1;
}

int main(int len, char*arg[]){
    char path[6]="/bin/";
    char *arr[5] = {NULL,NULL,NULL,NULL,NULL},string[100],*token;
    int pid = getpid(), wid, status, count = 0, i,temp;

    /* check id number of argumments is legal */
    if(len!=1){
        perror("Number of Argumments is not vailed");
		exit(1);
    }

    /* Initial memory allocation */
    passwords = (char**)malloc(arrayindex * sizeof(char*));
    if (passwords == NULL) {
        perror("Memory allocation!1");
        exit(1);
    }

    comands_to_lock = (char**)malloc(arrayindex * sizeof(char*));
    if (passwords == NULL) {
        perror("Memory allocation!2");
        exit(1);
    }

    for (i = 0; i < arrayindex; i++) {
        passwords[i] = (char*)malloc(9* sizeof(char));
        if (passwords[i] == NULL) {
            perror("Memory allocation!3");
            exit(1);
        }
        comands_to_lock[i] = (char*)malloc(256 * sizeof(char));
        if (comands_to_lock[i] == NULL) {
            perror("Memory allocation!4");
            exit(1);
        }
        strcpy(comands_to_lock[i],"*free*");
    }

    /*Resiving input from user's keyboard*/
    printf("SuperShell>");
        fgets(string,sizeof(string), stdin);
        string[strlen(string)-1] = '\0';
        /* while loop until user insert's "byebye" */
        while(flag){
        token = strtok(string, " ");
        //loop through the string to extract all other tokens
        while( token != NULL && count<4 ) {
            arr[count++]=token;
            token = strtok(NULL, " ");
        }

        /* Commands execution*/
        if(islocked(arr[0])== true){
        switch(my_hash(arr[0])){
            case 0:
                    pid = fork();
                     if (pid == 0){
                    arr[0]="concatFiles.out";
                    arr[4]=NULL;
                    execv("./concatFiles.out",arr);
                     }
                     break;
            case 1:
                    pid = fork();
                    if (pid == 0){
                     arr[2]=NULL;
                     arr[0]="runC.out";
                     execv("./runC.out",arr);}
                     break;
            case 2:
                    pid = fork();
                    if (pid == 0){
                     arr[0]="distABC.out";
                     arr[2]=NULL;
                     execv("./distABC.out",arr);}
                     break;
            case 3:
                    pid = fork();
                    if (pid == 0){
                     arr[0]="putLetter.out";
                     arr[4]=NULL;
                     execv("./putLetter.out",arr);}
                break;
            case 4:
                    pid = fork();
                    if (pid == 0){
                    arr[0]="randomFile.out";
                    arr[3]=NULL;
                    execv("./randomFile.out",arr);}
                break;
            case 5:
                    pid = fork();
                    if (pid == 0){
                    arr[0]="lowercase.out";
                    arr[3]=NULL;
                    execv("./lowercase.out",arr);}
                break;
            case 6:
                    pid = fork();
                    if (pid == 0){
                    arr[0]="uppercase.out";
                    arr[3]=NULL;
                    execv("./uppercase.out",arr);
                    }
                break;
            case 7:
            temp=lockCMD(arr[1], arr[2]);
                if (temp==1)
                    printf("The command %s is now locked!\n", arr[1]);
                if(temp==0)
                    printf("The command %s is already locked!\n", arr[1]);;
                break;
            case 8:
            temp=unlockCMD(arr[1], arr[2]);
                if (temp==1)
                    printf("The command %s is now unlocked!\n", arr[1]);
                break;
            case 9:
                flag=false;
                break;

            default:                              //Build-in shell commands
                    pid = fork();
                    if (pid == 0){
                    strcat(path,arr[0]);
                    execv(path,arr);
                    printf("Not supported\n");    // not supported commands
                    exit(1);
                    }
                    //execv("./notSupported.out",arr);
                 }//switch
        }//if is locked

                 /*In case last command was cat*/
                wait();
                if(strcmp("cat",arr[0])==0)
                printf("\n");

                /*Initialization*/
                count=0;
                strcpy(path,"/bin/");
                for(i=0;i<5;i++)
                    arr[i]=NULL;

              if(flag){  //if user has not entered "byebye command"                     
                while(wid = wait(&status) > 0);       //Parent waits for child to print
                printf("SuperShell>");
                fgets(string,sizeof(string), stdin);
                string[strlen(string)-1] = '\0';
              }
        }//byebye

        while(wid = wait(&status) > 0);             // force the parent to wait to all children
         if(pid !=0 )                               //If I'm a parent
         /*free allocated memory*/
         for (i = 0; i < arrayindex;i++) {
             free(comands_to_lock[i]);
             free(passwords[i]);
         }
         free(comands_to_lock);
         free(passwords);
        exit(1);
}
    /*This command will lock provided commandad and it's' password*/
    int lockCMD(char* cmd, char* pass) {
        int i = 0;
        if(pass==NULL){
            printf("Parameters are Missing or Invalid.\n");
            return -1;
        }
        /*Check if command already locked*/  
        for (i = 0; i < arrayindex; i++) {
            if (strcmp(cmd, comands_to_lock[i]) == 0)
                return 0;
        }

        /*No free space for new command in array*/
        if (arrayindex == alreadylocked) { 
            arrayindex++;
            alreadylocked++;
            passwords = realloc(passwords, (arrayindex) * sizeof(*passwords));
            if (passwords == NULL) {
                perror("Memory allocation!");
                exit(1);
            }
            comands_to_lock = realloc(comands_to_lock, (arrayindex) * sizeof(*comands_to_lock));
            if (comands_to_lock == NULL) {
                perror("Memory allocation!");
                exit(1);
            }
            passwords[arrayindex - 1] = (char*)malloc(9* sizeof(char));
            if (passwords[arrayindex - 1] == NULL) {
                perror("Memory allocation!");
                exit(1);
            }
            comands_to_lock[arrayindex - 1] = (char*)malloc(254* sizeof(char));
            if (comands_to_lock[arrayindex - 1] == NULL) {
                perror("Memory allocation!");
                exit(1);
            }

            strcpy(passwords[arrayindex - 1], pass);
            strcpy(comands_to_lock[arrayindex - 1], cmd);
         }


        /*There are free space for new command*/
        else
        {
            for (i = 0; i < arrayindex; i++) {
                if (strcmp("*free*", comands_to_lock[i]) == 0) {
                    strcpy(comands_to_lock[i], cmd);
                    alreadylocked++;
                    strcpy(passwords[i], pass);
                    return 1;
                }
            }
        }
        return 1;
    }
    
    /*This command will unlock command id vaild password has provided */
    int unlockCMD(char* cmd, char* pass) {
        int i = 0;
            if(pass==NULL){
            printf("Parameters are Missing or Invalid.\n");
            return -1;
        }
        for (i = 0; i < arrayindex; i++) {
            if (strcmp(cmd, comands_to_lock[i]) == 0) 
                if( strcmp(pass, passwords[i]) == 0) {
                strcpy(comands_to_lock[i], "*free*");
                alreadylocked--;
                return 1;
            }
                else {
                    printf("Wrong Password!!!\n");
                    return 0;
                }

        }
        printf("The command was not locked in the first place!\n");
        return 0;
    }

    /*This function will return true if was not locked or command was locked and recived valid password.*/
    bool islocked(char* cmd) {
        int i = 0;
        char userpass[9];
        for (i = 0; i < arrayindex; i++) {
            if (strcmp(cmd, comands_to_lock[i]) == 0) {
                printf("Enter password:");
                fgets(userpass, sizeof(userpass), stdin);
                userpass[strlen(userpass)-1] = '\0';
                if (strcmp(userpass, passwords[i]) == 0){
                    return true;
                }
                else{
                    printf("Wrong Password!!!");
                    return false;
                }
            }
                
        }
        return true;
    }



