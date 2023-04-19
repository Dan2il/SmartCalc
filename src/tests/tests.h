#ifndef TESTS_TESTS_H
#define TESTS_TESTS_H

#include <check.h>

#include "../QT_part/smart_calc/bin/allocate_memory/allocate_memory.h"
#include "../QT_part/smart_calc/bin/credit_calculator/credit_calculator.h"
#include "../QT_part/smart_calc/bin/deposit_calculator/deposit_calculator.h"
#include "../QT_part/smart_calc/bin/expression/calculation.h"
#include "../QT_part/smart_calc/bin/expression/expression.h"
#include "../QT_part/smart_calc/bin/list/list.h"
#include "../QT_part/smart_calc/bin/sort_station/sort_station.h"
// #include "../read_expression.h"

void StartTestsList();
void StartTestsAllocateMemory();
void StartTestsReadLexemes();
void StartTestsExpression();
void StartTestsSortStation();
void StartTestsCalculation();
void StartTestsCreditCalculator();
void StartTestsDepositCalculator();

#endif // TESTS_TESTS_H