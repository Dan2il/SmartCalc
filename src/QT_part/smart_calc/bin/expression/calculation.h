/*!
 * \file calculation.h
 */
#ifndef EXPRESSION_CALCULATION_H
#define EXPRESSION_CALCULATION_H

#include <math.h>

#include "structures.h"

/*!
 * \brief HandlerCalculation Вычисление выражения
 */
ErrorsType HandlerCalculation(struct List *expression, double *result);

/*!
 * \brief HandlerCalculationWhithX Вычисление выражения с х-параметром
 */
ErrorsType HandlerCalculationWhithX(struct List *expression, double *result,
                                    double variable_x);

ErrorsType CalculationOperator(struct List *stack_number, struct Node *oprtr);
ErrorsType CalculationPowerOperator(struct List *stack_number);
void CalculationUnOperator(struct Node *front_stack_number,
                           struct Node *un_operator);
ErrorsType CalculationOtherOperator(struct List *stack_number,
                                    struct Node *oprtr);

#endif
