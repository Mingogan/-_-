#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>

void printMode(mode_t mode){
    printf("Битовое представление: %o\n", mode & 0777);

    printf("Буквенное представление: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "r" : "-");
    printf((mode & S_IXUSR) ? "r" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "r" : "-");
    printf((mode & S_IXGRP) ? "r" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "r" : "-");
    printf((mode & S_IXOTH) ? "r" : "-");
    
}

mode_t updadteMode(){

}

int main(){
    
}


