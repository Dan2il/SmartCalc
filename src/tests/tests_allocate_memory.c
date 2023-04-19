#include "tests.h"

START_TEST(GetMemory_1) {
  ErrorsType errors = NO_ERRORS;
  char *test = GetMemory(&errors, 64, sizeof(char));
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_ptr_nonnull(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
  free(test);
}
END_TEST

START_TEST(GetMemory_2) {
  ErrorsType errors = NO_ERRORS;
  int *test = GetMemory(&errors, 64, sizeof(int));
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_ptr_nonnull(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
  free(test);
}
END_TEST

START_TEST(GetMemory_3) {
  ErrorsType errors = NO_ERRORS;
  struct Node *test = GetMemory(&errors, 32, sizeof(struct Node));
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_ptr_nonnull(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
  free(test);
}
END_TEST

START_TEST(GetMemory_4) {
  struct Node *test = GetMemory(NULL, 32, sizeof(struct Node));
  ck_assert_ptr_null(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
}
END_TEST

START_TEST(GetMemory_5) {
  ErrorsType errors = NO_ERRORS;
  struct Node *test = GetMemory(&errors, 0, sizeof(struct Node));
  ck_assert_int_eq(errors, NULL_NUMBER);
  ck_assert_ptr_null(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
}
END_TEST

START_TEST(GetMemory_6) {
  ErrorsType errors = NO_ERRORS;
  struct Node *test = GetMemory(&errors, -134532, sizeof(struct Node));
  ck_assert_int_eq(errors, NEGATIVE_NUMBER);
  ck_assert_ptr_null(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
}
END_TEST

START_TEST(GetMemory_7) {
  ErrorsType errors = NO_ERRORS;
  struct Node *test = GetMemory(&errors, 23523, -5);
  ck_assert_int_eq(errors, NEGATIVE_NUMBER);
  ck_assert_ptr_null(test);
  // ck_assert_int_eq(64 + 8, malloc_usable_size(test));
}
END_TEST

void StartTestsAllocateMemory() {
  Suite *suite = suite_create("TestsAllocateMemory");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, GetMemory_1);
  tcase_add_test(getCase, GetMemory_2);
  tcase_add_test(getCase, GetMemory_3);
  tcase_add_test(getCase, GetMemory_4);
  tcase_add_test(getCase, GetMemory_5);
  tcase_add_test(getCase, GetMemory_6);
  tcase_add_test(getCase, GetMemory_7);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}