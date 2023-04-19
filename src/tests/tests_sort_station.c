#include "tests.h"

// 2*2moda-((x*y*0.245*678.43534)/m*o*d+.567)+234,45^m

#define CHECK_LEXEME(lex_check, lex_type, oprd_n, oprd_type, opr, pr_lvl)      \
  ck_assert_int_eq(lex_check.lexeme_type, lex_type);                           \
  ck_assert_double_eq(lex_check.operand, oprd_n);                              \
  ck_assert_int_eq(lex_check.operand_type, oprd_type);                         \
  ck_assert_int_eq(lex_check.oprtr, opr);                                      \
  ck_assert_int_eq(lex_check.priority_level, pr_lvl);

START_TEST(SortStation_1) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2+2";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 3);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_ptr_null(node);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_2) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2*2";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 3);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_ptr_null(node);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_3) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2mod2";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 3);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MODULUS, 0);

  node = node->next_node;
  ck_assert_ptr_null(node);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_4) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(1+2)*4";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 5);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERAND, 4, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_ptr_nonnull(node);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}

START_TEST(SortStation_5) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(1+2)*4+3";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 7);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 4, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_6) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "((1+2)*4)+3";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 7);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 4, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_7) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "3+4*2/(1-5)^2";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 11);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 4, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 5, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, POWER, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_8) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2+3*(8-7/2)";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 9);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 8, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 7, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_9) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "5*(-3+8)";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);

  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 6);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 5, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_MINUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 8, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}

START_TEST(SortStation_10) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
               "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);

  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 63);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 15, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 7, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 15, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 7, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 200, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 15, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 7, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 15, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 7, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 3, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 1, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_11) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "-456-(-2*-56)+(+(-23)/45)";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);

  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 14);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 456, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_MINUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 2, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_MINUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 56, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_MINUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 23, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_MINUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, UNARY_PLUS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 45, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(SortStation_12) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test =
      "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*atan(444)/ln(log(555))";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);

  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_int_eq(converter.result->lexems->size, 18);

  struct Node *node = FrontList(converter.result->lexems);
  ck_assert_ptr_nonnull(node);

  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 111, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, COS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SIN, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 222, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SQRT, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, TAN, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ADDITION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 333, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ASIN, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ACOS, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 444, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, ATAN, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, MULTIPLICATION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERAND, 555, NUMBER, EMPTY_OPERATOR, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, LOG, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, LN, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, DIVISION, 0);

  node = node->next_node;
  ck_assert_int_eq(errors, NO_ERRORS);
  CHECK_LEXEME(node->lexeme, OPERATOR, 0, EMPTY_OPERAND, SUBSTRACTION, 0);
  FreeList(expression.lexems);
  FreeList(result.lexems);
  free(expression.lexems);
  free(result.lexems);
}
END_TEST

void StartTestsSortStation() {
  Suite *suite = suite_create("Tests_Sort_Station");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, SortStation_1);
  tcase_add_test(getCase, SortStation_2);
  tcase_add_test(getCase, SortStation_3);
  tcase_add_test(getCase, SortStation_4);
  tcase_add_test(getCase, SortStation_5);
  tcase_add_test(getCase, SortStation_6);
  tcase_add_test(getCase, SortStation_7);
  tcase_add_test(getCase, SortStation_8);
  tcase_add_test(getCase, SortStation_9);
  tcase_add_test(getCase, SortStation_10);
  tcase_add_test(getCase, SortStation_11);
  tcase_add_test(getCase, SortStation_12);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}