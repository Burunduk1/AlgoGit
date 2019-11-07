#include <cstdio>
#include <cstdarg>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

struct Finalize {
  char *s;
  Finalize( const char *fmt, ... ) {
    s = new char[999];
    va_list list;
    va_start(list, fmt);
    vsprintf(s, fmt, list);
    err(s), err(" [begin]\n");
  }
  ~Finalize() {
    err(s), err(" [end]\n");
  }
};

// Пример использования. Дебаг вывод точки входа и точки выхода из функции f(x)
int f( int x ) {
  Finalize _("f: x = %d", x);
  if (x == 1)
    return 1; // call ~Finalize
  return 2; // call ~Finalize
}
