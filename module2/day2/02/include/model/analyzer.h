#ifndef MODEL_ANALYZER_H_
#define MODEL_ANALYZER_H_

#include <stdint.h>

/**
 * @brief Конвертация IP-адреса в виде строки в формат uint32_t
 * 
 * @param ip Строка с IP-адресом
 * @return uint32_t Числовое представление IP-адреса
 */
uint32_t ip_to_int(const char *ip);

/**
 * @brief Проверка на соответствие ip-адреса подсети
 * 
 * @param ip IP-адрес
 * @param subnet Подсеть в которой проверяется ip
 * @param mask Маска подсети
 * @return int Возвращает 1, если ip входит в подсеть, 0 иначе
 */
int is_ip_in_subnet(uint32_t ip, uint32_t subnet, uint32_t mask);


/**
 * @brief Вспомогательная функция для генерации случайного ip-адреса
 * 
 * @return uint32_t Числовое представление IP-адреса
 */
uint32_t generate_random_ip();


#endif  // MODEL_ANALYZER_H_
