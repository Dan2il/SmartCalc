#include "tests.h"

#define CREATE_LIST                                                            \
  struct List list;                                                            \
  int errors = InitializationList(&list);                                      \
  ck_assert_int_eq(errors, NO_ERRORS);

#define CHECK_LEXEME(node, lex_type, operand_num, opd_type, opr_type,          \
                     pr_lvl_num)                                               \
  ck_assert_int_eq(node->lexeme.lexeme_type, lex_type);                        \
  ck_assert_double_eq(node->lexeme.operand, operand_num);                      \
  ck_assert_int_eq(node->lexeme.operand_type, opd_type);                       \
  ck_assert_int_eq(node->lexeme.oprtr, opr_type);                              \
  ck_assert_int_eq(node->lexeme.priority_level, pr_lvl_num);

START_TEST(CheckErrors_1) {
  struct List *list = NULL;
  ErrorsType errors = CheckErrors(1, CHECK_POINTER(list));
  ck_assert_int_eq(errors, NULL_POINTER);
}
END_TEST

START_TEST(CreateNode_1) {
  struct Lexeme push_lexeme = {.lexeme_type = OPERAND,
                               .operand = 234,
                               .operand_type = NUMBER,
                               .oprtr = EMPTY_OPERATOR,
                               .priority_level = 0};
  struct Node *new = CreateNode(push_lexeme, 2);
  ck_assert_ptr_nonnull(new);
  ck_assert_int_eq(new->lexeme.lexeme_type, OPERAND);
  ck_assert_double_eq(new->lexeme.operand, 234);
  ck_assert_ptr_null(new->next_node);
  ck_assert_int_eq(new->num_node, 2);
  free(new);
}
END_TEST

START_TEST(InitializationList_1) {
  CREATE_LIST

  ck_assert_ptr_nonnull(list.null_node);
  CHECK_LEXEME(list.null_node, EMPTY_LEXEME, 0, EMPTY_OPERAND, EMPTY_OPERATOR,
               0);
  ck_assert_ptr_null(list.null_node->next_node);
  ck_assert_int_eq(list.size, 0);
  free(list.null_node);
}
END_TEST

START_TEST(InitializationList_2) {
  int errors = InitializationList(NULL);
  ck_assert_int_eq(errors, NULL_POINTER);
}
END_TEST

START_TEST(PushFront_1) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};
  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 1);
  struct Node *check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = OPERAND;
  lexeme.operand = 5;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 2);
  check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 5, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_nonnull(check->next_node);
  int check_num_node = 0;
  CYCLE_FOR_LIST(list.null_node->next_node,
                 { next_node->num_node = check_num_node++; })

  check = list.null_node->next_node->next_node;

  // CHECK_LEXEME(check, OPERAND, 5, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = OPERAND;
  lexeme.operand = -45673.2;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 3);
  check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, -45673.2, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_nonnull(check->next_node);
  check_num_node = 0;
  CYCLE_FOR_LIST(list.null_node->next_node,
                 { next_node->num_node = check_num_node++; })

  FreeList(&list);
}
END_TEST

START_TEST(PushFront_2) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 1);
  struct Node *check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = EMPTY_LEXEME;
  lexeme.operand = 5;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, READ_EMPTY_LEXEME);
  ck_assert_int_eq(list.size, 1);
  check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  FreeList(&list);
}
END_TEST

START_TEST(PushBack_1) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 1);
  struct Node *check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = OPERATOR;
  lexeme.operand = 54;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 2);
  check = list.null_node->next_node;

  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_nonnull(check->next_node);

  check = list.null_node->next_node->next_node;

  // CHECK_LEXEME(list.null_node->next_node->next_node, OPERAND, 54, NUMBER,
  //              EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = OPERAND;
  lexeme.operand = 24;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 3);
  check = list.null_node->next_node;

  // CHECK_LEXEME(check, OPERAND, 24, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_nonnull(check->next_node);

  check = list.null_node->next_node->next_node->next_node;
  CHECK_LEXEME(check, OPERAND, 24, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_ptr_null(check->next_node);

  FreeList(&list);
}
END_TEST

