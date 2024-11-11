#ifndef MODELS_CONTACT_H_
#define MODELS_CONTACT_H_


#include <stdlib.h>


#ifndef MAX_STRING_LENGTH
#define MAX_STRING_LENGTH 256
#endif  // MAX_STRING_LENGTH

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 32
#endif  // MAX_NAME_LENGTH

#ifndef MAX_PHONE_NUMBER_LENGTH
#define MAX_PHONE_NUMBER_LENGTH 18
#endif  // MAX_PHONE_NUMBER_LENGTH



/**
 * @brief Структура представляющая номер телефона
 * 
 */
typedef struct PhoneNumber {
    char name[MAX_NAME_LENGTH];                  ///< Имя ассоциированное с номером
    char phone_number[MAX_PHONE_NUMBER_LENGTH];  ///< Номер
} PhoneNumber;


/**
 * @brief Структура представляющая список номеров у контакта
 * 
 */
typedef struct PhoneNumberList {
    size_t length;         ///< Количество номеров
    PhoneNumber *data;  ///< Массив номеров
} PhoneNumberList;


/**
 * @brief Структура представляющая информацию о работе
 * 
 */
typedef struct Workplace {
    char company_name[MAX_STRING_LENGTH];  ///< Название компании
    char position[MAX_STRING_LENGTH];      ///< Должность
} Workplace;


/**
 * @brief Структура представляющая информацию об электронных адресах
 * 
 */
typedef struct Email {
    char workEmail[MAX_STRING_LENGTH];      ///< Адрес рабочего почтового ящика
    char personalEmail[MAX_STRING_LENGTH];  ///< Адрес личного почтового ящика
} Email;


/**
 * @brief Структура представляющая информацию о социальных сетях
 * 
 */
typedef struct SocialMedia {
    char vk[MAX_STRING_LENGTH];        ///< Адрес страницы вконтакте
    char telegram[MAX_STRING_LENGTH];  ///< Адрес аккаунта телеграм
} SocialMedia;


/**
 * @brief Структура представляющая контакт
 * 
 */
typedef struct Contact {
    int id;                             ///< Идентификатор
    char first_name[MAX_NAME_LENGTH];   ///< Имя
    char middle_name[MAX_NAME_LENGTH];  ///< Отчество
    char last_name[MAX_NAME_LENGTH];    ///< Фамилия
    PhoneNumberList phone_numbers;      ///< Список номеров
    Workplace workplace;                ///< Информация о работе
    Email email;                        ///< Информация об электронных адресах
    SocialMedia social_media;           ///< Информация о социальных сетях
} Contact;


// Инициализаторы

/**
 * @brief Инициализатор Contact
 * 
 * @return Contact 
 */
Contact empty_contact();


/**
 * @brief Инициализатор PhoneNumberList пустым массивом
 * 
 * @return PhoneNumberList 
 */
PhoneNumberList empty_phone_number_list();

/**
 * @brief Инициализатор PhoneNubmer
 * 
 * @return PhoneNumber 
 */
PhoneNumber empty_phone_number();

/**
 * @brief Инициализатор Workplace
 * 
 * @return Workplace 
 */
Workplace empty_workplace();


/**
 * @brief Инициализатор Email
 * 
 * @return Email 
 */
Email empty_email();


/**
 * @brief Инициализатор SocialMedia
 * 
 * @return SocialMedia 
 */
SocialMedia empty_social_media();


// Деструкторы

/**
 * @brief Деструктор Contact
 * 
 * @param contact 
 */
void free_contact(Contact *contact);


/**
 * @brief Деструктор PhoneNumberList
 * 
 * @param phone_number_list 
 */
void free_phone_number_list(PhoneNumberList *phone_number_list);

#endif  // MODELS_CONTACT_H_
