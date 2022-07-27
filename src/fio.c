#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define STDIN_ECHO 1
#define STDOUT_CR_LF 1
#define STDERR_CR_LF 1

struct __FILE {
  int dummyVar;
};

extern int Retarget_putChar(int ch);
extern int Retarget_getChar();

FILE __stdout;
FILE __stdin;
FILE __stderr;

static int _getCharUndo = 0;
static int _getCharCh = -1;

int fputc(int c, FILE *stream) {
  (void)stream;
  unsigned char ch = c;
#if (STDOUT_CR_LF != 0)
  if (c == '\n') Retarget_putChar('\r');
#endif
  Retarget_putChar(ch);
  return ch;
}

int fgetc(FILE *stream) {
  (void)stream;
  int ch = 0;
  if (_getCharUndo) {
#ifdef __MICROLIB
    ch = _getCharCh;
#else
    ch = EOF;
#endif
    _getCharCh = -1;
    _getCharUndo = 0;
    return ch;
  }
  ch = Retarget_getChar();
  Retarget_putChar(ch);
  if (ch == '\r') Retarget_putChar('\n');
  _getCharCh = ch;
  return ch;
}

int __backspace(FILE *stream);
int __backspace(FILE *stream) {
  if (_getCharCh != EOF) {
    _getCharUndo = 1;
    return 0;
  }
  return EOF;
}