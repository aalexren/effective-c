#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

static uint counter = 0;

void increment(void) {
    counter++;
}

uint retrieve(void) {
    return counter;
}

int main() {
    for (int i = 0; i < 5; i++) {
        increment();
        uint value = retrieve();
        printf("%d\n", value);
    }

    return EXIT_SUCCESS;
}
