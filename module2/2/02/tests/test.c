#include <stdlib.h>
#include <check.h>

#include "calculator.h"


START_TEST(test_add) {
    ck_assert_double_eq(addition(0), 0);
    ck_assert_double_eq(addition(1, 2.0), 2);
    ck_assert_double_eq(addition(2, 1.0, 2.0), 3);
    ck_assert_double_eq(addition(3, 1.0, 3.0, 15.0), 19);
}
END_TEST

START_TEST(test_sub) {
    ck_assert_double_eq(substraction(0), 0);
    ck_assert_double_eq(substraction(1, 2.0), 2);
    ck_assert_double_eq(substraction(2, 1.0, 2.0), -1.0);
    ck_assert_double_eq(substraction(3, 1.0, 3.0, 15.0), -17);
}
END_TEST

START_TEST(test_mul) {
    ck_assert_double_eq(multiplication(0), 1);
    ck_assert_double_eq(multiplication(1, 2.0), 2);
    ck_assert_double_eq(multiplication(2, 1.0, 2.0), 2);
    ck_assert_double_eq(multiplication(3, 1.0, 3.0, 15.0), 45);
}
END_TEST

START_TEST(test_div) {
    ck_assert_double_eq(division(0), 0);
    ck_assert_double_eq(division(0, 0), 0);
    ck_assert_double_eq(division(1, 2.0), 2);
    ck_assert_double_eq(division(2, 1.0, 2.0), 0.5);
    ck_assert_double_eq(division(3, 1.0, 3.0, 15.0), 1.0/3.0/15.0);
}
END_TEST


int main(void) {
    Suite *s = suite_create("Calculator");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_sub);
    tcase_add_test(tc_core, test_mul);
    tcase_add_test(tc_core, test_div);

    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
