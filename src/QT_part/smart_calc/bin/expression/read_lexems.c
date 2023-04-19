#include "read_lexems.h"

// 2*moda-((xy*0.245*678.43534)/mod+56.5)+m

ErrorsType ReadLexeme(char *expression, int *index_symbol,
                      struct Lexeme *result) {
  ErrorsType errors = NO_ERRORS;
  errors =
      CheckErrors(4, CHECK_POINTER(expression), CHECK_POINTER(index_symbol),
                  CHECK_POINTER(result), CHECK_NEGATIVE(*index_symbol));
  if (errors == NO_ERRORS) {
    LexemeType lexeme_type = CheckLexeme(expression, *index_symbol);
    *result = ProcessReadLexeme(expression, index_symbol, lexeme_type);
  }

  return errors;
}

struct Lexeme ProcessReadLexeme(char *expression, int *index_symbol,
                                LexemeType lexeme_type) {
  struct Lexeme lexeme = GetEmptyLexeme();
  if (lexeme_type == OPERATOR) {
    lexeme = ReadOperator(expression, index_symbol);
  } else if (lexeme_type == OPERAND) {
    lexeme = ReadOperand(expression, index_symbol);
  }
  return lexeme;
}

struct Lexeme InitializationLexeme(LexemeType lexeme_type, double operand,
                                   Operands operand_type,
                                   Operators operator_type,
                                   int priority_level) {
  struct Lexeme lexeme = {.lexeme_type = lexeme_type,
                          .operand = operand,
                          .operand_type = operand_type,
                          .oprtr = operator_type,
                          .priority_level = priority_level};
  return lexeme;
}

struct Lexeme GetEmptyLexeme() {
  struct Lexeme lexeme = {.lexeme_type = EMPTY_LEXEME,
                          .operand = 0,
                          .operand_type = EMPTY_OPERAND,
                          .oprtr = EMPTY_OPERATOR,
                          .priority_level = 0};
  return lexeme;
}

LexemeType CheckLexeme(char *expression, int index_symbol) {
  LexemeType lexeme_type = EMPTY_LEXEME;
  if (CheckOperator(expression, index_symbol)) {
    lexeme_type = OPERATOR;
  } else if (CheckOperand(expression, index_symbol)) {
    lexeme_type = OPERAND;
  }
  return lexeme_type;
}

bool CheckOperator(char *expression, int index_symbol) {
  bool result = false;
  char symbol = expression[index_symbol];
  if (CheckSymbolsOperators(symbol)) {
    result = true;
  } else if (CheckModOperator(expression, index_symbol)) {
    result = true;
  } else if (CheckFunctionOperator(expression, index_symbol)) {
    result = true;
  }
  return result;
}

bool CheckSymbolsOperators(char symbol) {
  bool result = false;
  if (symbol == '(' || symbol == ')' || symbol == '+' || symbol == '-' ||
      symbol == '*' || symbol == '/' || symbol == '^') {
    result = true;
  }
  return result;
}

bool CheckFunctionOperator(char *expression, int index_symbol) {
  bool result = false;
  const char *functions[] = {"ln",   "cos",  "sin",  "tan", "log",
                             "sqrt", "acos", "asin", "atan"};
  for (int counter = 0; counter < 9; counter++) {
    if (strlen(expression)) {
      result = CheckStrNCmp(&expression[index_symbol], functions[counter],
                            strlen(functions[counter]));
    }
    if (result == true) {
      break;
    }
  }
  return result;
}

bool CheckStrNCmp(char *expression, const char *func, int length) {
  bool result = false;
  if ((int)strlen(func) >= length) {
    int check = strncmp(expression, func, length);
    if (!check) {
      result = true;
    }
  }
  return result;
}

