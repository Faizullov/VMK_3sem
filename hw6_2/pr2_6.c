#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char **argv){
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
    FILE *file;
    int n = 1;
    char *s = " ";
    int num = 1;
    char *name;
    int solve;

    if (argc == 5){
        n = (atoi(argv[2]))*(-1);
        s = argv[1];
        num = atoi(argv[3]);
        name = argv[4];
    }else if (argc == 4){
        name = argv[3];
        if (atoi(argv[1]) == 0){
            s = argv[1];
            if (atoi(argv[2]) < 0){
                n = atoi(argv[2])*(-1);
            } else {
                num = atoi(argv[2]);
            }
        } else {
            n = atoi(argv[1])*(-1);
            num = atoi(argv[2]);
        }
    } else if (argc == 3){
        name = argv[2];
        if (atoi(argv[1]) == 0){
            s = argv[1];
        } else{
            if (atoi(argv[1]) < 1){
                n = (atoi(argv[1]))*(-1);
            }else{
                num = atoi(argv[1]);
            }
        }
    }else if (argc == 2){
        name = argv[1];
    }
    
    if(strcmp(s, "-s"))
        solve = 1;
    else 
        solve = 0;
    file = fopen(name, "r");
    if (file){
        printf("To show more strings, enter: space\n");
        char c, f;
        f = 'a';
        // skip
        int j = 1;
        while (j != num){
            f = fgetc(file);
            while ((f != '\n') && (f != EOF)){
                f = fgetc(file);
            }
            j++;
        }
        int check = 0;
        c = getchar();
        if (c == 'q')
            printf("stop\n");
        else 
            printf("string/strings:\n");
        f = fgetc(file);
        int counter = 0;
        while ((c != 'q') && (f != EOF)){
            counter = 1;
            check = 1;
            while ((c != 'q') && (f != EOF) && (counter <= n)){
                if (c == ' '){
                    char *str;
                    int i = 1;
                    if ((f != '\n') && (f != EOF)){
                        check = 1;
                        str = malloc(sizeof(char));
                        counter++;
                        while ((f != '\n') && (f != EOF)){
                            str[i-1] = f;
                            f = fgetc(file);
                            i ++;
                            str = realloc(str, sizeof(char)*i);
                        }
                        str[i-1] = '\0';
                        printf("%s", str);
                        printf("\n");
                        free(str);
                    } else {
                        if (((check == 1) && (f != EOF)) || solve){
                            printf("\n");
                            counter++;
                        }
                        check = 0;
                    }
                }
                f = fgetc(file);
            }
            if (f != EOF){
                c = getchar();
                if (c == 'q')
                    printf("stop\n");
                else 
                    printf("string/strings:\n");
            }
        }
        fclose(file);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
        return 0;
    } else {
        printf("WRONG NAME\n");
        return 0;
    }
}