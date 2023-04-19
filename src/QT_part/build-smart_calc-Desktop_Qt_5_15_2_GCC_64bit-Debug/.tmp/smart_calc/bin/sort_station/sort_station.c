#include "sort_station.h"

// 2*2moda-((xy*0.245*678.43534)/mod+.567)+234,45^m

ErrorsType InitializationConverter(struct ConvertStation *for_init,
                                   struct Expression *for_conversion,
                                   struct Expression *for_result) {
  ErrorsType errors = NO_ERRORS;
  errors =
      CheckErrors(2, CHECK_POINTER(for_init), CHECK_POINTER(for_conversion));
  errors = CheckCorrectBrackets(for_conversion);
  if (ERRORS_NOT_FOUND(errors)) {
    for_init->for_convert = for_conversion;
    for_init->result = for_result;
    for_init->stack_operators = CreateList(&errors);
    for_init->handler_token = FrontList(for_conversion->lexems);
    for_init->errors = NO_ERRORS;
  }
  return errors;
}

ErrorsType CheckCorrectBrackets(struct Expression *for_conversion) {
    ErrorsType errors = NO_ERRORS;
    if (for_conversion) {
        int counter_brackets = 0;
        for (struct Node *node = FrontList(for_conversion->lexems); node != NULL; node = node->next_node) {
            if (node->lexeme.oprtr == STARTS_BRACKETS) {
                counter_brackets++;
            } else if (node->lexeme.oprtr == END_BRACKETS) {
                counter_brackets--;
            }
        }
        if (counter_brackets != 0) {
            errors = INCORRECT_DATA;
        }
    }
    return errors;
}

ErrorsType InfixToReversePolish(struct ConvertStation *converter) {
  converter->errors = CheckErrors(1, CHECK_POINTER(converter),
                                  CHECK_POINTER(converter->for_convert),
                                  CHECK_POINTER(converter->stack_operators));
  if (ERRORS_NOT_FOUND(converter->errors)) {
    while (converter->handler_token != NULL && converter->errors == NO_ERRORS) {
      converter->errors = Handlerlexeme(converter);
      converter->handler_token = converter->handler_token->next_node;
    }
    if (!(EmptyList(converter->stack_operators))) {
      struct Node *node = FrontList(converter->stack_operators);
      for (; node != NULL;) {
        if (node->lexeme.oprtr!= STARTS_BRACKETS) {
          converter->errors =
              PushBackList(converter->result->lexems, node->lexeme);
        }
        converter->errors = PopFrontList(converter->stack_operators);
        node = FrontList(converter->stack_operators);
      }
    }
    FreeList(converter->stack_operators);
    free(converter->stack_operators);
  }
  return converter->errors;
}

ErrorsType Handlerlexeme(struct ConvertStation *converter) {
  converter->errors = CheckErrors(2, CHECK_POINTER(converter),
                                  CHECK_POINTER(converter->handler_token));
  if (ERRORS_NOT_FOUND(converter->errors)) {
    if (converter->handler_token->lexeme.lexeme_type == OPERAND) {
      converter->errors = HandlerOperand(converter->result->lexems,
                                         &converter->handler_token->lexeme);
    } else if (converter->handler_token->lexeme.lexeme_type == OPERATOR) {
      converter->errors = HandlerOperator(converter);
    } else if (converter->handler_token->lexeme.lexeme_type == EMPTY_LEXEME) {
      converter->errors = READ_EMPTY_LEXEME;
    }
  }

  return converter->errors;
}

ErrorsType HandlerOperand(struct List *for_write_result,
                          struct Lexeme *lexeme) {
  ErrorsType errors = NO_ERRORS;
  errors = PushBackList(for_write_result, *lexeme);
  return errors;
}

ErrorsType HandlerOperator(struct ConvertStation *converter) {
  ErrorsType errors = NO_ERRORS;
  if (CheckBrackets(&converter->handler_token->lexeme)) {
    errors = HandlerOperatorBrackets(converter);
  } else if (EmptyList(converter->stack_operators) ||
             FrontList(converter->stack_operators)
                 ->lexeme.
                 oprtr== STARTS_BRACKETS) {
    errors = PushFrontList(converter->stack_operators,
                           converter->handler_token->lexeme);
  } else {
    errors = HandlerComprassionOperators(converter);
  }
  return errors;
}

