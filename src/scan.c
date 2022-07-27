#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define USE_LONGLONG 0

static int _skipAtoi(const char **s) {
  int i = 0;

  while (isdigit(**s)) i = i * 10 + *((*s)++) - '0';
  return i;
}

char *_skipSpaces(const char *str) {
  while (isspace(*str)) ++str;
  return (char *)str;
}

int vsscanf(const char *buf, const char *fmt, va_list args) {
  const char *str = buf;
  char *next;
  char digit;
  int num = 0;
  uint8_t qualifier;
  uint8_t base;
  int16_t fieldWidth;
  int isSign;

  while (*fmt && *str) {
    if (isspace(*fmt)) {
      fmt = _skipSpaces(++fmt);
      str = _skipSpaces(str);
    }

    if (*fmt != '%' && *fmt) {
      if (*fmt++ != *str++) break;
      continue;
    }

    if (!*fmt) break;
    ++fmt;

    if (*fmt == '*') {
      while (!isspace(*fmt) && *fmt != '%' && *fmt) fmt++;
      while (!isspace(*str) && *str) str++;
      continue;
    }

    fieldWidth = -1;
    if (isdigit(*fmt)) fieldWidth = _skipAtoi(&fmt);

    qualifier = -1;
    if (*fmt == 'h' || tolower(*fmt) == 'l' || tolower(*fmt) == 'z') {
      qualifier = *fmt++;
      if (qualifier == *fmt) {
        if (qualifier == 'h') {
          qualifier = 'H';
          fmt++;
        } else if (qualifier == 'l') {
          qualifier = 'L';
          fmt++;
        }
      }
    }

    if (!*fmt || !*str) break;

    base = 10;
    isSign = 0;

    switch (*fmt++) {
      case 'c': {
        char *s = (char *)va_arg(args, char *);
        if (fieldWidth == -1) fieldWidth = 1;
        do {
          *s++ = *str++;
        } while (--fieldWidth > 0 && *str);
        num++;
      }
        continue;
      case 's': {
        char *s = (char *)va_arg(args, char *);
        if (fieldWidth == -1) fieldWidth = __SHRT_MAX__;
        str = _skipSpaces(str);
        while (*str && !isspace(*str) && fieldWidth--) *s++ = *str++;
        *s = '\0';
        num++;
      }
        continue;
      case 'n': {
        int *i = (int *)va_arg(args, int *);
        *i = str - buf;
      }
        continue;
      case 'o':
        base = 8;
        break;
      case 'x':
      case 'X':
        base = 16;
        break;
      case 'i':
        base = 0;
      case 'd':
        isSign = 1;
      case 'u':
        break;
      case '%':
        if (*str++ != '%') return num;
        continue;
      default:
        return num;
    }

    str = _skipSpaces(str);

    digit = *str;
    if (isSign && digit == '-') digit = *(str + 1);

    if (!digit || (base == 16 && !isxdigit(digit)) ||
        (base == 10 && !isdigit(digit)) ||
        (base == 8 && (!isdigit(digit) || digit > '7')) ||
        (base == 0 && !isdigit(digit)))
      break;

    switch (qualifier) {
      case 'H':
        if (isSign) {
          signed char *s = (signed char *)va_arg(args, signed char *);
          *s = (signed char)strtol(str, &next, base);
        } else {
          unsigned char *s = (unsigned char *)va_arg(args, unsigned char *);
          *s = (unsigned char)strtoul(str, &next, base);
        }
        break;
      case 'h':
        if (isSign) {
          short *s = (short *)va_arg(args, short *);
          *s = (short)strtol(str, &next, base);
        } else {
          unsigned short *s = (unsigned short *)va_arg(args, unsigned short *);
          *s = (unsigned short)strtoul(str, &next, base);
        }
        break;
      case 'l':
        if (isSign) {
          long *l = (long *)va_arg(args, long *);
          *l = strtol(str, &next, base);
        } else {
          unsigned long *l = (unsigned long *)va_arg(args, unsigned long *);
          *l = strtoul(str, &next, base);
        }
        break;
#if USE_LONGLONG == 1
      case 'L':
        if (isSign) {
          long long *l = (long long *)va_arg(args, long long *);
          *l = simple_strtoll(str, &next, base);
        } else {
          unsigned long long *l =
              (unsigned long long *)va_arg(args, unsigned long long *);
          *l = simple_strtoull(str, &next, base);
        }
        break;
#endif
      case 'Z':
      case 'z': {
        size_t *s = (size_t *)va_arg(args, size_t *);
        *s = (size_t)strtoul(str, &next, base);
      } break;
      default:
        if (isSign) {
          int *i = (int *)va_arg(args, int *);
          *i = (int)strtol(str, &next, base);
        } else {
          unsigned int *i = (unsigned int *)va_arg(args, unsigned int *);
          *i = (unsigned int)strtoul(str, &next, base);
        }
        break;
    }
    num++;

    if (!next) break;
    str = next;
  }

  if (*fmt == '%' && *(fmt + 1) == 'n') {
    int *p = (int *)va_arg(args, int *);
    *p = str - buf;
  }

  return num;
}

int sscanf(const char *buf, const char *fmt, ...) {
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsscanf(buf, fmt, args);
  va_end(args);

  return i;
}

int scanf(const char *fmt, ...) {
  char line[BUFFER_SIZE];
  va_list args;
  int i = 0;
  char ch = 0;
  while (ch != '\r') {
    ch = getc(&__stdin);
    if (isprint(ch)) line[i++] = ch;
  }
  line[i++] = 0;

  va_start(args, fmt);
  i = vsscanf(line, fmt, args);
  va_end(args);

  return i;
}