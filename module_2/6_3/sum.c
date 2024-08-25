#include <stdio.h>
#include <stdarg.h>

double sum(int num_args, ...) {
    va_list args;
    va_start(args, num_args);
    double result = 0;

    for (int i = 0; i < num_args; i++) {
        result += va_arg(args, double);
    }

    va_end(args);
    return result;
}
