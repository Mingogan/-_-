#include <stdio.h>
#include <stdarg.h>

double add(int num_args, ...) {
    va_list args;
    va_start(args, num_args);
    double sum = 0;

    for (int i = 0; i < num_args; i++) {
        sum += va_arg(args, double);
    }

    va_end(args);
    return sum;
}

double subtract(int num_args, ...) {
    va_list args;
    va_start(args, num_args);
    double result = va_arg(args, double);
    for (int i = 0; i < num_args-1; i++) {
        if (num_args > 1) {
            result -= va_arg(args, double);
        }
    }

    va_end(args);
    return result;
}

double multiply(int num_args, ...) {
    va_list args;
    va_start(args, num_args);
    double product = 1;

    for (int i = 0; i < num_args; i++) {
        product *= va_arg(args, double);
    }

    va_end(args);
    return product;
}

double divide(int num_args, ...) {
    va_list args;
    va_start(args, num_args);
    double result = va_arg(args, double);
    for (int i = 0; i < num_args-1; i++) {
        if (num_args > 1) {
            double divisor = va_arg(args, double);
            if (divisor != 0) {
                result /= divisor;
            } else {
                printf("На ноль делить нельзя\n");
                result = 0;
            }
        }
    }

    va_end(args);
    return result;
}

typedef struct {
    char *name;
    double (*func)(int, ...);
} Function;

Function functions[] = {
    {"add", add},
    {"subtract", subtract},
    {"multiply", multiply},
    {"divide", divide}
};

int main() {
    int choice;
    int num_args;
    double args[5];  

    while (1) {
        printf("Выберите команду:\n");
        printf("1 - add\n");
        printf("2 - subtract\n");
        printf("3 - multiply\n");
        printf("4 - divide\n");
        printf("0 - exit\n");
        printf("Введите номер команды: ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > 4) {
            printf("Неверная команда: %d\n", choice);
            continue;
        }
        
        printf("Введите количество аргументов: ");
        scanf("%d", &num_args);
        if (num_args>5){
            printf("Много аргументов\n");
            continue;
        }

        printf("Введите аргументы: ");
        for (int i = 0; i < num_args; i++) {
            scanf("%lf", &args[i]);
        }

        double result;
        switch (num_args) {
            case 1:
                result = functions[choice-1].func(1, args[0]);
                break;
            case 2:
                result = functions[choice-1].func(2, args[0], args[1]);
                break;
            case 3:
                result = functions[choice-1].func(3, args[0], args[1], args[2]);
                break;
            case 4:
                result = functions[choice-1].func(4, args[0], args[1], args[2], args[3]);
                break;
            case 5:
                result = functions[choice-1].func(5, args[0], args[1], args[2], args[3], args[4]);
                break;
            default:
                printf("Много аргументов\n");
                continue;
        }
        printf("Результат: %lf\n\n", result);
    }

    return 0;
}