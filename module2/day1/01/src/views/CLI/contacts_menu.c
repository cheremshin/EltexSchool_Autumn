#include "views/CLI/contacts_menu.h"


#include <stdio.h>


int contacts_menu() {
    ContactManager manager;
    contact_manager_init(&manager);

    int exited = 0;

    while (!exited) {
        display_menu();
        exited = process_menu_choice(&manager);
    }

    contact_manager_clear(&manager);
    return 0;
}



void display_menu() {
    printf("====== Contact Manager ======\n");
    printf("1. Get all contacts\n");
    printf("2. Get contact\n");
    printf("3. Add contact\n");
    printf("4. Update contact\n");
    printf("5. Remove contact\n");
    printf("6. Exit\n");
    printf("=============================\n");
}

int process_menu_choice(ContactManager *manager) {
    int choice;

    printf("Enter your choice\n> ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            get_all_contacts(manager);
            break;
        case 2:
            get_contact(manager);
            break;
        case 3:
            add_contact(manager);
            break;
        case 4:
            update_contact(manager);
            break;
        case 5:
            remove_contact(manager);
            break;
        case 6:   // Exit
            return 1;
        default:
            printf("Invalid choice\n");
            break;
    }

    printf("\n");

    return 0;
}

void get_all_contacts(ContactManager *manager) {
    if (manager->contacts_count == 0) {
        printf("No contacts found\n");
    } else {
        for (size_t i = 0; i < manager->contacts_count; i++) {
            print_contact_brief(&manager->contacts[i]);
        }
    }
}

void get_contact(ContactManager *manager) {
    int id;

    printf("Enter contact id\n> ");
    scanf("%d", &id);

    Contact *contact = manager->get(manager, id);

    if (contact == NULL) {
        printf("Contact not found\n");
    } else {
        print_contact(contact);
    }
}

void add_contact(ContactManager *manager) {
    Contact contact = empty_contact();

    fill_contact(&contact);
    manager->add(manager, &contact);

    free_contact(&contact);
}

void update_contact(ContactManager *manager) {
    if (manager->contacts_count == 0) {
        printf("No contacts found\n");
    } else {
        int id;
        printf("Enter contact id\n> ");
        scanf("%d", &id);

        Contact contact = empty_contact();
        Contact *existing_contact = manager->get(manager, id);

        if (existing_contact == NULL) {
            printf("Contact not found\n");
        } else {
            contact.id = existing_contact->id;
            fill_contact(&contact);
            manager->update(manager, &contact);
        }

        free_contact(&contact);
    }
}

void remove_contact(ContactManager *manager) {
    if (manager->contacts_count == 0) {
        printf("No contacts found\n");
    } else {
        int id;
        printf("Enter contact id\n> ");
        scanf("%d", &id);

        manager->remove(manager, id);
    }
}


/**
 * @brief Выводит контакт в коротком виде
 * 
 * @param contact 
 */
void print_contact_brief(Contact *contact) {
    printf("%d. %s %s\n", contact->id,
                          contact->first_name,
                          contact->last_name);
}

void print_contact(Contact *contact) {
    printf("Contact '%d' details\n", contact->id);
    printf("%s %s %s\n", contact->first_name,
                            contact->middle_name,
                            contact->last_name);
    printf("\n");
    printf("Phone numbers\n");
    for (size_t i = 0; i < contact->phone_numbers.length; i++) {
        printf("%s - %s\n", contact->phone_numbers.data[i].name,
                            contact->phone_numbers.data[i].phone_number);
    }

    printf("\n");
    printf("Workplace\n");
    printf("Company name: %s\n", contact->workplace.company_name);
    printf("Position: %s\n", contact->workplace.position);

    printf("\n");
    printf("Email\n");
    printf("Work email: %s\n", contact->email.workEmail);
    printf("Personal email: %s\n", contact->email.personalEmail);

    printf("\n");
    printf("Social media\n");
    printf("VK: %s\n", contact->social_media.vk);
    printf("Telegram: %s\n", contact->social_media.telegram);
}

void fill_contact(Contact *contact) {
    printf("Enter first name\n> ");
    read_string(contact->first_name, MAX_NAME_LENGTH);
    printf("Enter last name\n> ");
    read_string(contact->last_name, MAX_NAME_LENGTH);


    printf("You can add additional info (1 - add, 0 - skip)\n> ");
    int additional_info = 0;
    scanf("%d", &additional_info);

    if (additional_info == 1) {
        printf("Enter middle name\n> ");
        read_string(contact->middle_name, MAX_NAME_LENGTH);

        int phone_number_count = 0;
        printf("Enter phone number count\n> ");
        scanf("%d", &phone_number_count);

        if (phone_number_count > 0) {
            PhoneNumberList phone_number_list = empty_phone_number_list();
            phone_number_list.length = phone_number_count;
            phone_number_list.data = (PhoneNumber *) malloc(sizeof(PhoneNumber) * phone_number_count);
            contact->phone_numbers = phone_number_list;

            for (int i = 0; i < phone_number_count; i++) {
                printf("Enter phone number name\n> ");
                read_string(phone_number_list.data[i].name, MAX_NAME_LENGTH);
                printf("Enter phone number\n> ");
                read_string(phone_number_list.data[i].phone_number, MAX_PHONE_NUMBER_LENGTH);
            }
        }

        printf("Enter workplace company name\n> ");
        read_string(contact->workplace.company_name, MAX_STRING_LENGTH);
        printf("Enter workplace position\n> ");
        read_string(contact->workplace.position, MAX_STRING_LENGTH);

        printf("Enter work email\n> ");
        read_string(contact->email.workEmail, MAX_STRING_LENGTH);
        printf("Enter personal email\n> ");
        read_string(contact->email.personalEmail, MAX_STRING_LENGTH);

        printf("Enter VK\n> ");
        read_string(contact->social_media.vk, MAX_STRING_LENGTH);
        printf("Enter Telegram\n> ");
        read_string(contact->social_media.telegram, MAX_STRING_LENGTH);
    }
}

void read_string(char *str, int max_length) {
    int i = 0;
    char ch = getchar();

    // Пропускаем пробелы
    while (ch == ' ' || ch == '\t' || ch == '\n') {
        ch = getchar();
    };

    while (ch != '\n' && i < max_length) {
        str[i++] = ch;
        ch = getchar();
    }

    str[i] = '\0';
}
