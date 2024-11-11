#include "models/contact_manager.h"

#include <string.h>
#include <stdio.h>


// Internal functions

Contact *contact_manager_get(ContactManager *self, int id);
int contact_manager_add(ContactManager *self, Contact *contact);
int contact_manager_update(ContactManager *self, Contact *contact);
int contact_manager_remove(ContactManager *self, int id);
int expand(ContactManager *self);
void copy_contact(Contact* dst, Contact* src);


Contact *contact_manager_get(ContactManager *self, int id) {
    if (self == NULL) {
        return NULL;
    }

    Contact *contact = NULL;

    for (size_t i = 0; i < self->contacts_count; i++) {
        if (self->contacts[i].id == id) {
            contact = &self->contacts[i];
            break;
        }
    }

    return contact;
}

int contact_manager_add(ContactManager *self, Contact *contact) {
    if (self == NULL) {
        return OPERATION_ERROR;
    }

    int status = OPERATION_SUCCESS;

    if (self->contacts_count == self->contacts_capacity) {
        status = expand(self);
    }

    if (status == OPERATION_SUCCESS) {
        copy_contact(&self->contacts[self->contacts_count], contact);
        self->contacts[self->contacts_count].id = self->last_id++;

        self->contacts_count++;
    }

    return status;
}

int contact_manager_update(ContactManager *self, Contact *contact) {
    if (self == NULL) {
        return OPERATION_ERROR;
    }

    int status = OPERATION_SUCCESS;

    Contact *existing_contact = contact_manager_get(self, contact->id);

    if (existing_contact != NULL) {
        contact_manager_remove(self, contact->id);
        status = contact_manager_add(self, contact);
    } else {
        status = OPERATION_ERROR;
    }

    return status;
}

int contact_manager_remove(ContactManager *self, int id) {
    if (self == NULL) {
        return OPERATION_ERROR;
    }

    int status = OPERATION_SUCCESS;

    int found = 0;
    for (size_t i = 0; i < self->contacts_count; i++) {
        if (!found) {
            if (self->contacts[i].id == id) {
                found = 1;

                free_contact(&self->contacts[i]);
            }
        } else {
            copy_contact(&self->contacts[i - 1], &self->contacts[i]);
            free_contact(&self->contacts[i]);
        }
    }

    if (found) {
        self->contacts_count--;
    } else {
        status = OPERATION_ERROR;
    }

    return status;
}


void contact_manager_init(ContactManager *manager) {
    if (manager == NULL) {
        return;
    }

    manager->get = contact_manager_get;
    manager->add = contact_manager_add;
    manager->update = contact_manager_update;
    manager->remove = contact_manager_remove;

    manager->contacts = NULL;
    manager->contacts_count = 0;
    manager->contacts_capacity = 0;
    manager->last_id = 1;
    expand(manager);
}

void contact_manager_clear(ContactManager *manager) {
    if (manager == NULL) {
        return;
    }

    for (size_t i = 0; i < manager->contacts_count; i++) {
        free_contact(&manager->contacts[i]);
    }

    free(manager->contacts);
    manager->contacts = NULL;
    manager->contacts_count = 0;
    manager->contacts_capacity = 0;
    manager->last_id = 1;
}

int expand(ContactManager *self) {
    int status = OPERATION_SUCCESS;

    // Initial capacity
    if (self->contacts_capacity == 0) {
        self->contacts_capacity = 8;
    }

    // Increase capacity
    self->contacts_capacity *= 2;

    Contact *new_contacts = malloc(self->contacts_capacity * sizeof(Contact));

    if (new_contacts == NULL) {
        status = OPERATION_ERROR;
    } else {
        for (size_t i = 0; i < self->contacts_count; i++) {
            copy_contact(&new_contacts[i], &self->contacts[i]);
            free_contact(&self->contacts[i]);
        }

        free(self->contacts);
        self->contacts = new_contacts;
    }

    return status;
}

void copy_contact(Contact* dst, Contact* src) {
    dst->id = src->id;

    strncpy(dst->first_name, src->first_name, MAX_NAME_LENGTH);
    strncpy(dst->middle_name, src->middle_name, MAX_NAME_LENGTH);
    strncpy(dst->last_name, src->last_name, MAX_NAME_LENGTH);

    strncpy(dst->workplace.company_name, src->workplace.company_name, MAX_STRING_LENGTH);
    strncpy(dst->workplace.position, src->workplace.position, MAX_STRING_LENGTH);

    strncpy(dst->email.workEmail, src->email.workEmail, MAX_STRING_LENGTH);
    strncpy(dst->email.personalEmail, src->email.personalEmail, MAX_STRING_LENGTH);

    strncpy(dst->social_media.vk, src->social_media.vk, MAX_STRING_LENGTH);
    strncpy(dst->social_media.telegram, src->social_media.telegram, MAX_STRING_LENGTH);

    if (src->phone_numbers.data != NULL) {
        dst->phone_numbers.length = src->phone_numbers.length;
        dst->phone_numbers.data = malloc(src->phone_numbers.length * sizeof(PhoneNumber));
        memcpy(dst->phone_numbers.data, src->phone_numbers.data, src->phone_numbers.length * sizeof(PhoneNumber));
    } else {
        dst->phone_numbers.length = 0;
        dst->phone_numbers.data = NULL;
    }
}
