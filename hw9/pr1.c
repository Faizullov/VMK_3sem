#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc != 6){
        printf("WRONG PARAMETERS\n");
        return 0;
    }
    int pid1, pid2;
    int status1, status2;
    if (atoi(argv[5]) == 1){
        pid1 = fork();
        if (pid1 == 0){
            execl(argv[1], argv[1], argv[2], NULL);
            printf("ERR WITH FIRST PROGRAMM\n");
            exit(-1);
        }
        if (pid1 == -1){
            printf("ERROR CREATE 1\n");
            return 0;
        }
        pid2 = fork();
        if (pid2 == 0){
            execl(argv[3], argv[3], argv[4], NULL);
            printf("ERR WITH SECOND PROGRAMM\n");
            exit(-1);
        }
        if (pid2 == -1){
            printf("ERROR CREATE 2\n");
            return 0;
        }
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
        if (WIFEXITED(status1) != 0){
            printf("1 End with %d\n", WEXITSTATUS(status1));
        } else {
            printf("Err with first programm\n");
        }
        if (WIFEXITED(status2) != 0){
            printf("2 End with %d\n", WEXITSTATUS(status2));
        } else {
            printf("Err with second programm\n");
        }
        return 0;
    }
    if (atoi(argv[5]) == 2){
        pid1 = fork();
        if (pid1 == 0){
            execl(argv[1], argv[1], argv[2], NULL);
            printf("ERR WITH FIRST PROGRAMM\n");
            exit(-1);
        }
        if (pid1 == -1){
            printf("ERROR CREATE 1\n");
            return 0;
        }
        wait(&status1);
        if (WIFEXITED(status1) != 0){
            printf("1 End with %d\n", WEXITSTATUS(status1));
        } else {
            printf("Err with first programm\n");
        }
        pid2 = fork();
        if (pid2 == 0){
            execl(argv[3], argv[3], argv[4], NULL);
            printf("ERR WITH FIRST PROGRAMM\n");
            exit(-1);
        }
        if (pid2 == -1){
            printf("ERROR CREATE 1\n");
            return 0;
        }
        wait(&status2);
        if (WIFEXITED(status2) != 0){
            printf("2 End with %d\n", WEXITSTATUS(status2));
        } else {
            printf("Err with second programm\n");
        }
        return 0;
    }
    return 0;
}