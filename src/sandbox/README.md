Przykład zmiennych statycznych - pozwalający lepiej zrozumieć widoczność zmiennych zadeklarowanych ze słowem `static`.

```c
#include <stdio.h>

// This is the file-scope variable (with internal linkage), visible only in
// this compilation unit.
static int shared = 3;

// This one has external linkage (not limited to this compilation unit).
extern int over_shared;

// Also internal linkage.
int over_shared_too = 2;

static void ChangeShared() {
  // Reference to the file-scope variable in a function.
  shared = 5;
}

static void LocalShadow() {
  // Local variable that will hide the global of the same name.
  int shared;

  // This will affect only the local variable and will have no effect on the
  // file-scope variable of the same name.
  shared = 1000;
}

static void ParamShadow(int shared) {
  // This will affect only the parameter and will have no effect on the file-
  // scope variable of the same name.
  shared = -shared;
}

int main() {
  // Reference to the file-scope variable.

  printf("%d\n", shared);

  ChangeShared();

  printf("%d\n", shared);

  LocalShadow();

  printf("%d\n", shared);

  ParamShadow(1);

  printf("%d\n", shared);

  return 0;
}
```
