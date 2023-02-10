#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    int c1 = 0, d = 0, u = 0, s = 0, skip = 0;
    char *name;
    if (argc >= 2){
        name = argv[1];
        if (argc >= 3){
            if (strcmp("-c", argv[1]) == 0){
                c1 = 1;
            } else if (strcmp("-d", argv[1]) == 0){
                d = 1;
            } else if (strcmp("-u", argv[1]) == 0){
                u = 1;
            } else if(strcmp("-s", argv[1]) == 0){
                s = 1;
            }
            name = argv[2];
            if (argc >= 4){
                if (s == 1){
                    skip = atoi(argv[2]);
                    s = 0;
                }
                if (strcmp("-c", argv[2]) == 0){
                    c1 = 1;
                } else if (strcmp("-d", argv[2]) == 0){
                    d = 1;
                } else if (strcmp("-u", argv[2]) == 0){
                    u = 1;
                } else if(strcmp("-s", argv[2]) == 0){
                    s = 1;
                }
                name = argv[3];
                if (argc >= 5){
                    if (s == 1){
                        skip = atoi(argv[3]);
                        s = 0;
                    }
                    if (strcmp("-c", argv[3]) == 0){
                        c1 = 1;
                    } else if (strcmp("-d", argv[3]) == 0){
                        d = 1;
                    } else if (strcmp("-u", argv[3]) == 0){
                        u = 1;
                    } else if(strcmp("-s", argv[3]) == 0){
                        s = 1;
                    }
                    name = argv[4];
                    if (argc == 6){
                        if (s == 1){
                            skip = atoi(argv[4]);
                            s = 0;
                        }
                        if (strcmp("-c", argv[4]) == 0){
                            c1 = 1;
                        } else if (strcmp("-d", argv[4]) == 0){
                            d = 1;
                        } else if (strcmp("-u", argv[4]) == 0){
                            u = 1;
                        } else if(strcmp("-s", argv[4]) == 0){
                            s = 1;
                        }
                        name = argv[5];
                    }
                }
            }
        }
    }
    FILE *file;
    char **list = NULL;
    int *same = NULL;
    char c;
    list = malloc(sizeof(char*));
    file = fopen(name, "r");
    int i = 0;
    int size;
    c = fgetc(file);
    while (c != EOF){
        list[i] = NULL;
        list[i] = malloc(sizeof(char));
        int counter = 0;
        while (c != '\n'){
            list[i][counter] = c;
            counter++;
            c = fgetc(file);
            list[i] = realloc(list[i], sizeof(char)*(counter+1));
        }
        list[i][counter] = '\0';
        i++;
        c = fgetc(file);
        list = realloc(list, sizeof(char*)*(i+1));
    }
    fclose(file);
    int *check_same = NULL;
    check_same = (int*)calloc((i+1), sizeof(int));
    same = (int*)calloc((i+1), sizeof(int));
    size = i;
    i = 0;
    char *s1;
    char *s2;
    int check1 = 0;
    for(i = 0; i < size; i ++){
        if (strlen(list[i]) < skip){
            continue;
        }
        s1 = &list[i][skip];
        check1 = 0;
        for (int j = 0; j < size; j++){
            if (i == j){
                continue;
            }
            if (strlen(list[j]) < skip){
                continue;
            }
            s2 = &list[j][skip];
            if (strcmp(s1, s2) == 0){
                same[j]++;
                if (check_same[j] == 1){
                    check1 = 1;
                }
                if ((check1 == 0)){
                    check_same[i] = 1;
                }
            }
        }
        check1 = 0;
    }
    for (i = 0; i < size; i ++){
        if (d == 1){
            if (same[i] != 0){
                if (c1 == 1){
                    printf("%d ", same[i]+1);
                }
                printf("%s\n", list[i]);
            }
        } else if (u == 1){
            if (same[i] == 0){
                if (c1 == 1){
                    printf("%d ", same[i]+1);
                }
                printf("%s\n", list[i]);
            }
        }else {
            if (same[i] != 0){
                if (check_same[i] == 1){
                    if (c1 == 1){
                        printf("%d ", same[i]+1);
                    }
                 printf("%s\n", list[i]);
                }
            } else {
                if (c1 == 1){
                    printf("%d ", same[i]+1);
                }
                printf("%s\n", list[i]);
            }
        }
    }

    free(same);
    for(int j = 0; j < i; j++){
        free(list[j]);
    }
    free(list);
    free(check_same);
    return 0;
}