#include <stdio.h>
#include <time.h>
#include <unistd.h>

unsigned sleep(unsigned seconds) {
  const uint32_t tickstart = clock();
  const int period = seconds * CLOCKS_PER_SEC;
  while ((clock() - tickstart) < period)
    asm volatile("nop");
  return 0;
}

int usleep(useconds_t usec) {
  const size_t tickstart = clock();
  static const size_t clocksPerUsec = CLOCKS_PER_SEC / 1000000;
  const size_t period = usec * clocksPerUsec;
  while ((clock() - tickstart) < period)
    asm volatile("nop");
  return 0;
}

void swab(const void *src, void *dest, ssize_t n) {
  unsigned char tmp;
  while (n--) {
    tmp = *((unsigned char *)src);
    *((unsigned char *)src) = *((unsigned char *)dest);
    *((unsigned char *)dest) = tmp;
  }
}
