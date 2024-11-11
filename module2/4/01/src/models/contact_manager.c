#include "models/contact_manager.h"

#include <string.h>
#include <stdio.h>


// Internal functions

Contact *contact_manager_get(ContactManager *self, int id);
int contact_manager_add(ContactManager *self, Contact *contact);
int contact_manager_update(ContactManager *self, Contact *contact);
int contact_manager_remove(ContactManager *self, int id);
ContactNode *contact_manager_get_node(ContactManager *self, int id);
void copy_contact(Contact* dst, Contact* src);
ContactNode *allocate_node();


Contact *contact_manager_get(ContactManager *self, int id) {
    Contact *contact = NULL;
    ContactNode *node = contact_manager_get_node(self, id);

    if (node != NULL) {
        contact = node->contact;
    }

    return contact;
}

int contact_manager_add(ContactManager *self, Contact *contact) {
    int status = OPERATION_SUCCESS;

    if (self == NULL || contact == NULL) {
        status = OPERATION_ERROR;
    } else {
        ContactNode *new_node = allocate_node();

        if (new_node == NULL) {
            status = OPERATION_ERROR;
        } else {
            copy_contact(new_node->contact, contact);
            new_node->contact->id = self->last_id++;
            new_node->next = NULL;
            new_node->prev = self->tail;

            if (self->tail != NULL) {  // Вставка в конец
                self->tail->next = new_node;
            } else {  // Первая вставка
                self->head = new_node;
            }

            self->tail = new_node;
        }
    }

    return status;
}

int contact_manager_update(ContactManager *self, Contact *contact) {
    int status = OPERATION_SUCCESS;

    if (self == NULL || contact == NULL) {
        status = OPERATION_ERROR;
    } else {
        Contact *existing_contact = contact_manager_get(self, contact->id);

        if (existing_contact == NULL) {
            status = OPERATION_ERROR;
        } else {
            contact_manager_remove(self, contact->id);
            status = contact_manager_add(self, contact);
        }
    }

    return status;
}

int contact_manager_remove(ContactManager *self, int id) {
    int status = OPERATION_ERROR;

    if (self != NULL) {
        ContactNode *node_to_remove = contact_manager_get_node(self, id);

        if (node_to_remove != NULL) {
            if (node_to_remove->prev != NULL) {
                node_to_remove->prev->next = node_to_remove->next;
            } else {
                self->head = node_to_remove->next;
            }

            if (node_to_remove->next != NULL) {
                node_to_remove->next->prev = node_to_remove->prev;
            } else {
                self->tail = node_to_remove->prev;
            }

            free_contact(node_to_remove->contact);
            free(node_to_remove);
            status = OPERATION_SUCCESS;
        }
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

    manager->head = NULL;
    manager->tail = NULL;
    manager->last_id = 1;
}

void contact_manager_clear(ContactManager *manager) {
    if (manager == NULL) {
        return;
    }

    ContactNode *current = manager->head;
    while (current != NULL) {
        ContactNode *next = current->next;
        free_contact(current->contact);
        free(current);
        current = next;
    }
    
    manager->head = NULL;
    manager->tail = NULL;
    manager->last_id = 1;
}

ContactNode *contact_manager_get_node(ContactManager *self, int id) {
    ContactNode *current = NULL;

    if (self != NULL) {
        current = self->head;

        while ((current != NULL) && (current->contact->id != id)) {
            current = current->next;
        }
    }

    return current;
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

ContactNode *allocate_node() {
    ContactNode *node = (ContactNode *)malloc(sizeof(ContactNode));
    
    if (node != NULL) {
        node->contact = (Contact *)malloc(sizeof(Contact));

        if (node->contact == NULL) {
            free(node);
            node = NULL;
        }
    }

    return node;
}
