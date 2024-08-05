#include <stdio.h>
#include <stdarg.h>

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
