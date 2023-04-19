#include <stdio.h>
#include <string.h>

#include "processing_errors.h"
#include "read_expression.h"

int main() {
  char expression[256];
  GetExpression(expression);
  printf("exp: '%s'\n", expression);
}