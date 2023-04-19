/*!
 * \file sort_station.h
 */
#ifndef SORT_STATION_EXPRESSION_H
#define SORT_STATION_EXPRESSION_H

#include "../expression/expression.h"
#include "../processing_errors/processing_errors.h"

typedef enum { EMPTY_LVL, LOW, AVERAGE, HIGH } PriorityLvl;

typedef enum { ERROR_COMP, EQUALLY, LESS, GREATER } Comprassion;

struct ConvertStation {
  struct Expression *for_convert;
  struct Expression *result;

  struct List *stack_operators;

  struct Node *handler_token;

  ErrorsType errors;
};

/*!
 * \brief InitializationConverter Инициализирует структуру ConvertStation
 */
ErrorsType InitializationConverter(struct ConvertStation *for_init,
                                   struct Expression *for_conversion,
                                   struct Expression *for_result);
/*!
 * \brief InfixToReversePolish Конвертирует инфиксное выражение в обратную
 * польскую нотацию
 */
ErrorsType InfixToReversePolish(struct ConvertStation *converter);

ErrorsType Handlerlexeme(struct ConvertStation *converter);
ErrorsType HandlerOperand(struct List *for_write_result, struct Lexeme *lexeme);
ErrorsType HandlerOperator(struct ConvertStation *converter);
ErrorsType HandlerOperatorBrackets(struct ConvertStation *converter);
ErrorsType HandlerComprassionOperators(struct ConvertStation *converter);

PriorityLvl GetPriorityLvl(struct Lexeme *lex);
bool CheckBrackets(struct Lexeme *lexeme);
bool CheckFunctions(struct Lexeme *lexeme);
ErrorsType CheckCorrectBrackets(struct Expression *for_conversion);

#endif  // SORT_STATION_EXPRESSION_H
