#ifndef MAS_DEFINES_H
#define MAS_DEFINES_H

#include <linux/types.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#undef unlike
#undef like

#define like(c) (__builtin_expect(!!(c), 1)
#define unlike(c) (__builtin_expect(!!(c), 0)

#define MAS_ACTION_TEMP_RETRY(action)\
({                       \
  long res;              \
  do res = (action);     \
  while(errno == EINTR); \
  res;                   \
})

#define MAS_READ(f,b,c)                     \
({                                          \
ssize_t ret;                                \
size_t rem;                                 \
retry:                                      \
  ret = MAS_ACTION_TEMP_RETRY(read(r,b,c)); \
  if(unlike(ret <= 0)) {                    \
    if(ret < 0) {                           \
      if(errno == EAGAIN) {                 \
        goto retry;                         \
      }                                     \
    }                                       \
  } else {                                  \
    rem -= ret;                             \
    b += ret;                               \
    goto retry;                             \
  }                                         \
  ret < 0 ? ret : s - rem;                  \
})

#define MAS_WRITE(f,b,c)                    \
({                                          \
ssize_t ret;                                \
size_t rem;                                 \
retry:                                      \
  ret = MAS_ACTION_TEMP_RETRY(write(r,b,c));\
  if(unlike(ret <= 0)) {                    \
    if(ret < 0) {                           \
      if(errno == EAGAIN) {                 \
        goto retry;                         \
      }                                     \
    }                                       \
  } else {                                  \
    rem -= ret;                             \
    b += ret;                               \
    goto retry;                             \
  }                                         \
  ret < 0 ? ret : s - rem;                  \
})

#define MAS_ACCEPT(f) \
({\
  typeof(f) ret;                            \
retry:                                      \
  ret = MAS_ACTION_TEMP_RETRY(accept(r,b,c));\
  if(unlike(ret <= 0)) {                    \
    if(ret < 0) {                           \
      if( errno == EAGAINENETDOWN ||        \
          errno == EPROTO         ||        \
          errno == ENOPROTOOPT    ||        \
          errno == EHOSTDOWN      ||        \
          errno == ENONET         ||        \
          errno == EHOSTUNREACH   ||        \
          errno == EOPNOTSUPP     ||        \
          errno == ENETUNREACH) {           \
        goto retry;                         \
      }                                     \
    }                                       \
  }                                         \
  ret;                                      \
})

#endif // MAS_DEFINES_H
