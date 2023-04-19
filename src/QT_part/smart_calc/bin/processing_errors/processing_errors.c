#include "processing_errors.h"

ErrorsType CheckErrors(int num_check, ...) {
  ErrorsType result = NO_ERRORS;
  va_list checks;
  va_start(checks, num_check);
  for (int counter_num = 0; counter_num < num_check; counter_num++) {
    result = va_arg(checks, ErrorsType);
    if (result != NO_ERRORS) {
      break;
    }
  }

  va_end(checks);
  return result;
}

// void PrintErrors(ErrorsType errors) {
//   char *text_errors = NULL;
//   GetTextErrors(errors, text_errors);
//   printf("%s\n", text_errors);
//   if (text_errors) {
//     free(text_errors);
//   }
// }

// void GetTextErrors(ErrorsType errors, char *text_errors) {
//   text_errors = (char *)malloc(256 * sizeof(char));
//   if (text_errors) {
//     if (errors == NO_ERRORS) {
//       text_errors = "Нет ошибок";
//     } else if (errors == NULL_POINTER) {
//       text_errors = "Указатель равен NULL";
//     } else if (errors == READ_EMPTY_LEXEME) {
//       text_errors = "Прочитана пустая лексема";
//     } else if (errors == READ_INCORRECT_SYMBOL) {
//       text_errors = "Прочитан некорректный символ";
//     } else if (errors == INCORRECT_DATA) {
//       text_errors = "Поданы некорректные данные";
//     } else if (errors == NEGATIVE_NUMBER) {
//       text_errors = "Отрицательное число";
//     } else if (errors == NULL_NUMBER) {
//       text_errors = "Число равно нулю";
//     } else if (errors == EMPTY_EXPRESSION) {
//       text_errors = "Пустое выражение";
//     } else if (errors == LONG_EXPRESSION) {
//       text_errors = "Слишком длинное выражение";
//     } else if (errors == READ_EOF) {
//       text_errors = "Прочитан EOF";
//     } else if (errors == COMPRASSION_ERROR) {
//       text_errors = "Ошибка сравнения";
//     } else {
//       text_errors = "Ошибка вывода";
//     }
//   }
// }

ErrorsType CheckPointer(void *pointer) {
  ErrorsType result = NO_ERRORS;
  if (!pointer) {
    result = NULL_POINTER;
  }
  return result;
}

ErrorsType CheckNegativeNumber(double num) {
  ErrorsType result = NO_ERRORS;
  if (num < 0) {
    result = NEGATIVE_NUMBER;
  }
  return result;
}

ErrorsType CheckNullNumber(double num) {
  ErrorsType result = NO_ERRORS;
  if (num == 0) {
    result = NULL_NUMBER;
  }
  return result;
}

ErrorsType CheckLengthExpression(char *expression) {
  ErrorsType result = NO_ERRORS;
  if (strlen(expression) > 255) {
    result = LONG_EXPRESSION;
  }
  return result;
}