ErrorsType HandlerOperatorBrackets(struct ConvertStation *converter) {
  ErrorsType errors = NO_ERRORS;
  if (converter->handler_token->lexeme.oprtr== STARTS_BRACKETS) {
    errors = PushFrontList(converter->stack_operators,
                           converter->handler_token->lexeme);
  } else if (converter->handler_token->lexeme.oprtr== END_BRACKETS) {
    for (struct Node *operator= FrontList(converter->stack_operators);
         operator->lexeme.oprtr!= STARTS_BRACKETS && operator!= NULL;) {
      PushBackList(converter->result->lexems, operator->lexeme);
      errors = PopFrontList(converter->stack_operators);
      operator= FrontList(converter->stack_operators);
      if (errors != NO_ERRORS || operator== NULL) {
        break;
      }
    }
    errors = PopFrontList(converter->stack_operators);
  }
  return errors;
}

ErrorsType HandlerOperatorEndBrackets(struct ConvertStation *converter) {
  struct Node *front_operator = FrontList(converter->stack_operators);
  while (front_operator != NULL && converter->errors == NO_ERRORS) {
    converter->errors = PushBackList(converter->result->lexems,
                                     converter->handler_token->lexeme);
    converter->errors = PopFrontList(converter->stack_operators);
    front_operator = FrontList(converter->stack_operators);
    if (front_operator->lexeme.oprtr== STARTS_BRACKETS) {
      converter->errors = PopFrontList(converter->stack_operators);
      break;
    }
  }
  return converter->errors;
}

ErrorsType HandlerComprassionOperators(struct ConvertStation *converter) {
  ErrorsType errors = NO_ERRORS;
  struct Node *operator= FrontList(converter->stack_operators);
  for (; operator->lexeme.oprtr!= STARTS_BRACKETS && operator!= NULL &&
         errors == NO_ERRORS;) {
    if (converter->handler_token->lexeme
            .
            oprtr== POWER && FrontList(converter->stack_operators)
            ->lexeme.
            oprtr== POWER) {
      break;
    }
    PriorityLvl pr_lvl_op1 = GetPriorityLvl(&converter->handler_token->lexeme);
    PriorityLvl pr_lvl_op2 =
        GetPriorityLvl(&FrontList(converter->stack_operators)->lexeme);
    if (pr_lvl_op1 <= pr_lvl_op2) {
      errors = PushBackList(converter->result->lexems, operator->lexeme);
      errors = PopFrontList(converter->stack_operators);
      operator= FrontList(converter->stack_operators);
      if (errors != NO_ERRORS || operator== NULL) {
        break;
      }
    } else {
      break;
    }
  }
  converter->errors = PushFrontList(converter->stack_operators,
                                    converter->handler_token->lexeme);
  return errors;
}

PriorityLvl GetPriorityLvl(struct Lexeme *lex) {
  PriorityLvl result = EMPTY_LVL;
  if (lex->oprtr== ADDITION || lex->oprtr== SUBSTRACTION) {
    result = LOW;
  } else if (lex->oprtr== DIVISION || lex->oprtr== MULTIPLICATION || lex->
             oprtr== MODULUS) {
    result = AVERAGE;
  } else if (lex->oprtr== POWER || lex->oprtr== UNARY_PLUS || lex->
             oprtr== UNARY_MINUS || CheckFunctions(lex)) {
    result = HIGH;
  }
  return result;
}

bool CheckFunctions(struct Lexeme *lexeme) {
  bool result = false;
  if (lexeme->oprtr== COS || lexeme->oprtr== SIN ||
      lexeme->
      oprtr== TAN || lexeme->
      oprtr== ACOS || lexeme->
      oprtr== ASIN || lexeme->
      oprtr== ATAN || lexeme->
      oprtr== SQRT || lexeme->
      oprtr== LN || lexeme->
      oprtr== LOG) {
    result = true;
  }
  return result;
}

bool CheckBrackets(struct Lexeme *lexeme) {
  bool result = false;
  if (lexeme->oprtr== STARTS_BRACKETS || lexeme->oprtr== END_BRACKETS) {
    result = true;
  }
  return result;
}
