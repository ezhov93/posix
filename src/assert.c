#include <assert.h>
#include <stdio.h>

void __aeabi_assert (const char *expr, const char *file, int line) {
  char str[12], *p;
  fprintf(stderr, "Assertion failed: %s, file %s, line %d", expr,file,line);
  abort();
}