START_TEST(PushBack_2) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(list.size, 1);
  struct Node *check = list.null_node->next_node;
  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_ptr_null(check->next_node);

  lexeme.lexeme_type = EMPTY_LEXEME;
  lexeme.operand = 5;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, READ_EMPTY_LEXEME);
  ck_assert_int_eq(list.size, 1);
  check = list.null_node->next_node;
  CHECK_LEXEME(check, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_ptr_null(check->next_node);

  FreeList(&list);
}
END_TEST

START_TEST(Front_1) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  struct Node *fr_n = FrontList(&list);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(fr_n, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_ptr_null(fr_n->next_node);

  lexeme.lexeme_type = OPERATOR;
  lexeme.operand = 0;
  lexeme.operand_type = EMPTY_OPERAND;
  lexeme.oprtr = ADDITION;
  lexeme.priority_level = 1;

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  fr_n = FrontList(&list);

  CHECK_LEXEME(fr_n, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 1);

  lexeme.lexeme_type = OPERAND;
  lexeme.operand = -45673.2;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushFrontList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  fr_n = FrontList(&list);

  CHECK_LEXEME(fr_n, OPERAND, -45673.2, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_nonnull(fr_n->next_node);
  int check_num_node = 0;
  CYCLE_FOR_LIST(fr_n->next_node, { next_node->num_node = check_num_node++; })

  FreeList(&list);
}
END_TEST

START_TEST(Front_2) {
  CREATE_LIST

  struct Node *fr_n = FrontList(&list);
  ck_assert_ptr_null(fr_n);

  FreeList(&list);
}
END_TEST

START_TEST(Back_1) {
  CREATE_LIST

  struct Lexeme lexeme = {.lexeme_type = OPERAND,
                          .operand = 234.45,
                          .operand_type = NUMBER,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  struct Node *fr_n = BackList(&list);

  CHECK_LEXEME(fr_n, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(fr_n->next_node);

  lexeme.lexeme_type = OPERATOR;
  lexeme.operand = 0;
  lexeme.operand_type = EMPTY_OPERAND;
  lexeme.oprtr = SUBSTRACTION;
  lexeme.priority_level = 1;

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  fr_n = BackList(&list);

  CHECK_LEXEME(fr_n, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 1);
  ck_assert_ptr_null(fr_n->next_node);

  lexeme.lexeme_type = OPERAND;
  lexeme.operand = 24;
  lexeme.operand_type = NUMBER;
  lexeme.oprtr = EMPTY_OPERATOR;
  lexeme.priority_level = 0;

  errors = PushBackList(&list, lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);

  fr_n = BackList(&list);

  CHECK_LEXEME(fr_n, OPERAND, 24, NUMBER, EMPTY_OPERATOR, 0);

  ck_assert_ptr_null(fr_n->next_node);

  FreeList(&list);
}
END_TEST

START_TEST(PopFront_1) {
  ErrorsType errors = NO_ERRORS;
  struct List test_l;
  errors = InitializationList(&test_l);
  ck_assert_int_eq(errors, NO_ERRORS);
  for (int counter = 0; counter < 100; counter++) {
    struct Lexeme push_l = {.lexeme_type = OPERAND,
                            .operand = counter,
                            .operand_type = NUMBER,
                            .oprtr = EMPTY_OPERATOR,
                            .priority_level = 0};
    PushBackList(&test_l, push_l);
  }
  struct Node *node = test_l.null_node;
  for (int counter = 0; counter < 100; counter++) {
    node = node->next_node;
    ck_assert_int_eq(node->lexeme.operand, counter);
    ck_assert_int_eq(node->num_node, counter + 1);
  }
  int size_list = 100;
  for (int counter = 1; counter < 100; counter++) {
    ck_assert_int_eq(test_l.size, size_list--);
    PopFrontList(&test_l);
    node = FrontList(&test_l);
    ck_assert_int_eq(node->lexeme.operand, counter);
    ck_assert_int_eq(node->num_node, 1);
  }
  FreeList(&test_l);
}
END_TEST

START_TEST(PopBack_1) {
  ErrorsType errors = NO_ERRORS;
  struct List test_l;
  errors = InitializationList(&test_l);
  ck_assert_int_eq(errors, NO_ERRORS);
  for (int counter = 0; counter < 100; counter++) {
    struct Lexeme push_l = {.lexeme_type = OPERAND,
                            .operand = counter,
                            .operand_type = NUMBER,
                            .oprtr = EMPTY_OPERATOR,
                            .priority_level = 0};
    PushBackList(&test_l, push_l);
  }
  struct Node *node = test_l.null_node;
  for (int counter = 0; counter < 100; counter++) {
    node = node->next_node;
    ck_assert_int_eq(node->lexeme.operand, counter);
    ck_assert_int_eq(node->num_node, counter + 1);
  }

  for (int counter = 99; counter > -1; counter--) {
    ck_assert_int_eq(test_l.size, counter + 1);
    node = BackList(&test_l);
    ck_assert_int_eq(node->lexeme.operand, counter);
    ck_assert_int_eq(node->num_node, counter + 1);
    PopBackList(&test_l);
  }
  FreeList(&test_l);
}
END_TEST

START_TEST(Empty_1) {
  ErrorsType errors = NO_ERRORS;
  struct List test_l;
  errors = InitializationList(&test_l);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(EmptyList(&test_l), true);
  for (int counter = 0; counter < 100; counter++) {
    struct Lexeme push_l = {.lexeme_type = OPERAND,
                            .operand = counter,
                            .operand_type = NUMBER,
                            .oprtr = EMPTY_OPERATOR,
                            .priority_level = 0};
    PushBackList(&test_l, push_l);
  }
  ck_assert_int_eq(EmptyList(&test_l), false);
  FreeList(&test_l);
}
END_TEST

START_TEST(AtList_1) {
  ErrorsType errors = NO_ERRORS;
  struct List *test_l = CreateList(&errors);
  ck_assert_int_eq(errors, NO_ERRORS);

  for (int counter = 0; counter < 100; counter++) {
    struct Lexeme push_l = {.lexeme_type = OPERAND,
                            .operand = counter,
                            .operand_type = NUMBER,
                            .oprtr = EMPTY_OPERATOR,
                            .priority_level = 0};
    PushBackList(test_l, push_l);
  }
  struct Node *node_cycle = test_l->null_node;
  for (int counter = 0; counter < 100;) {
    node_cycle = node_cycle->next_node;
    ck_assert_ptr_nonnull(node_cycle);
    ck_assert_int_eq(node_cycle->lexeme.operand, counter);
    counter++;
    ck_assert_int_eq(node_cycle->num_node, counter);
  }
  node_cycle = test_l->null_node;
  struct Node *node_test_at = test_l->null_node;

  for (int counter = 0; counter < 100; counter++) {
    node_cycle = node_cycle->next_node;
    node_test_at = AtList(test_l, counter + 1);
    ck_assert_int_eq(node_cycle->lexeme.operand, counter);
    ck_assert_int_eq(node_cycle->num_node, counter + 1);

    ck_assert_int_eq(node_test_at->lexeme.operand, counter);
    ck_assert_int_eq(node_test_at->num_node, counter + 1);

    ck_assert_ptr_eq(node_cycle, node_test_at);
  }

  FreeList(test_l);
  free(test_l);
}
END_TEST

void StartTestsList() {
  Suite *suite = suite_create("Tests_List");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, CheckErrors_1);

  tcase_add_test(getCase, CreateNode_1);

  tcase_add_test(getCase, InitializationList_1);
  tcase_add_test(getCase, InitializationList_2);

  tcase_add_test(getCase, PushFront_1);
  tcase_add_test(getCase, PushFront_2);

  tcase_add_test(getCase, PushBack_1);
  tcase_add_test(getCase, PushBack_2);

  tcase_add_test(getCase, Front_1);
  tcase_add_test(getCase, Front_2);

  tcase_add_test(getCase, Back_1);

  tcase_add_test(getCase, PopFront_1);

  tcase_add_test(getCase, PopBack_1);

  tcase_add_test(getCase, Empty_1);

  tcase_add_test(getCase, AtList_1);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}