bool CheckModOperator(char *expression, int index_symbol) {
  bool result = false;
  char symbol = expression[index_symbol];

  if (symbol == 'm' && expression[index_symbol + 1] != '\0' &&
      expression[index_symbol + 1] == 'o' &&
      expression[index_symbol + 2] != '\0' &&
      expression[index_symbol + 2] == 'd' &&
      expression[index_symbol + 3] != '\0' &&
      !(CheckSymbolsOperators(expression[index_symbol + 3])) &&
      index_symbol != 0 &&
      !(CheckSymbolsOperators(expression[index_symbol - 1]))) {
    result = true;
  }
  return result;
}

bool CheckOperand(char *expression, int index_symbol) {
  bool result = false;
  char symbol = expression[index_symbol];
  if (symbol >= ASCII_NUM_START && symbol <= ASCII_NUM_FINISH) {
    result = true;
  } else if (symbol >= ASCII_LETTER_START && symbol <= ASCII_LETTER_FINISH) {
    result = true;
  } else if ((symbol == '.' || symbol == ',') &&
             expression[index_symbol + 1] != '\0' &&
             (expression[index_symbol + 1] >= ASCII_NUM_START &&
              expression[index_symbol + 1] <= ASCII_NUM_FINISH)) {
    result = true;
  }
  return result;
}

struct Lexeme ReadOperator(char *expression, int *index_symbol) {
  Operators operator= EMPTY_OPERATOR;
  if (expression[*index_symbol] == '(') {
    operator= STARTS_BRACKETS;
    *index_symbol += 1;
  } else if (expression[*index_symbol] == ')') {
    operator= END_BRACKETS;
    *index_symbol += 1;
  } else if (expression[*index_symbol] == '+') {
    operator= ADDITION;
    if (CheckUnOperator(expression, *index_symbol)) {
      operator= UNARY_PLUS;
    }
    *index_symbol += 1;
  } else if (expression[*index_symbol] == '-') {
    operator= SUBSTRACTION;
    if (CheckUnOperator(expression, *index_symbol)) {
      operator= UNARY_MINUS;
    }
    *index_symbol += 1;
  } else if (expression[*index_symbol] == '*') {
    operator= MULTIPLICATION;
    *index_symbol += 1;
  } else if (expression[*index_symbol] == '/') {
    operator= DIVISION;
    *index_symbol += 1;
  } else if (expression[*index_symbol] == '^') {
    operator= POWER;
    *index_symbol += 1;
  } else if (expression[*index_symbol] == 'm') {
    operator= MODULUS;
    *index_symbol += 3;
  } else if (CheckFunctionOperator(expression, *index_symbol)) {
    operator= ReadFunctionsOperators(expression, index_symbol);
  }
  struct Lexeme lexeme = {.lexeme_type = OPERATOR,
                          .operand = 0,
                          .operand_type = EMPTY_OPERAND,
                          .oprtr = operator,
                          .priority_level = 0 };
  return lexeme;
}

Operators ReadFunctionsOperators(char *expression, int *index_symbol) {
  Operators result = EMPTY_OPERATOR;
  if (CheckStrNCmp(&expression[*index_symbol], "ln", 2)) {
    result = LN;
    *index_symbol += 2;
  } else if (CheckStrNCmp(&expression[*index_symbol], "cos", 3)) {
    result = COS;
    *index_symbol += 3;
  } else if (CheckStrNCmp(&expression[*index_symbol], "sin", 3)) {
    result = SIN;
    *index_symbol += 3;
  } else if (CheckStrNCmp(&expression[*index_symbol], "tan", 3)) {
    result = TAN;
    *index_symbol += 3;
  } else if (CheckStrNCmp(&expression[*index_symbol], "log", 3)) {
    result = LOG;
    *index_symbol += 3;
  } else if (CheckStrNCmp(&expression[*index_symbol], "sqrt", 4)) {
    result = SQRT;
    *index_symbol += 4;
  } else if (CheckStrNCmp(&expression[*index_symbol], "acos", 4)) {
    result = ACOS;
    *index_symbol += 4;
  } else if (CheckStrNCmp(&expression[*index_symbol], "asin", 4)) {
    result = ASIN;
    *index_symbol += 4;
  } else if (CheckStrNCmp(&expression[*index_symbol], "atan", 4)) {
    result = ATAN;
    *index_symbol += 4;
  }
  return result;
}

