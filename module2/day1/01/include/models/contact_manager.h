#ifndef MODELS_CONTACT_MANAGER_H_
#define MODELS_CONTACT_MANAGER_H_


#include "contact.h"

#include <stdlib.h>


/**
 * @brief Статус коды операций
 * 
 */

#ifndef OPERATION_SUCCESS
#define OPERATION_SUCCESS 0
#endif  // OPERATION_SUCCESS

#ifndef OPERATION_ERROR
#define OPERATION_ERROR 1
#endif  // OPERATION_ERROR


typedef struct ContactManager ContactManager;


/**
 * @brief Операция получения контакта по id
 * 
 * @param self Указатель на менеджер контактов
 * @param id Идентификатор
 * 
 * Не рекомендуется напрямую изменять Contact, полученный этой функцией,
 * для этого воспользуйтесь ContactManagerUpdate
 * 
 * @return Указатель на контакт, если существует, иначе - NULL
 */
typedef Contact *(*ContactManagerGet)(struct ContactManager *self, int id);


/**
 * @brief Операция добавления контакта
 * 
 * @param self Указатель на менеджер контактов
 * @param contact Указатель на добавляемый контакт
 * 
 * Осуществляет копирование данных из contact.
 * Рекомендуется использовать пустой Contact, а после добавления очищать его.
 * 
 * @return Статус код операции
 */
typedef int (*ContactManagerAdd)(struct ContactManager *self, Contact *contact);


/**
 * @brief Операция обновления контакта
 * 
 * @param self Указатель на менеджер контактов
 * @param contact Указатель на контакт, по которому производится обновление
 * 
 * Осуществляет копирование данных из contact.
 * Рекомендуется использовать скопированный Contact из ContactManagerGet, а после обновления очищать его.
 * 
 * @return Статус код операции
 */
typedef int (*ContactManagerUpdate)(struct ContactManager *self, Contact *contact);


/**
 * @brief Операция удаления контакта
 * 
 * @param self Указатель на менеджер контактов
 * @param id Идентификатор контакта
 * 
 * 
 * @return Статус код операции
 */
typedef int (*ContactManagerRemove)(struct ContactManager *self, int id);



/**
 * @brief Структура, представляющая из себя телефонную книгу
 * 
 */
typedef struct ContactManager {
    size_t contacts_count;  ///< Количество контактов
    Contact *contacts;   ///< Массив контактов
    size_t contacts_capacity;  ///< Размер массива
    int last_id; ///< Последний выданный идентификатор

    ContactManagerGet get;
    ContactManagerAdd add;
    ContactManagerUpdate update;
    ContactManagerRemove remove;
} ContactManager;


/**
 * @brief Инициализация менеджера
 * 
 * @param manager Указатель переменную, где менеджер будет храниться
 */
void contact_manager_init(ContactManager *manager);

/**
 * @brief Очистка памяти после использования
 * 
 * @param manager Указатель на менеджер, который необходимо очистить
 */
void contact_manager_clear(ContactManager *manager);


#endif  // MODELS_CONTACT_MANAGER_H_
