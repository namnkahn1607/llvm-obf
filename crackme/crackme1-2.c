// Crackme 1 & 2: System of linear equations in 4 variables

#include <stdint.h>
#include <stdio.h>

int check(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    if (a + b == 0x11223344 && (b ^ c) == 0x55667788 && c - d == 0x99aabbcc &&
        (d ^ a) + c == 0xdeadbeef) {
        return 1;
    }
    return 0;
}

int main() {
    uint32_t a, b, c, d;
    printf("Enter 4 hex: ");
    if (scanf("%x %x %x %x", &a, &b, &c, &d) == 4) {
        printf(check(a, b, c, d) ? "Correct!\n" : "Wrong!\n");
    }
    return 0;
}
