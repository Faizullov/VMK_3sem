#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *file;
    int fd;
    char c;
    int n;
    file = fopen("input", "wb");
    c = ' ';
    while (c != '\n'){
        scanf("%d", &n);
        c = getchar();
        fwrite(&n, sizeof(int), 1, file);
    }
    fclose(file);
    return 0;
}