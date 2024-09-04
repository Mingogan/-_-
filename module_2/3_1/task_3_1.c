#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>

void printMode(mode_t mode) {
    printf("Битовое представление: %o\n", mode & 0777);

    printf("Буквенное представление: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

mode_t updateMode(mode_t current_mode, char target, char operation, char action) {
    mode_t mask = 0;
    mode_t action_mask;

    switch(action){
        case 'r':
            action_mask = S_IRUSR | S_IRGRP | S_IROTH;
            break;
        case 'w':
            action_mask = S_IWUSR | S_IWGRP | S_IWOTH;
            break;
        case 'x':
            action_mask = S_IXUSR | S_IXGRP | S_IXOTH;
            break;
        default:
            fprintf(stderr, "Недопустимое действие: %c\n", action);
            exit(EXIT_FAILURE);
    }
    
    if (target == 'u') { 
        mask = action_mask & (S_IRUSR | S_IWUSR | S_IXUSR);
    } else if (target == 'g') { 
        mask = action_mask & (S_IRGRP | S_IWGRP | S_IXGRP);
    } else if (target == 'o') { 
        mask = action_mask & (S_IROTH | S_IWOTH | S_IXOTH);
    } else if (target == 'a') { // Все 
        mask = action_mask;
    }

    switch (operation) {
        case '+': 
            current_mode |= mask;
            break;
        case '-': 
            current_mode &= ~mask;
            break;
        case '=': 
            if (target == 'u') {
                current_mode = (current_mode & ~0700) | (mask & 0700);
            } else if (target == 'g') {
                current_mode = (current_mode & ~0070) | (mask & 0070);
            } else if (target == 'o') {
                current_mode = (current_mode & ~0007) | (mask & 0007);
            } else if (target == 'a') {
                current_mode = (current_mode & ~0777) | mask;
            }
            break;
        default:
            fprintf(stderr, "Недопустимая операция: %c\n", operation);
            exit(EXIT_FAILURE);
    }
    return current_mode;
}

int main() {
    char input[20];
    struct stat rights;
    mode_t mode;

    while (1) {
        printf("\n1. Ввести права доступа вручную\n");
        printf("2. Считать права доступа из файла\n");
        printf("3. Для выхода\n");

        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "3\n") == 0) {
            break;
        }

        if (strcmp(input, "1\n") == 0) {
            printf("Введите права доступа в буквенном (wxrwxr--) или цифровом формате (0777): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if (input[0] == '0') {
                sscanf(input, "%o", &mode);
            } else {
                mode = 0;
                if (input[0] == 'r') mode |= S_IRUSR;
                if (input[1] == 'w') mode |= S_IWUSR;
                if (input[2] == 'x') mode |= S_IXUSR;
                if (input[3] == 'r') mode |= S_IRGRP;
                if (input[4] == 'w') mode |= S_IWGRP;
                if (input[5] == 'x') mode |= S_IXGRP;
                if (input[6] == 'r') mode |= S_IROTH;
                if (input[7] == 'w') mode |= S_IWOTH;
                if (input[8] == 'x') mode |= S_IXOTH;
            }
            printMode(mode);

        } else if (strcmp(input, "2\n") == 0) {
            printf("Введите имя файла: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if (stat(input, &rights) == 0) {
                printf("Имя файла: %s\n", input);
                printf("Цифровое представление: %o\n", rights.st_mode & 0777);
                printMode(rights.st_mode);
                mode = rights.st_mode;
            } 
        } else {
            printf("Неправильный ввод\n");
            continue;
        }

        // Изменение прав доступа
        printf("Введите команду для изменения прав (u+x): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 3) {
            mode = updateMode(mode, input[0], input[1], input[2]);
            printMode(mode);
        } else {
            printf("Неверный формат команды для изменения прав\n");
        }
    }
    return 0;
}
