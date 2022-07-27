#ifndef POSIX_SIGNAL_H
#define POSIX_SIGNAL_H

#define SIGEV_NONE 0
#define SIGEV_SIGNAL 1 // Not supported
#define SIGEV_THREAD 2

union sigval {
  int sival_int;
  void *sival_ptr;
};

struct sigevent {
  int sigev_notify;
  int sigev_signo; // ignored
  union sigval sigev_value;
  void (*sigev_notify_function)(union sigval);
  void *sigev_notify_attributes;
};

#endif // POSIX_SIGNAL_H
