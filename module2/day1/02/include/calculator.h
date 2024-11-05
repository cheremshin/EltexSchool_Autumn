#ifndef CALCULATOR_H_
#define CALCULATOR_H_


#include <stddef.h>
#include <stdarg.h>


/**
 * @brief Сумма n чисел
 * 
 * @param n количество аргументов
 * @param ... аргументы типа double
 * @return double 
 */
double addition(size_t n, ...);

/**
 * @brief Разность первого и последующий чисел
 * 
 * @param n количество аргументов
 * @param ... аргументы типа double
 * @return double 
 */
double substraction(size_t n, ...);

/**
 * @brief Произведение n чисел
 * 
 * @param n количество аргументов
 * @param ... аргументы типа double
 * @return double 
 */
double multiplication(size_t n, ...);

/**
 * @brief Деление n чисел 
 * 
 * @param n количество аргументов
 * @param ... аргументы типа double
 * @return double 
 */
double division(size_t n, ...);

#endif  // CALCULATOR_H_
