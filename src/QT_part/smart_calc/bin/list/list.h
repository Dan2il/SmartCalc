/*!
 * \file list.h
 */
#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../allocate_memory/allocate_memory.h"
#include "../processing_errors/processing_errors.h"

typedef enum { EMPTY_LEXEME, OPERATOR, OPERAND } LexemeType;

typedef enum {
  EMPTY_OPERATOR,
  STARTS_BRACKETS,
  END_BRACKETS,
  MULTIPLICATION,
  ADDITION,
  SUBSTRACTION,
  DIVISION,
  POWER,
  MODULUS,
  UNARY_PLUS,
  UNARY_MINUS,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} Operators;

typedef enum {
  EMPTY_OPERAND,
  DOT,
  COMMA,
  LETTER,
  NUMBER,
  OTHER_SYMBOL
} Operands;

struct Lexeme {
  LexemeType lexeme_type;
  Operands operand_type;
  double operand;
  Operators oprtr;
  int priority_level;
};

struct Node {
  struct Lexeme lexeme;
  struct Node *next_node;
  int num_node;
};

struct List {
  struct Node *null_node;
  int size;
};

#define CYCLE_FOR_LIST(START_NODE, OPERATION)                                  \
  for (struct Node *next_node = START_NODE; next_node != NULL;                 \
       next_node = next_node->next_node) {                                     \
    OPERATION                                                                  \
  }

#define CYCLE_FOR_LIST_PTR(START_NODE, OPERATION)                              \
  for (struct Node *next_node = START_NODE; next_node != NULL;                 \
       next_node = next_node->next_node) {                                     \
    OPERATION                                                                  \
  }

struct Node *CreateNode(struct Lexeme lex, int num_node);
struct List *CreateList();
ErrorsType InitializationList(struct List *list);
ErrorsType FreeList(struct List *list);

ErrorsType PushFrontList(struct List *list, struct Lexeme push_lexeme);
ErrorsType PushBackList(struct List *list, struct Lexeme push_lexeme);
struct Node *FrontList(struct List *list);
struct Node *BackList(struct List *list);
struct Node *AtList(struct List *list, int num_node);
ErrorsType PopFrontList(struct List *list);
ErrorsType PopBackList(struct List *list);

ErrorsType CheckLexemeType(LexemeType lex_t);

bool EmptyList(struct List *list);

#endif
