#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdarg.h>

typedef double (*operation_func)(int, ...);

void* load_function(const char* lib_name, const char* func_name) {
    void* handle = dlopen(lib_name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка при загрузке библиотеки %s: %s\n", lib_name, dlerror());
        exit(1);
    }

    void* func = dlsym(handle, func_name);
    if (!func) {
        fprintf(stderr, "Ошибка при загрузке функции: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }

    return func;
}

int main() {
    int choice;
    int num_args;
    double args[5];  

    void* handles[4];
    operation_func functions[4];

    handles[0] = load_function("./libsum.so", "sum");
    handles[1] = load_function("./libsubtract.so", "subtract");
    handles[2] = load_function("./libmultiply.so", "multiply");
    handles[3] = load_function("./libdivide.so", "divide");

    functions[0] = (operation_func)handles[0];
    functions[1] = (operation_func)handles[1];
    functions[2] = (operation_func)handles[2];
    functions[3] = (operation_func)handles[3];

    while (1) {
        printf("Выберите команду:\n");
        printf("1 - sum\n");
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
        if (num_args > 5) {
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
                result = functions[choice-1](1, args[0]);
                break;
            case 2:
                result = functions[choice-1](2, args[0], args[1]);
                break;
            case 3:
                result = functions[choice-1](3, args[0], args[1], args[2]);
                break;
            case 4:
                result = functions[choice-1](4, args[0], args[1], args[2], args[3]);
                break;
            case 5:
                result = functions[choice-1](5, args[0], args[1], args[2], args[3], args[4]);
                break;
            default:
                printf("Много аргументов\n");
                continue;
        }
        printf("Результат: %lf\n\n", result);
    }

    for (int i = 0; i < 4; i++) {
        dlclose(handles[i]);
    }

    return 0;
}