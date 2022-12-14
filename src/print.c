#include <stdarg.h>

static void printchar(char **str, int c) {
  extern int putchar(int c);

  if (str) {
    **str = c;
    ++(*str);
  } else
    (void)putchar(c);
}

#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints(char **out, const char *string, int width, int pad) {
  register int pc = 0, padchar = ' ';

  if (width > 0) {
    register int len = 0;
    register const char *ptr;
    for (ptr = string; *ptr; ++ptr) ++len;
    if (len >= width)
      width = 0;
    else
      width -= len;
    if (pad & PAD_ZERO) padchar = '0';
  }
	
  if (!(pad & PAD_RIGHT)) {
    for (; width > 0; --width) {
      printchar(out, padchar);
      ++pc;
    }
  }
	
  for (; *string; ++string) {
    printchar(out, *string);
    ++pc;
  }
	
  for (; width > 0; --width) {
    printchar(out, padchar);
    ++pc;
  }

  return pc;
}

#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int b, int sg, int width, int pad,
                  int letbase) {
  char print_buf[PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0, pc = 0;
  register unsigned int u = i;

  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return prints(out, print_buf, width, pad);
  }

  if (sg && b == 10 && i < 0) {
    neg = 1;
    u = -i;
  }

  s = print_buf + PRINT_BUF_LEN - 1;
  *s = '\0';

  while (u) {
    t = u % b;
    if (t >= 10) t += letbase - '0' - 10;
    *--s = t + '0';
    u /= b;
  }

  if (neg) {
    if (width && (pad & PAD_ZERO)) {
      printchar(out, '-');
      ++pc;
      --width;
    } else {
      *--s = '-';
    }
  }

  return pc + prints(out, s, width, pad);
}

static int print(char **out, const char *format, va_list args) {
  register int width, pad;
  register int pc = 0;
  char scr[2];

  for (; *format != 0; ++format) {
    if (*format == '%') {
      ++format;
      width = pad = 0;
      if (*format == '\0') break;
      if (*format == '%') goto out;
      if (*format == '-') {
        ++format;
        pad = PAD_RIGHT;
      }
      while (*format == '0') {
        ++format;
        pad |= PAD_ZERO;
      }
      for (; *format >= '0' && *format <= '9'; ++format) {
        width *= 10;
        width += *format - '0';
      }
      if (*format == 's') {
        register char *s = (char *)va_arg(args, int);
        pc += prints(out, s ? s : "(null)", width, pad);
        continue;
      }
      if (*format == 'd') {
        pc += printi(out, va_arg(args, int), 10, 1, width, pad, 'a');
        continue;
      }
      if (*format == 'x') {
        pc += printi(out, va_arg(args, int), 16, 0, width, pad, 'a');
        continue;
      }
      if (*format == 'X') {
        pc += printi(out, va_arg(args, int), 16, 0, width, pad, 'A');
        continue;
      }
      if (*format == 'u') {
        pc += printi(out, va_arg(args, int), 10, 0, width, pad, 'a');
        continue;
      }
      if (*format == 'c') {
        scr[0] = (char)va_arg(args, int);
        scr[1] = '\0';
        pc += prints(out, scr, width, pad);
        continue;
      }
    } else {
    out:
      printchar(out, *format);
      ++pc;
    }
  }
  if (out) **out = '\0';
  va_end(args);
  return pc;
}

__attribute__((weak)) int printf(const char *format, ...) {
  va_list args;

  va_start(args, format);
  return print(0, format, args);
}

__attribute__((weak)) int sprintf(char *out, const char *format, ...) {
  va_list args;

  va_start(args, format);
  return print(&out, format, args);
}

__attribute__((weak)) int snprintf(char *buf, unsigned int count, const char *format, ...) {
  va_list args;

  (void)count;

  va_start(args, format);
  return print(&buf, format, args);
}

// int main(void)
// {
// 	char *ptr = "Hello world!";
// 	char *np = 0;
// 	int i = 5;
// 	unsigned int bs = sizeof(int)*8;
// 	int mi;
// 	char buf[80];

// 	mi = (1 << (bs-1)) + 1;
// 	printf("%s\n", ptr);
// 	printf("printf test\n");
// 	printf("%s is null pointer\n", np);
// 	printf("%d = 5\n", i);
// 	printf("%d = - max int\n", mi);
// 	printf("char %c = 'a'\n", 'a');
// 	printf("hex %x = ff\n", 0xff);
// 	printf("hex %02x = 00\n", 0);
// 	printf("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
// 	printf("%d %s(s)%", 0, "message");
// 	printf("\n");
// 	printf("%d %s(s) with %%\n", 0, "message");
// 	sprintf(buf, "justif: \"%-10s\"\n", "left"); printf("%s", buf);
// 	sprintf(buf, "justif: \"%10s\"\n", "right"); printf("%s", buf);
// 	sprintf(buf, " 3: %04d zero padded\n", 3); printf("%s", buf);
// 	sprintf(buf, " 3: %-4d left justif.\n", 3); printf("%s", buf);
// 	sprintf(buf, " 3: %4d right justif.\n", 3); printf("%s", buf);
// 	sprintf(buf, "-3: %04d zero padded\n", -3); printf("%s", buf);
// 	sprintf(buf, "-3: %-4d left justif.\n", -3); printf("%s", buf);
// 	sprintf(buf, "-3: %4d right justif.\n", -3); printf("%s", buf);

// 	return 0;
// }