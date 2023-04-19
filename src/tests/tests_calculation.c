#include "tests.h"

#define INCCURACY 0.0000001

START_TEST(HandlerCalculation_1) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 4);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_2) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(1+2)*4";
  char *empty = " ";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, empty, EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 12);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}

START_TEST(HandlerCalculation_3) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 15);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_4) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 15);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_5) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 3.5);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_6) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 15.5);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_7) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq(check, 25);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_8) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, -30.0721649485, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_9) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, -568.5111111, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_10) {
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 0, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_11) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2/1+2+3+4*5*6^7-727/728+((1000+500*2)*201)+sin(1)";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 6000726.018826, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_12) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "-((611*233)+8+800*2-(2-2*(4*6*245-(4+8231)))*1033)";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 4723525.000000, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_13) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(611*233)+8+800*2+(2+2*(4*6*5*(4+8231)))-100";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 2120273.000000, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}

START_TEST(HandlerCalculation_14) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "-(-(-4,4-1,1))";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, -5.5, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_15) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "9mod2";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 1, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_16) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(6^2)/8";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 4.5, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_17) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "cos(sin(log(1)))";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 1, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_18) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "6^2^3*1-6^2^3";
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

  double check = 0;
  errors = HandlerCalculation(result.lexems, &check);
  ck_assert_double_eq_tol(check, 0, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_19) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "sin";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 2);
  ck_assert_int_eq(errors, INCORRECT_DATA);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculation_20) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "2.3+2.4";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 2);
  ck_assert_double_eq_tol(check, 4.7, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_1) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "sin(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 25);
  ck_assert_double_eq_tol(check, 0.42261826174, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_2) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "cos(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 53.5);
  ck_assert_double_eq_tol(check, 0.59482278675, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_3) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "tan(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, -56);
  ck_assert_double_eq_tol(check, -1.48256096851, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_4) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "acos(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, -0.45);
  ck_assert_double_eq_tol(check, 116.74368395, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_5) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "asin(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 0.25);
  ck_assert_double_eq_tol(check, 14.4775121859, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_6) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "asin(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 256);
  ck_assert_double_eq_tol(check, 0, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_7) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "atan(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 256);
  ck_assert_double_eq_tol(check, 89.7761894996, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_8) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "sqrt(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 256.025);
  ck_assert_double_eq_tol(check, 16.0007812309, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_9) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "ln(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 56);
  ck_assert_double_eq_tol(check, 4.02535169074, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_10) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "log(x)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 785263);
  ck_assert_double_eq_tol(check, 5.89501513486, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_11) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test =
      "cos(0,25)+sin(0,25)+tan(0,25)+acos(0,25)+asin(0,25)+atan(0,25)+sqrt(0,"
      "25)+ln(0,25)+log(0,25)";
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

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 785263);
  ck_assert_double_eq_tol(check, 103.556606256, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

START_TEST(HandlerCalculationWhithX_12) {
  ErrorsType errors = NO_ERRORS;
  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  char *test = "(x+x)+x-x*x/x^x";
  TypeNotation type_notation = CLASSIC;
  errors = InitializationExpression(&expression, test, type_notation);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = ReadStringExpression(&expression);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationExpression(&result, "0", EMPTY);
  ck_assert_int_eq(errors, NO_ERRORS);
  errors = InitializationConverter(&converter, &expression, &result);
  ck_assert_int_eq(errors, NO_ERRORS);

  errors = InfixToReversePolish(&converter);
  ck_assert_int_eq(errors, NO_ERRORS);

  double check = 0;
  errors = HandlerCalculationWhithX(result.lexems, &check, 2);
  ck_assert_double_eq_tol(check, 5, INCCURACY);

  FreeList(expression.lexems);
  free(expression.lexems);

  FreeList(result.lexems);
  free(result.lexems);
}
END_TEST

void StartTestsCalculation() {
  Suite *suite = suite_create("TestsCalculation");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, HandlerCalculation_1);
  tcase_add_test(getCase, HandlerCalculation_2);
  tcase_add_test(getCase, HandlerCalculation_3);
  tcase_add_test(getCase, HandlerCalculation_4);
  tcase_add_test(getCase, HandlerCalculation_5);
  tcase_add_test(getCase, HandlerCalculation_6);
  tcase_add_test(getCase, HandlerCalculation_7);
  tcase_add_test(getCase, HandlerCalculation_8);
  tcase_add_test(getCase, HandlerCalculation_9);
  tcase_add_test(getCase, HandlerCalculation_10);
  tcase_add_test(getCase, HandlerCalculation_11);
  tcase_add_test(getCase, HandlerCalculation_12);
  tcase_add_test(getCase, HandlerCalculation_13);
  tcase_add_test(getCase, HandlerCalculation_14);
  tcase_add_test(getCase, HandlerCalculation_15);
  tcase_add_test(getCase, HandlerCalculation_16);
  tcase_add_test(getCase, HandlerCalculation_17);
  tcase_add_test(getCase, HandlerCalculation_18);
  tcase_add_test(getCase, HandlerCalculation_19);
  tcase_add_test(getCase, HandlerCalculation_20);

  tcase_add_test(getCase, HandlerCalculationWhithX_1);
  tcase_add_test(getCase, HandlerCalculationWhithX_2);
  tcase_add_test(getCase, HandlerCalculationWhithX_3);
  tcase_add_test(getCase, HandlerCalculationWhithX_4);
  tcase_add_test(getCase, HandlerCalculationWhithX_5);
  tcase_add_test(getCase, HandlerCalculationWhithX_6);
  tcase_add_test(getCase, HandlerCalculationWhithX_7);
  tcase_add_test(getCase, HandlerCalculationWhithX_8);
  tcase_add_test(getCase, HandlerCalculationWhithX_9);
  tcase_add_test(getCase, HandlerCalculationWhithX_10);
  tcase_add_test(getCase, HandlerCalculationWhithX_11);
  tcase_add_test(getCase, HandlerCalculationWhithX_12);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}