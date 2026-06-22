#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b) {
    return a / b;
}

int main() {
    int x = 10;
    int y = 0;

    printf("Debug demo program\n");
    printf("x = %d, y = %d\n", x, y);

    int result = divide(x, y);

    printf("Result = %d\n", result);
    return 0;
}
