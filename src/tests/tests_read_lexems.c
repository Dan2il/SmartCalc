#include "tests.h"

#define CHECK_LEXEME(lex_check, lex_type, oprd_n, oprd_type, opr, pr_lvl)      \
  ck_assert_int_eq(lex_check.lexeme_type, lex_type);                           \
  ck_assert_double_eq(lex_check.operand, oprd_n);                              \
  ck_assert_int_eq(lex_check.operand_type, oprd_type);                         \
  ck_assert_int_eq(lex_check.oprtr, opr);                                      \
  ck_assert_int_eq(lex_check.priority_level, pr_lvl);

START_TEST(CheckLexeme_1) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 0;
  LexemeType lexeme_type = CheckLexeme(expression, index);
  ck_assert_int_eq(lexeme_type, OPERAND);
}
END_TEST

START_TEST(CheckLexeme_2) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 1;
  LexemeType lexeme_type = CheckLexeme(expression, index);
  ck_assert_int_eq(lexeme_type, OPERATOR);
}
END_TEST

START_TEST(CheckLexeme_3) {
  char *expression = "2*2moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 3;
  LexemeType lexeme_type = CheckLexeme(expression, index);
  ck_assert_int_eq(lexeme_type, OPERATOR);
}
END_TEST

START_TEST(CheckLexeme_4) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 17;
  LexemeType lexeme_type = CheckLexeme(expression, index);
  ck_assert_int_eq(lexeme_type, OPERATOR);
}
END_TEST

START_TEST(CheckLexeme_5) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 30;
  LexemeType lexeme_type = CheckLexeme(expression, index);
  ck_assert_int_eq(lexeme_type, OPERAND);
}
END_TEST

START_TEST(ProcessReadLexeme_1) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 1;
  LexemeType lexeme_type = OPERATOR;
  struct Lexeme lexeme = ProcessReadLexeme(expression, &index, lexeme_type);
  ck_assert_int_eq(lexeme.lexeme_type, OPERATOR);
  ck_assert_int_eq(lexeme.operand, 0);
  ck_assert_int_eq(lexeme.operand_type, EMPTY_OPERAND);
  ck_assert_int_eq(lexeme.oprtr, MULTIPLICATION);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ProcessReadLexeme_2) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 17;
  LexemeType lexeme_type = OPERATOR;
  struct Lexeme lexeme = ProcessReadLexeme(expression, &index, lexeme_type);
  ck_assert_int_eq(lexeme.lexeme_type, OPERATOR);
  ck_assert_int_eq(lexeme.operand, 0);
  ck_assert_int_eq(lexeme.operand_type, EMPTY_OPERAND);
  ck_assert_int_eq(lexeme.oprtr, MULTIPLICATION);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ProcessReadLexeme_3) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 27;
  LexemeType lexeme_type = OPERATOR;
  struct Lexeme lexeme = ProcessReadLexeme(expression, &index, lexeme_type);
  ck_assert_int_eq(lexeme.lexeme_type, OPERATOR);
  ck_assert_int_eq(lexeme.operand, 0);
  ck_assert_int_eq(lexeme.operand_type, EMPTY_OPERAND);
  ck_assert_int_eq(lexeme.oprtr, END_BRACKETS);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ProcessReadLexeme_4) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 2;
  LexemeType lexeme_type = OPERATOR;
  struct Lexeme lexeme = ProcessReadLexeme(expression, &index, lexeme_type);
  ck_assert_int_eq(lexeme.lexeme_type, OPERATOR);
  ck_assert_int_eq(lexeme.operand, 0);
  ck_assert_int_eq(lexeme.operand_type, EMPTY_OPERAND);
  ck_assert_int_eq(lexeme.oprtr, MODULUS);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ProcessReadLexeme_5) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+56.5)";
  int index = 28;
  LexemeType lexeme_type = OPERATOR;
  struct Lexeme lexeme = ProcessReadLexeme(expression, &index, lexeme_type);
  ck_assert_int_eq(lexeme.lexeme_type, OPERATOR);
  ck_assert_int_eq(lexeme.operand, 0);
  ck_assert_int_eq(lexeme.operand_type, EMPTY_OPERAND);
  ck_assert_int_eq(lexeme.oprtr, DIVISION);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ReadNumOperand_1) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+.567)";
  int index = 0;
  struct Lexeme lexeme = ReadNumOperand(expression, &index);
  ck_assert_int_eq(lexeme.lexeme_type, OPERAND);
  ck_assert_int_eq(lexeme.operand, 2);
  ck_assert_int_eq(lexeme.operand_type, NUMBER);
  ck_assert_int_eq(lexeme.oprtr, EMPTY_OPERATOR);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ReadNumOperand_2) {
  char *expression = "2*moda-((xy*0,245*678.43534)/mod+.567)";
  int index = 12;
  struct Lexeme lexeme = ReadNumOperand(expression, &index);
  ck_assert_int_eq(lexeme.lexeme_type, OPERAND);
  ck_assert_double_eq(lexeme.operand, 0.245);
  ck_assert_int_eq(lexeme.operand_type, NUMBER);
  ck_assert_int_eq(lexeme.oprtr, EMPTY_OPERATOR);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ReadNumOperand_3) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+.567)";
  int index = 18;
  struct Lexeme lexeme = ReadNumOperand(expression, &index);
  ck_assert_int_eq(lexeme.lexeme_type, OPERAND);
  ck_assert_double_eq(lexeme.operand, 678.43534);
  ck_assert_int_eq(lexeme.operand_type, NUMBER);
  ck_assert_int_eq(lexeme.oprtr, EMPTY_OPERATOR);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ReadNumOperand_4) {
  char *expression = "2*moda-((xy*0.245*678.43534)/mod+.567)";
  int index = 33;
  struct Lexeme lexeme = ReadNumOperand(expression, &index);
  ck_assert_int_eq(lexeme.lexeme_type, OPERAND);
  ck_assert_double_eq(lexeme.operand, 0.567);
  ck_assert_int_eq(lexeme.operand_type, NUMBER);
  ck_assert_int_eq(lexeme.oprtr, EMPTY_OPERATOR);
  ck_assert_int_eq(lexeme.priority_level, 0);
}
END_TEST

