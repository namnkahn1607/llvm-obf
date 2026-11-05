// Crackme 4: Try linear MBA - Substitute x + y with (x ^ y) + 2*(x & y)

#include <stdint.h>
#include <stdio.h>

int check(uint32_t x, uint32_t y) {
    uint32_t mba1 = (x ^ y) + 2 * (x & y);
    uint32_t mba2 = (x | y) + (x & y);
    return (mba1 == 0x12345678U) && ((mba2 ^ x) == 0x9abcdef0U);
}

int main() {
    uint32_t x, y;
    printf("Enter 2 hex: ");
    if (scanf("%x %x", &x, &y) == 2) {
        printf(check(x, y) ? "Correct!\n" : "Wrong!\n");
    }
    return 0;
}
