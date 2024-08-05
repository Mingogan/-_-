#include <stdio.h>
#include <stdarg.h>

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
