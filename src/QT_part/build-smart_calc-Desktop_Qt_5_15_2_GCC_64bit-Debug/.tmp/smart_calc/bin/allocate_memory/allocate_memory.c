#include "allocate_memory.h"

void *GetMemory(ErrorsType *errors, int allocate_size, int size_type) {
  void *array = NULL;
  if (errors != NULL) {
    *errors = CheckArgumentsForGetMemory(allocate_size, size_type);
    if (ERRORS_NOT_FOUND(*errors)) {
      array = malloc(allocate_size * size_type);
      if (array == NULL) {
        *errors = NULL_POINTER;
      }
    }
  }
  return array;
}

ErrorsType CheckArgumentsForGetMemory(int allocate_size, int size_type) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(4, CHECK_NEGATIVE(allocate_size),
                       CHECK_NULL_NUMBER(allocate_size),
                       CHECK_NEGATIVE(size_type), CHECK_NULL_NUMBER(size_type));
  return errors;
}