/*!
 * \file read_lexems.h
 */
#ifndef EXPRESSION_READ_LEXEMS_H
#define EXPRESSION_READ_LEXEMS_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../allocate_memory/allocate_memory.h"
#include "../processing_errors/processing_errors.h"
#include "structures.h"

#define MAX_SIZE_EXPRESSION 256

#define ASCII_NUM_START 48
#define ASCII_NUM_FINISH 57

#define ASCII_LETTER_START 97
#define ASCII_LETTER_FINISH 122

/*!
 * \brief ProcessReadLexeme Проверяет данные и обрабатывает их в функции
 * ProcessReadLexeme
 */

ErrorsType ReadLexeme(char *expression, int *index_symbol,
                      struct Lexeme *result);

/*!
 * \brief ProcessReadLexeme Читает символ из expression с индексом index_symbol
 * и обрабатывает в соответствии с lexeme_type, записывая в лексему
 */
struct Lexeme ProcessReadLexeme(char *expression, int *index_symbol,
                                LexemeType lexeme_type);
/*!
 * \brief CheckLexeme Проверяет тип лексемы
 */
LexemeType CheckLexeme(char *expression, int index_symbol);

bool CheckOperator(char *expression, int index_symbol);
bool CheckSymbolsOperators(char symbol);
bool CheckFunctionOperator(char *expression, int index_symbol);
bool CheckModOperator(char *expression, int index_symbol);
bool CheckOperand(char *expression, int index_symbol);
bool CheckUnOperator(char *expression, int index_symbol);

/*!
 * \brief GetEmptyLexeme Создает пустую лексему
 */
struct Lexeme GetEmptyLexeme();

/*!
 * \brief InitializationLexeme Записывает в лексему указанные в аргументах
 * данные
 */
struct Lexeme InitializationLexeme(LexemeType lexeme_type, double operand,
                                   Operands operand_type,
                                   Operators operator_type, int priority_level);

struct Lexeme ReadOperand(char *expresion, int *index_symbol);
struct Lexeme ReadOperator(char *expression, int *index_symbol);
struct Lexeme ReadNumOperand(char *expresion, int *index_symbol);
Operators ReadFunctionsOperators(char *expression, int *index_symbol);

void CheckDotInExpression(char *expresion, int *index_symbol, char *result);
void GetStringNumInExpression(char *expresion, int *index_symbol, char *result);
double StringToDouble(char *for_convert);
void WriteUnOperator(char *expression, int index_symbol, struct Lexeme *lexeme);

bool CheckFunctionOperator(char *expression, int index_symbol);
bool CheckStrNCmp(char *expression, const char *func, int length);

#endif  // EXPRESSION_READ_LEXEMS_H
