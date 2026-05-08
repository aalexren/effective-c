#include <stdio.h>
#include <stdlib.h>

typedef void (*fp)(void);

void a(void) {
    puts("a function has been invoked!");
}

void b(void) {
    puts("b function has been invoked!");
}

void c(void) {
    puts("c function has been invoked!");
}

int main() {
    void (*funcs[3])(void) = {&a, &b, &c};
    // void (*funcs[3])(void) = {a, b, c};
    // fp funcs[3] = {a, b, c};

    for (int i = 0; i < 3; i++) {
        funcs[i]();
    }
    
    return EXIT_SUCCESS;
}