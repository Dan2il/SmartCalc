#include "calculation.h"

ErrorsType HandlerCalculation(struct List *expression, double *result) {
  ErrorsType errors = NO_ERRORS;
  errors =
      CheckErrors(3, CHECK_POINTER(expression),
                  CHECK_POINTER(expression->null_node), CHECK_POINTER(result));
  if (ERRORS_NOT_FOUND(errors)) {
    struct List *stack_number = CreateList(&errors);
    if (ERRORS_NOT_FOUND(errors)) {
      struct Node *token = FrontList(expression);
      for (; token != NULL; token = token->next_node) {
        if (token->lexeme.lexeme_type == OPERAND) {
          errors = PushFrontList(stack_number, token->lexeme);
        } else if (token->lexeme.lexeme_type == OPERATOR) {
          errors = CalculationOperator(stack_number, token);
        }
        if (errors != NO_ERRORS) {
          break;
        }
        if (FrontList(stack_number)->lexeme.operand == NAN ||
            FrontList(stack_number)->lexeme.operand == INFINITY) {
          break;
        }
      }
      if (token && EmptyList(stack_number)) {
        errors = INCORRECT_DATA;
      }
      if (!(EmptyList(stack_number))) {
        if (isnan(FrontList(stack_number)->lexeme.operand)) {
          *result = 0;
        } else if (!(EmptyList(stack_number))) {
          *result = FrontList(stack_number)->lexeme.operand;
        }
      }
    }
    if (stack_number) {
      FreeList(stack_number);
      free(stack_number);
    }
  }
  return errors;
}

ErrorsType HandlerCalculationWhithX(struct List *expression, double *result,
                                    double variable_x) {
  ErrorsType errors = NO_ERRORS;
  errors =
      CheckErrors(3, CHECK_POINTER(expression),
                  CHECK_POINTER(expression->null_node), CHECK_POINTER(result));
  if (ERRORS_NOT_FOUND(errors)) {
    struct List *stack_number = CreateList(&errors);
    if (ERRORS_NOT_FOUND(errors)) {
      struct Node *token = FrontList(expression);
      for (; token != NULL; token = token->next_node) {
        if (token->lexeme.lexeme_type == OPERAND) {
          if (token->lexeme.operand_type == LETTER) {
            struct Lexeme lex_x = {.lexeme_type = OPERAND,
                                   .operand = variable_x,
                                   .operand_type = NUMBER,
                                   .oprtr = EMPTY_OPERATOR,
                                   .priority_level = 0};
            errors = PushFrontList(stack_number, lex_x);
          } else if (token->lexeme.operand_type == NUMBER) {
            errors = PushFrontList(stack_number, token->lexeme);
          }
        } else if (token->lexeme.lexeme_type == OPERATOR) {
          errors = CalculationOperator(stack_number, token);
        }
        if (errors != NO_ERRORS) {
          break;
        }
        if (FrontList(stack_number)->lexeme.operand == NAN ||
            FrontList(stack_number)->lexeme.operand == INFINITY) {
          break;
        }
      }
      if ((!EmptyList(stack_number))) {
        if (isnan(FrontList(stack_number)->lexeme.operand)) {
          *result = 0;
        } else if (!(EmptyList(stack_number))) {
          *result = FrontList(stack_number)->lexeme.operand;
        }
      }
    }
    if (stack_number) {
      FreeList(stack_number);
      free(stack_number);
    }
  }
  return errors;
}