START_TEST(ReadLexeme_1) {
  char *expression = "2*2moda-((xy*0.245*678.43534)/mod+.567)+234,45^m";
  int index = 0;
  struct Lexeme lexeme;
  ErrorsType errors = NO_ERRORS;
  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 1);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);
  ck_assert_int_eq(index, 2);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 3);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, MODULUS, 0);
  ck_assert_int_eq(index, 6);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 97, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 7);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);
  ck_assert_int_eq(index, 8);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);
  ck_assert_int_eq(index, 9);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, STARTS_BRACKETS, 0);
  ck_assert_int_eq(index, 10);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 120, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 11);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 121, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 12);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);
  ck_assert_int_eq(index, 13);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 0.245, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 18);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);
  ck_assert_int_eq(index, 19);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 678.43534, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 28);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);
  ck_assert_int_eq(index, 29);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);
  ck_assert_int_eq(index, 30);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 109, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 31);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 111, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 32);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 100, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 33);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  ck_assert_int_eq(index, 34);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 0.567, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 38);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, END_BRACKETS, 0);
  ck_assert_int_eq(index, 39);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  ck_assert_int_eq(index, 40);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 234.45, NUMBER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 46);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERATOR, 0, EMPTY_OPERAND, POWER, 0);
  ck_assert_int_eq(index, 47);

  errors = ReadLexeme(expression, &index, &lexeme);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(lexeme, OPERAND, 109, LETTER, EMPTY_OPERATOR, 0);
  ck_assert_int_eq(index, 48);
}

START_TEST(CheckUnOperator_1) {
  char *test = "-2+-2*2-(+5-6)+(5+6)";
  bool result = false;

  result = CheckUnOperator(test, 0);
  ck_assert_int_eq(result, true);

  result = CheckUnOperator(test, 2);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 3);
  ck_assert_int_eq(result, true);

  result = CheckUnOperator(test, 5);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 7);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 9);
  ck_assert_int_eq(result, true);

  result = CheckUnOperator(test, 11);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 14);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 17);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 19);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 20);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(CheckUnOperator_2) {
  char *test = "5*(-3+8)";
  bool result = false;

  result = CheckUnOperator(test, 0);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 1);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 2);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 3);
  ck_assert_int_eq(result, true);

  result = CheckUnOperator(test, 4);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 5);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 6);
  ck_assert_int_eq(result, false);

  result = CheckUnOperator(test, 7);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(CheckStrNCmp_1) {
  char *expression = "sin(25)";
  char *func = "sin";
  bool result = CheckStrNCmp(&expression[0], func, 3);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(CheckStrNCmp_2) {
  char *expression = "x(25)";
  char *func = "sin";
  bool result = CheckStrNCmp(&expression[0], func, 3);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(CheckStrNCmp_3) {
  char *expression = "x(25)+cos(24)-atan(2)";
  bool result = CheckStrNCmp(&expression[0], "sin", 3);
  ck_assert_int_eq(result, false);

  result = CheckStrNCmp(&expression[6], "cos", 3);
  ck_assert_int_eq(result, true);

  result = CheckStrNCmp(&expression[6], "cas", 3);
  ck_assert_int_eq(result, false);

  result = CheckStrNCmp(&expression[14], "atan", 4);
  ck_assert_int_eq(result, true);
}

START_TEST(CheckFunctionOperator_1) {
  char *expression =
      "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*atan(444)/ln(log(555))";

  bool result = CheckFunctionOperator(expression, 0);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 3);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 4);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 8);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 12);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 13);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 14);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 18);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 24);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 30);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 35);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 46);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 51);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 55);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 58);
  ck_assert_int_eq(result, true);

  result = CheckFunctionOperator(expression, 63);
  ck_assert_int_eq(result, false);

  result = CheckFunctionOperator(expression, 66);
  ck_assert_int_eq(result, false);
}
END_TEST

void StartTestsReadLexemes() {
  Suite *suite = suite_create("TestsReadLexems");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, CheckLexeme_1);
  tcase_add_test(getCase, CheckLexeme_2);
  tcase_add_test(getCase, CheckLexeme_3);
  tcase_add_test(getCase, CheckLexeme_4);
  tcase_add_test(getCase, CheckLexeme_5);

  tcase_add_test(getCase, ProcessReadLexeme_1);
  tcase_add_test(getCase, ProcessReadLexeme_2);
  tcase_add_test(getCase, ProcessReadLexeme_3);
  tcase_add_test(getCase, ProcessReadLexeme_4);
  tcase_add_test(getCase, ProcessReadLexeme_5);

  tcase_add_test(getCase, ReadNumOperand_1);
  tcase_add_test(getCase, ReadNumOperand_2);
  tcase_add_test(getCase, ReadNumOperand_3);
  tcase_add_test(getCase, ReadNumOperand_4);

  tcase_add_test(getCase, ReadLexeme_1);

  tcase_add_test(getCase, CheckUnOperator_1);
  tcase_add_test(getCase, CheckUnOperator_2);

  tcase_add_test(getCase, CheckStrNCmp_1);
  tcase_add_test(getCase, CheckStrNCmp_2);
  tcase_add_test(getCase, CheckStrNCmp_3);

  tcase_add_test(getCase, CheckFunctionOperator_1);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}