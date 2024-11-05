#include "calculator.h"

#include <math.h>

#include <stdio.h>


double addition(size_t n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;
    for (size_t i = 0; i < n; i++) {
        result += va_arg(args, double);
    }

    va_end(args);

    return result;
}


double substraction(size_t n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;

    if (n > 0) {
        result = va_arg(args, double);
    }

    for (size_t i = 1; i < n; i++) {
        result -= va_arg(args, double);
    }

    va_end(args);

    return result;
}


double multiplication(size_t n, ...) {
    va_list args;
    va_start(args, n);

    double result = 1;

    if (n > 0) {
        result = va_arg(args, double);
    }

    for (size_t i = 1; i < n; i++) {
        result *= va_arg(args, double);
    }

    va_end(args);

    return result;
}


double division(size_t n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;
    double value;

    if (n > 0) {
        result = va_arg(args, double);
    }

    for (size_t i = 1; i < n; i++) {
        value = va_arg(args, double);

        if (value == 0) {
            return NAN;
        }

        result /= value;
    }

    va_end(args);

    return result;
}

Command commands[] = {
    {"add", addition},
    {"substract", substraction},
    {"multiply", multiplication},
    {"divide", division},
    {"sqrt", NULL},
};

size_t commands_count = sizeof(commands) / sizeof(commands[0]);
