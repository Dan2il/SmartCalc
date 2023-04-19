#include "tests.h"

#define CHECK_LEXEME(lex_check, lex_type, oprd_n, oprd_type, opr, pr_lvl)      \
  ck_assert_int_eq(lex_check.lexeme_type, lex_type);                           \
  ck_assert_double_eq(lex_check.operand, oprd_n);                              \
  ck_assert_int_eq(lex_check.operand_type, oprd_type);                         \
  ck_assert_int_eq(lex_check.oprtr, opr);                                      \
  ck_assert_int_eq(lex_check.priority_level, pr_lvl);

START_TEST(InitializationExpression_1) {
  struct Expression exp;
  char *test = "2*2moda-((xy*0.245*678.43534)/mod+.567)+234,45^m";
  ErrorsType errors = InitializationExpression(&exp, test, CLASSIC);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_int_eq(0, exp.status_write_lexems);
  ck_assert_int_eq(CLASSIC, exp.type_string);
  FreeList(exp.lexems);
  free(exp.lexems);
}
END_TEST

START_TEST(ReadStringExpression_1) {
  struct Expression exp;
  char *test = "2*2moda-((xy*0.245*678.43534)/mod+.567)+234,45^m";
  TypeNotation type_notation = CLASSIC;
  ErrorsType errors = InitializationExpression(&exp, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&exp);

  struct Node *node = FrontList(exp.lexems);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MODULUS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 97, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 120, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 121, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 0.245, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 678.43534, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 109, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 111, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 100, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 0.567, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, POWER, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 109, LETTER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_null(node);

  FreeList(exp.lexems);
  free(exp.lexems);
}
END_TEST

START_TEST(ReadStringExpression_2) {
  struct Expression exp;
  char *test =
      "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*atan(444)/ln(log(555))";
  TypeNotation type_notation = CLASSIC;
  ErrorsType errors = InitializationExpression(&exp, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&exp);

  struct Node *node = FrontList(exp.lexems);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SIN, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, COS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 111, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, TAN, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SQRT, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 222, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ACOS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ASIN, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 333, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ATAN, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 444, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, LN, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, LOG, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERAND, 555, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);

  node = node->next_node;
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);
  FreeList(exp.lexems);
  free(exp.lexems);
}
END_TEST

void StartTestsExpression() {
  Suite *suite = suite_create("TestsExpression");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, InitializationExpression_1);

  tcase_add_test(getCase, ReadStringExpression_1);
  tcase_add_test(getCase, ReadStringExpression_2);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}