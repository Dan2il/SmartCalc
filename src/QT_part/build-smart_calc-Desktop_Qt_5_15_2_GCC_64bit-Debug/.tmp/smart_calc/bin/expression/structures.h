#ifndef EXPRESSION_STRUCTURES_H
#define EXPRESSION_STRUCTURES_H

#include "../list/list.h"

typedef enum { EMPTY, CLASSIC, POLISH, REVERSE_POLISH } TypeNotation;

struct Expression {
  struct List *lexems;
  TypeNotation type_lexems;
  int status_write_lexems;
  char *string_representation;
  TypeNotation type_string;
};

#endif  // EXPRESSION_STRUCTURES_H