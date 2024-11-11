#include "calculator.h"
#include <stdio.h>
#include <math.h>


#define MAX_ARGUMENTS_COUNT 16

void print_commands() {
    printf("Available commands:\n");
    for (size_t i = 0; i < commands_count; i++) {
        printf("%zu: %s\n", i, commands[i].name);
    }
}

int main(void) {
    size_t command_index;
    size_t args_count;

    while (1) {
        print_commands();
        printf("Enter command index (-1 to quit)\n> ");
        scanf("%zu", &command_index);

        if (command_index == (size_t)-1) {
            break; // Завершение программы
        }

        if (command_index >= commands_count) {
            printf("Invalid command index\n");
            continue;
        }

        printf("Enter number of arguments (max %d)\n> ", MAX_ARGUMENTS_COUNT);
        scanf("%zu", &args_count);

        if (args_count > MAX_ARGUMENTS_COUNT) {
            printf("Too many arguments, max is %d\n", MAX_ARGUMENTS_COUNT);
            continue;
        }

        double args[MAX_ARGUMENTS_COUNT];
        printf("Enter arguments:\n");
        for (size_t i = 0; i < args_count; i++) {
            printf("> ");
            scanf("%lf", &args[i]);
        }

        // Вызов операции
        double result;
        switch (command_index) {
            case 0: // Addition
                result = addition(args_count, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]);
                break;
            case 1: // Substraction
                result = substraction(args_count, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]);
                break;
            case 2: // Multiplication
                result = multiplication(args_count, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]);
                break;
            case 3: // Division
                result = division(args_count, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]);
                break;
            default:
                printf("Invalid command\n");
                continue;
        }

        if (isnan(result)) {
            printf("Error: Division by zero\n");
        } else {
            printf("Result: %lf\n", result);
        }
    }

    return 0;
}
