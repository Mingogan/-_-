#include <stdio.h>
#include <stdarg.h>

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
