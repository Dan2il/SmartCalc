/*!
 * \file processing_errors.h
 */
#ifndef PROCESSING_ERRORS_PROCESSING_ERRORS_H_
#define PROCESSING_ERRORS_PROCESSING_ERRORS_H_

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRORS_NOT_FOUND(errors) errors == NO_ERRORS

#define CHECK_POINTER(pointer) CheckPointer(pointer)
#define CHECK_NEGATIVE(num) CheckNegativeNumber(num)
#define CHECK_NULL_NUMBER(num) CheckNullNumber(num)

typedef enum {
  NO_ERRORS,
  NULL_POINTER,
  READ_EMPTY_LEXEME,
  READ_INCORRECT_SYMBOL,
  INCORRECT_DATA,
  NEGATIVE_NUMBER,
  NULL_NUMBER,
  EMPTY_EXPRESSION,
  LONG_EXPRESSION,
  READ_EOF,
  COMPRASSION_ERROR,
  NOT_REVERSE_POLISH
} ErrorsType;

/*!
 * \brief CheckErrors Функция с переменным количеством аргументов. Первым
 * аргументов (num_check), указывается количество последующих проверок. Далее,
 * их результат сравнивается с NO_ERRORS
 */
ErrorsType CheckErrors(int num_check, ...);

ErrorsType CheckPointer(void *pointer);
ErrorsType CheckNegativeNumber(double num);
ErrorsType CheckNullNumber(double num);

void PrintErrors(ErrorsType errors);
void GetTextErrors(ErrorsType errors, char *text_errors);

#endif  // PROCESSING_ERRORS_PROCESSING_ERRORS_H_
