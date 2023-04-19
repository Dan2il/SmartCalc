#include "expression.h"

// 2 * mod a - ((xy * 0.245 * 678.43534) / mod + 56.5)
// 2*2moda-((xy*0.245*678.43534)/mod+.567)+234,45^m

ErrorsType InitializationExpression(struct Expression *expression,
                                    char *string_representation_expression,
                                    TypeNotation type_notation) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(expression),
                       CHECK_POINTER(string_representation_expression));
  if (ERRORS_NOT_FOUND(errors)) {
    struct List *for_lexems = CreateList(&errors);
    expression->lexems = for_lexems;
    expression->status_write_lexems = 0;
    expression->string_representation = string_representation_expression;
    expression->type_lexems = EMPTY;
    expression->type_string = type_notation;
  }
  return errors;
}

ErrorsType ReadStringExpression(struct Expression *expression) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(expression),
                       CHECK_POINTER(expression->string_representation));
  if (expression->type_string == CLASSIC) {
    errors = ReadStringExpressionToClassinNotation(expression);
  }
  return errors;
}

ErrorsType ReadStringExpressionToClassinNotation(
    struct Expression *expression) {
  ErrorsType errors = NO_ERRORS;
  for (int index_symbol = 0;
       expression->string_representation[index_symbol] != '\0';) {
    struct Lexeme lexeme;
    errors =
        ReadLexeme(expression->string_representation, &index_symbol, &lexeme);
    if (lexeme.lexeme_type != EMPTY_LEXEME) {
        PushBackList(expression->lexems, lexeme);
    } else {
        errors = INCORRECT_DATA;
    }
    if (errors != NO_ERRORS) {
      break;
    }
  }
  return errors;
}

ErrorsType Сalculation(struct Expression *expression) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(expression),
                       CHECK_POINTER(expression->lexems));
  if (expression->type_lexems == REVERSE_POLISH) {
    //
  } else {
    errors = NOT_REVERSE_POLISH;
  }
  return errors;
}
