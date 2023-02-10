#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

#define SIZE 1000

int main(int argc, char **argv){
    int fd[2];
    int fd2[2];
    pipe(fd2);
    pipe(fd);
    FILE *file;
    file = fopen(argv[1], "r+");
    pid_t pid1;
    if (argc != 2){
        printf("ERR\n");
        return 0;
    }
    if (file){
        pid1 = fork();
        if (pid1 == 0){      // son
            char buf[SIZE];
            int len;
            len = 1;
            close(fd[1]);
            close(fd2[0]);
            char tmp;
            while (read(fd[0], buf, sizeof(buf))){
                len = strlen(buf);
                if(buf[len - 1] == '\n')
                    len--;
                for(int i = 0; i < len / 2; i++){
                    tmp = buf[i];
                    buf[i] = buf[len - 1 - i];
                    buf[len - 1 - i] = tmp;
                }
                write(fd2[1], buf, sizeof(buf));
            }
            close(fd2[1]);
            close(fd[0]);
            exit(0);
        } else{
            // father
            char buf[SIZE];
            close (fd[0]); // close to read
            close(fd2[1]);
            while(fgets(buf, SIZE, file)){
                char newbuf[SIZE];
                write(fd[1], buf, sizeof(buf));
                read(fd2[0], newbuf, sizeof(buf));
                fseek(file, -strlen(buf), SEEK_CUR);
                fprintf(file, "%s", newbuf);
            }
            close(fd[1]);
            close(fd2[0]);
            fclose(file);
            return 0;
        }
    }
    else {
        printf("ERR WITH FILE\n");
        return 0;
    }
    return 0;
}