bool CheckUnOperator(char *expression, int index_symbol) {
  bool result = false;
  if (expression[index_symbol] == '+' || expression[index_symbol] == '-') {
    if (index_symbol == 0) {
      result = true;
    } else if (CheckSymbolsOperators(expression[index_symbol - 1]) ||
               (index_symbol > 2 &&
                CheckModOperator(expression, index_symbol - 3))) {
      if (expression[index_symbol - 1] != ')') {
        result = true;
      }
    }
  }
  return result;
}

void WriteUnOperator(char *expression, int index_symbol,
                     struct Lexeme *lexeme) {
  if (expression[index_symbol] == '+') {
    lexeme->oprtr = UNARY_PLUS;
  } else if (expression[index_symbol] == '-') {
    lexeme->oprtr = UNARY_MINUS;
  }
}

struct Lexeme ReadOperand(char *expresion, int *index_symbol) {
  struct Lexeme lexeme = GetEmptyLexeme();
  char symbol = expresion[*index_symbol];
  if ((symbol >= ASCII_NUM_START && symbol <= ASCII_NUM_FINISH) ||
      symbol == '.' || symbol == ',') {
    lexeme = ReadNumOperand(expresion, index_symbol);
  } else if (symbol >= ASCII_LETTER_START && symbol <= ASCII_LETTER_FINISH) {
    lexeme = InitializationLexeme(OPERAND, symbol, LETTER, EMPTY_OPERATOR, 0);
    *index_symbol += 1;
  }
  return lexeme;
}

struct Lexeme ReadNumOperand(char *expresion, int *index_symbol) {
  ErrorsType errors = NO_ERRORS;
  struct Lexeme lexeme = GetEmptyLexeme();
  char *str_num = GetMemory(&errors, MAX_SIZE_EXPRESSION, sizeof(char));
  str_num[0] = '\0';
  if (ERRORS_NOT_FOUND(errors)) {
    CheckDotInExpression(expresion, index_symbol, str_num);
    GetStringNumInExpression(expresion, index_symbol, str_num);

    lexeme = InitializationLexeme(OPERAND, StringToDouble(str_num), NUMBER,
                                  EMPTY_OPERATOR, 0);
    free(str_num);
  }
  return lexeme;
}

void CheckDotInExpression(char *expresion, int *index_symbol, char *result) {
  if (expresion[*index_symbol] == '.' || expresion[*index_symbol] == ',') {
    result[0] = '0';
  }
}

void GetStringNumInExpression(char *expresion, int *index_symbol,
                              char *result) {
  if (index_symbol && expresion && result) {
    int counter_num = 0;
    if (result[counter_num] != '\0') {
      counter_num = 1;
    }
    for (;; *index_symbol += 1) {
      if (expresion[*index_symbol] == '\0') {
        break;
      }
      if (expresion[*index_symbol] >= ASCII_NUM_START &&
          expresion[*index_symbol] <= ASCII_NUM_FINISH) {
        result[counter_num] = expresion[*index_symbol];
        counter_num++;
        result[counter_num] = '\0';
      } else if (expresion[*index_symbol] == '.' ||
                 expresion[*index_symbol] == ',') {
        result[counter_num] = ',';
        counter_num++;
      } else {
        break;
      }
    }
  }
}

double StringToDouble(char *for_convert) {
  char *save = for_convert;
  char check_dot[255];
  char *save_2 = for_convert;
  strcpy(check_dot, save);
  for (int counter = 0; counter < (int)strlen(check_dot); counter++) {
    if (check_dot[counter] == ',') {
      check_dot[counter] = '.';
    }
  }
  double result = strtod(for_convert, &save);
  double result_2 = strtod(check_dot, &save_2);
  if (fabs(result) != fabs(result_2)) {
    if (result_2 > result) {
      result = result_2;
    }
  }
  return result;
}
