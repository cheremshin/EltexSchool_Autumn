#include "models/contact.h"


Contact empty_contact() {
    Contact contact = {
        .id = 0,
        .first_name = {0},
        .middle_name = {0},
        .last_name = {0},
        .phone_numbers = empty_phone_number_list(),
        .workplace = empty_workplace(),
        .email = empty_email(),
        .social_media = empty_social_media()
    };

    return contact;
}

PhoneNumberList empty_phone_number_list() {
    PhoneNumberList phone_number_list = {
        .length = 0,
        .data = NULL
    };

    return phone_number_list;
}

Workplace empty_workplace() {
    Workplace workplace = {
        .company_name = {0},
        .position = {0}
    };

    return workplace;
}

Email empty_email() {
    Email email = {
        .workEmail = {0},
        .personalEmail = {0}
    };

    return email;
}

SocialMedia empty_social_media() {
    SocialMedia social_media = {
        .vk = {0},
        .telegram = {0}
    };

    return social_media;
}

void free_contact(Contact *contact) {
    free_phone_number_list(&contact->phone_numbers);
}

void free_phone_number_list(PhoneNumberList *phone_number_list) {
    free(phone_number_list->data);
    phone_number_list->data = NULL;
    phone_number_list->length = 0;
}
