#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#define MAXDIR 1000
typedef struct dirent dirent;

void rec(char *dir){
    DIR *direntio = opendir(dir);
    dirent* ent;
    char son[MAXDIR];
    struct stat inf;
    while((ent = readdir(direntio)) != NULL){
        if (strcmp(ent->d_name, ".") != 0 && (strcmp(ent->d_name, "..") != 0)){
            stat(ent->d_name, &inf);
            if(inf.st_mode & S_IFDIR){
                printf("%s\n", ent -> d_name);
                if(chdir(ent -> d_name) == 0){
                    getcwd(son, MAXDIR);
                    rec(son);
                    chdir("..");
                }
            }
        }
    }
    free(ent);
    closedir(direntio);
}
int main(int argc, char **argv)
{
    char dir[MAXDIR];
    getcwd(dir, MAXDIR);
    printf("You directory %s\n", dir);
    rec(dir);
    return 0;
}