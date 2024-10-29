#ifndef VIEWS_CLI_CONTACTS_MENU_H_
#define VIEWS_CLI_CONTACTS_MENU_H_

#include "models/contact_manager.h"


/**
 * @brief Функция, запускающая консольное приложение
 * 
 * @return int Код ошибки
 */
int contacts_menu();



void display_menu();
int process_menu_choice(ContactManager *manager);

void get_all_contacts(ContactManager *manager);
void get_contact(ContactManager *manager);
void add_contact(ContactManager *manager);
void update_contact(ContactManager *manager);
void remove_contact(ContactManager *manager);


void print_contact_brief(Contact *contact);
void print_contact(Contact *contact);
void fill_contact(Contact *contact);

void read_string(char *str, int max_length);

#endif  // VIEWS_CLI_CONTACTS_MENU_H_