ErrorsType CalculationOperator(struct List *stack_number,
                               struct Node *operator) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(CHECK_POINTER(stack_number), CHECK_POINTER(operator));
  if (ERRORS_NOT_FOUND(errors)) {
    if (!(EmptyList(stack_number))) {
      if (operator->lexeme.oprtr == UNARY_PLUS || operator->lexeme.oprtr ==
          UNARY_MINUS) {
        struct Node *front_stack_number = FrontList(stack_number);
        CalculationUnOperator(front_stack_number, operator);
      } else if (operator->lexeme.oprtr == POWER) {
        CalculationPowerOperator(stack_number);
      } else if (operator->lexeme.oprtr == COS) {
        FrontList(stack_number)->lexeme.operand =
            cos(FrontList(stack_number)->lexeme.operand / 57.29577951308);
      } else if (operator->lexeme.oprtr == SIN) {
        FrontList(stack_number)->lexeme.operand =
            sin(FrontList(stack_number)->lexeme.operand / 57.29577951308);
      } else if (operator->lexeme.oprtr == TAN) {
        FrontList(stack_number)->lexeme.operand =
            tan(FrontList(stack_number)->lexeme.operand / 57.29577951308);
      } else if (operator->lexeme.oprtr == ACOS) {
        FrontList(stack_number)->lexeme.operand =
            acos(FrontList(stack_number)->lexeme.operand) * 57.29577951308;
      } else if (operator->lexeme.oprtr == ASIN) {
        FrontList(stack_number)->lexeme.operand =
            asin(FrontList(stack_number)->lexeme.operand) * 57.29577951308;
      } else if (operator->lexeme.oprtr == ATAN) {
        FrontList(stack_number)->lexeme.operand =
            atan(FrontList(stack_number)->lexeme.operand) * 57.29577951308;
      } else if (operator->lexeme.oprtr == SQRT) {
        FrontList(stack_number)->lexeme.operand =
            sqrt(FrontList(stack_number)->lexeme.operand);
      } else if (operator->lexeme.oprtr == LN) {
        FrontList(stack_number)->lexeme.operand =
            log(FrontList(stack_number)->lexeme.operand);
      } else if (operator->lexeme.oprtr == LOG) {
        FrontList(stack_number)->lexeme.operand =
            log10(FrontList(stack_number)->lexeme.operand);
      } else {
        errors = CalculationOtherOperator(stack_number, operator);
      }
    } else {
      errors = INCORRECT_DATA;
    }
  }
  return errors;
}

void CalculationUnOperator(struct Node *front_stack_number,
                           struct Node *un_operator) {
  if (un_operator->lexeme.oprtr == UNARY_MINUS) {
    front_stack_number->lexeme.operand =
        front_stack_number->lexeme.operand * -1;
  }
}

ErrorsType CalculationPowerOperator(struct List *stack_number) {
  ErrorsType errors = NO_ERRORS;
  struct Node *degree = FrontList(stack_number);
  struct Node *number = degree->next_node;
  if (degree && number) {
    struct Lexeme new_lex = {.lexeme_type = OPERAND,
                             .operand = 0,
                             .operand_type = NUMBER,
                             .oprtr = EMPTY_OPERATOR,
                             .priority_level = 0};
    new_lex.operand = pow(number->lexeme.operand, degree->lexeme.operand);
    PopFrontList(stack_number);
    PopFrontList(stack_number);
    PushFrontList(stack_number, new_lex);
  } else {
    errors = NULL_POINTER;
  }
  return errors;
}

ErrorsType CalculationOtherOperator(struct List *stack_number,
                                    struct Node *operator) {
  ErrorsType errors = NO_ERRORS;
  struct Node *right = FrontList(stack_number);
  struct Node *left = right->next_node;
  if (right && left) {
    struct Lexeme new_lex = {.lexeme_type = OPERAND,
                             .operand = 0,
                             .operand_type = NUMBER,
                             .oprtr = EMPTY_OPERATOR,
                             .priority_level = 0};
    if (operator->lexeme.oprtr == MULTIPLICATION) {
      new_lex.operand = left->lexeme.operand * right->lexeme.operand;
    } else if (operator->lexeme.oprtr == ADDITION) {
      new_lex.operand = left->lexeme.operand + right->lexeme.operand;
    } else if (operator->lexeme.oprtr == SUBSTRACTION) {
      new_lex.operand = left->lexeme.operand - right->lexeme.operand;
    } else if (operator->lexeme.oprtr == DIVISION) {
      new_lex.operand = left->lexeme.operand / right->lexeme.operand;
    } else if (operator->lexeme.oprtr == MODULUS) {
      new_lex.operand = fmod(left->lexeme.operand, right->lexeme.operand);
    }
    PopFrontList(stack_number);
    PopFrontList(stack_number);
    PushFrontList(stack_number, new_lex);
  } else {
    errors = NULL_POINTER;
  }
  return errors;
}
