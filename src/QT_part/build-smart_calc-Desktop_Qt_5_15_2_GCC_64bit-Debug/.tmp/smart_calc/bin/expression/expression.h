/*!
 * \file expression.h
 */
#ifndef EXPRESSION_EXPRESSION_H
#define EXPRESSION_EXPRESSION_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// #include "../../read_expression.h"
#include "../allocate_memory/allocate_memory.h"
#include "../processing_errors/processing_errors.h"
#include "read_lexems.h"
#include "structures.h"

/*!
 * \brief InitializationExpression Инициализирует структуру Expression
 */
ErrorsType InitializationExpression(struct Expression *expression,
                                    char *string_representation_expression,
                                    TypeNotation type_notation);

ErrorsType ReadStringExpression(struct Expression *expression);
ErrorsType ReadStringExpressionToClassinNotation(struct Expression *expression);

#endif  // EXPRESSION_EXPRESSION_H
