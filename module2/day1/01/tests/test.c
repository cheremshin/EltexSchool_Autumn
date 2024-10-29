#include <check.h>
#include "models/contact_manager.h"
#include "models/contact.h"


START_TEST(contact_manager_init_test) {
    ContactManager manager;
    contact_manager_init(&manager);
    
    ck_assert_ptr_nonnull(manager.contacts);
    ck_assert_int_eq(manager.contacts_count, 0);
    ck_assert_int_eq(manager.contacts_capacity, 16);

    contact_manager_clear(&manager);
}
END_TEST

START_TEST(contact_manager_add_test) {
    ContactManager manager;
    contact_manager_init(&manager);

    Contact contact = empty_contact();
    strncpy(contact.first_name, "Sergei", MAX_NAME_LENGTH);
    strncpy(contact.last_name, "Cheremisin", MAX_NAME_LENGTH);
    contact.phone_numbers.length = 1;
    contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber));
    strncpy(contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
    strncpy(contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);

    int status = manager.add(&manager, &contact);
    ck_assert_int_eq(status, OPERATION_SUCCESS);
    ck_assert_uint_eq(manager.contacts_count, 1);
    ck_assert_str_eq(manager.contacts[0].first_name, "Sergei");
    ck_assert_str_eq(manager.contacts[0].last_name, "Cheremisin");
    ck_assert_int_eq(manager.contacts[0].phone_numbers.length, 1);
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[0].name, "Phone number 1");
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[0].phone_number, "1234567890");

    free(contact.phone_numbers.data);
    contact_manager_clear(&manager);
}
END_TEST


START_TEST(contact_manager_get_test) {
    ContactManager manager;
    contact_manager_init(&manager);

    Contact contact = empty_contact();
    strncpy(contact.first_name, "Sergei", MAX_NAME_LENGTH);
    strncpy(contact.last_name, "Cheremisin", MAX_NAME_LENGTH);
    contact.phone_numbers.length = 1;
    contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber));
    strncpy(contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
    strncpy(contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);

    int status = manager.add(&manager, &contact);
    ck_assert_int_eq(status, OPERATION_SUCCESS);

    Contact *found_contact = manager.get(&manager, manager.contacts[0].id);
    ck_assert_ptr_nonnull(found_contact);
    ck_assert_str_eq(found_contact->first_name, "Sergei");
    ck_assert_str_eq(found_contact->last_name, "Cheremisin");
    ck_assert_int_eq(found_contact->phone_numbers.length, 1);
    ck_assert_str_eq(found_contact->phone_numbers.data[0].name, "Phone number 1");
    ck_assert_str_eq(found_contact->phone_numbers.data[0].phone_number, "1234567890");

    free(contact.phone_numbers.data);
    contact_manager_clear(&manager);
}
END_TEST

START_TEST(contact_manager_update_test) {
    ContactManager manager;
    contact_manager_init(&manager);

    Contact contact = empty_contact();
    strncpy(contact.first_name, "Sergei", MAX_NAME_LENGTH);
    strncpy(contact.last_name, "Cheremisin", MAX_NAME_LENGTH);
    contact.phone_numbers.length = 1;
    contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber));
    strncpy(contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
    strncpy(contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);

    int status = manager.add(&manager, &contact);
    ck_assert_int_eq(status, OPERATION_SUCCESS);
    
    Contact updated_contact = empty_contact();
    updated_contact.id = manager.contacts[0].id;
    strncpy(updated_contact.first_name, "ANTON", MAX_NAME_LENGTH);
    strncpy(updated_contact.last_name, "ANTONOV", MAX_NAME_LENGTH);
    updated_contact.phone_numbers.length = 2;
    updated_contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber) * 2);
    strncpy(updated_contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
    strncpy(updated_contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);
    strncpy(updated_contact.phone_numbers.data[1].name, "Phone number 2", MAX_NAME_LENGTH);
    strncpy(updated_contact.phone_numbers.data[1].phone_number, "9876543210", MAX_PHONE_NUMBER_LENGTH);

    status = manager.update(&manager, &updated_contact);
    ck_assert_int_eq(status, OPERATION_SUCCESS);
    ck_assert_uint_eq(manager.contacts_count, 1);
    ck_assert_str_eq(manager.contacts[0].first_name, "ANTON");
    ck_assert_str_eq(manager.contacts[0].last_name, "ANTONOV");
    ck_assert_int_eq(manager.contacts[0].phone_numbers.length, 2);
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[0].name, "Phone number 1");
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[0].phone_number, "1234567890");
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[1].name, "Phone number 2");
    ck_assert_str_eq(manager.contacts[0].phone_numbers.data[1].phone_number, "9876543210");

    free(contact.phone_numbers.data);
    free(updated_contact.phone_numbers.data);
    contact_manager_clear(&manager);
}
END_TEST

START_TEST(contact_manager_remove_test) {
    ContactManager manager;
    contact_manager_init(&manager);

    Contact contact = empty_contact();
    strncpy(contact.first_name, "Sergei", MAX_NAME_LENGTH);
    strncpy(contact.last_name, "Cheremisin", MAX_NAME_LENGTH);
    contact.phone_numbers.length = 1;
    contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber));
    strncpy(contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
    strncpy(contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);

    int status = manager.add(&manager, &contact);
    ck_assert_int_eq(status, OPERATION_SUCCESS);

    status = manager.remove(&manager, manager.contacts[0].id);
    ck_assert_int_eq(status, OPERATION_SUCCESS);
    ck_assert_uint_eq(manager.contacts_count, 0);

    free(contact.phone_numbers.data);
    contact_manager_clear(&manager);
}
END_TEST

START_TEST(contact_manager_expand_test) {
    ContactManager manager;
    contact_manager_init(&manager);

    for (int i = 0; i < 20; i++) {
        Contact contact = empty_contact();
        strncpy(contact.first_name, "Test" + i, MAX_NAME_LENGTH);
        strncpy(contact.last_name, "Testov" + i, MAX_NAME_LENGTH);
        contact.phone_numbers.length = 1;
        contact.phone_numbers.data = (PhoneNumber *) malloc(sizeof(PhoneNumber));
        strncpy(contact.phone_numbers.data[0].name, "Phone number 1", MAX_NAME_LENGTH);
        strncpy(contact.phone_numbers.data[0].phone_number, "1234567890", MAX_PHONE_NUMBER_LENGTH);

        int status = manager.add(&manager, &contact);
        ck_assert_int_eq(status, OPERATION_SUCCESS);

        free(contact.phone_numbers.data);
    }

    ck_assert_uint_eq(manager.contacts_count, 20);
    ck_assert_uint_eq(manager.contacts_capacity, 32);

    contact_manager_clear(&manager);
}
END_TEST

int main(void) {
    Suite *s = suite_create("ContactManager");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, contact_manager_init_test);
    tcase_add_test(tc_core, contact_manager_add_test);
    tcase_add_test(tc_core, contact_manager_update_test);
    tcase_add_test(tc_core, contact_manager_remove_test);
    tcase_add_test(tc_core, contact_manager_expand_test);

    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}