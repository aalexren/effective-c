#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf buf;

int main() {
    int volatile foo = 5;
    if (setjmp(buf) != 2) {
        if (foo != 5) {
            puts("hi"); longjmp(buf, 2);
        }
        foo = 6;
        longjmp(buf, 1);
    }
    return EXIT_SUCCESS;
}