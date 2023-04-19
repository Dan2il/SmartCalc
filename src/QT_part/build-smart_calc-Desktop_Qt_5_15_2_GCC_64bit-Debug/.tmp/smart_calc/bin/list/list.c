#include "list.h"

struct Node *CreateNode(struct Lexeme lex, int num_node) {
  struct Node *new = (struct Node *)malloc(1 * sizeof(struct Node));
  if (new) {
    new->lexeme = lex;
    new->next_node = NULL;
    new->num_node = num_node;
  }
  return new;
}

struct List *CreateList(ErrorsType *errors) {
  struct List *list = (struct List *)malloc(1 * sizeof(struct List));
  *errors = InitializationList(list);
  return list;
}

ErrorsType FreeList(struct List *list) {
  ErrorsType errors = CheckErrors(1, CHECK_POINTER(list));
  if (errors == NO_ERRORS) {
    for (struct Node *next_node = list->null_node; next_node != NULL;) {
      struct Node *clean = next_node;
      next_node = next_node->next_node;
      free(clean);
    }
  }
  return errors;
}

ErrorsType InitializationList(struct List *list) {
  int errors = CheckErrors(1, CHECK_POINTER(list));
  if (errors == NO_ERRORS) {
    struct Lexeme push_lexeme = {.lexeme_type = EMPTY_LEXEME,
                                 .operand = 0,
                                 .operand_type = EMPTY_OPERAND,
                                 .oprtr= EMPTY_OPERATOR,
                                 .priority_level = 0};
    list->null_node = CreateNode(push_lexeme, -1);
    list->size = 0;
    errors = CheckErrors(1, CHECK_POINTER(list->null_node));
  }
  return errors;
}

ErrorsType PushFrontList(struct List *list, struct Lexeme push_lexeme) {
  ErrorsType errors =
      CheckErrors(3, CHECK_POINTER(list), CHECK_POINTER(list->null_node),
                  CheckLexemeType(push_lexeme.lexeme_type));
  if (errors == NO_ERRORS) {
    struct Node *new = CreateNode(push_lexeme, 1);
    new->next_node = list->null_node->next_node;
    list->null_node->next_node = new;
    list->size = list->size + 1;
    int counter_num_node = 0;
    CYCLE_FOR_LIST_PTR(list->null_node->next_node,
                       { next_node->num_node = counter_num_node++; })
  }
  return errors;
}

ErrorsType PushBackList(struct List *list, struct Lexeme push_lexeme) {
  ErrorsType errors =
      CheckErrors(3, CHECK_POINTER(list), CHECK_POINTER(list->null_node),
                  CheckLexemeType(push_lexeme.lexeme_type));
  if (errors == NO_ERRORS) {
    struct Node *new = CreateNode(push_lexeme, list->size + 1);
    CYCLE_FOR_LIST_PTR(list->null_node, {
      if (next_node->next_node == NULL) {
        next_node->next_node = new;
        break;
      }
    })
    list->size += 1;
  }
  return errors;
}

struct Node *FrontList(struct List *list) {
  struct Node *result = NULL;
  ErrorsType errors =
      CheckErrors(2, CHECK_POINTER(list), CHECK_POINTER(list->null_node));
  if (errors == NO_ERRORS) {
    result = list->null_node->next_node;
  }
  return result;
}

struct Node *BackList(struct List *list) {
  struct Node *result = NULL;
  ErrorsType errors =
      CheckErrors(2, CHECK_POINTER(list), CHECK_POINTER(list->null_node));
  if (errors == NO_ERRORS) {
    CYCLE_FOR_LIST_PTR(list->null_node->next_node, {
      if (next_node->next_node == NULL) {
        result = next_node;
        break;
      }
    })
  }
  return result;
}

struct Node *AtList(struct List *list, int num_node) {
  struct Node *result = list->null_node;
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(4, CHECK_POINTER(list), CHECK_POINTER(list->null_node),
                       CHECK_NULL_NUMBER(num_node), CHECK_NEGATIVE(num_node));
  if (ERRORS_NOT_FOUND(errors)) {
    while (result->num_node != num_node) {
      result = result->next_node;
    }
  }
  return result;
}

ErrorsType PopFrontList(struct List *list) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(list), CHECK_POINTER(list->null_node));
  if (ERRORS_NOT_FOUND(errors)) {
    struct Node *node_clear = FrontList(list);
    list->null_node->next_node = node_clear->next_node;
    free(node_clear);
    int counter = 0;
    for (struct Node *node = list->null_node; node != NULL;
         node = node->next_node) {
      node->num_node = counter++;
    }
    list->size = list->size - 1;
  }
  return errors;
}

ErrorsType PopBackList(struct List *list) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(list), CHECK_POINTER(list->null_node));
  if (ERRORS_NOT_FOUND(errors)) {
    struct Node *node_clear = BackList(list);
    struct Node *node = list->null_node;
    for (; node->next_node->next_node != NULL;) {
      node = node->next_node;
    }
    node->next_node = NULL;
    free(node_clear);
    list->size = list->size - 1;
  }
  return errors;
}

bool EmptyList(struct List *list) {
  bool result = false;
  if (list->size == 0) {
    result = true;
  }
  return result;
}

ErrorsType CheckLexemeType(LexemeType lex_t) {
  ErrorsType result = NO_ERRORS;
  if (lex_t == EMPTY_LEXEME) {
    result = READ_EMPTY_LEXEME;
  }
  return result;
}
