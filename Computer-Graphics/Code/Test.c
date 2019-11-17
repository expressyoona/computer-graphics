#include <stdio.h>

void b() {
    a();
}

void a() {
    printf("Method A\n");
}

int main() {
    b();
}