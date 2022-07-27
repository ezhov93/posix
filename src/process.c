#include <stdio.h>

int errno;

void abort(void) {
  for (;;) {
  }
}

void exit(int error) {
  fprintf(&__stderr, "...Program finished with exit code %d\n", error);
  abort();
}