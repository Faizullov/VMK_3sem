#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#define SIZ 4


int scan_int(int fd, int off){
    int a;
    lseek(fd, off, SEEK_SET);
    read(fd, &a, 4);
    return a;
}

void sort(int fd, int size){
    int i = 0;
    int buf1;
    int buf2;
    while (i < size - 4){
        if(scan_int(fd, i+4) <= scan_int(fd, i)){
            lseek(fd, i, SEEK_SET);
            read(fd, &buf1, 4);
            lseek(fd, i+4, SEEK_SET);
            read(fd, &buf2, 4);
            lseek(fd, i, SEEK_SET);
            write(fd, &buf2, 4);
            lseek(fd, i+4, SEEK_SET);
            write(fd, &buf1, 4);
            sort(fd, size);
        }
        i = i + 4;
    }
}

void write_in(int out, int n){
    int digits = 1;
    int saved = n;
    char changed;
    while(saved){
        saved = saved / 10;
        digits = digits * 10;
    }
    while(n){
        digits = digits / 10;
        changed = (char)(n/digits) + '0';
        write(out, &changed, 1);
        n = n % digits;
    }
    changed = ' ';
    write(out, &changed, 1);
}

int main(int argc, char** argv){
    int fd,out;
    int n;
    int size;
    fd = open(argv[1], O_RDWR, 0);
    if (fd == -1){
        printf("ERR\n");
        return 0;
    }
    struct stat fd_st;
    stat(argv[1], &fd_st);
    out = open(argv[2], O_RDWR|O_TRUNC|O_CREAT, 0666);
    struct stat out_st;
    stat(argv[2], &out_st);
    if(fd_st.st_ino == out_st.st_ino){
        printf("EQ\n");
        return 0;
    }
    size = fd_st.st_size;
    sort(fd, size);
    lseek(fd, 0, SEEK_SET);
    char symb;
    while(read(fd, &n, 4) == 4){
        if (n < 0){
            symb = '-';
            write(out, &symb, 1);
            write_in(out, -1*n);
        } else if (n == 0){
            symb = '0';
            write(out, &symb, 1);
        } else {
            write_in(out, n);
        }
    }
    close(fd);
    close(out);
    return 0;
}