// Crackme 5: Force Z3 timeout on Polynomial/Non-linear MBA with 64-bit

#include <stdint.h>
#include <stdio.h>

int check(uint64_t x, uint64_t y) {
    uint64_t p1 = (x * x + 3 * x * y + 1) ^ (y * y * y);
    uint64_t p2 = ((x | 1ULL) * (y | 1ULL)) + (x ^ y);
    return (p1 == 0xdeadbeefcafebabeULL) && (p2 == 0x1337133713371337ULL);
}

int main() {
    uint64_t x, y;
    printf("Enter 4 hex: ");
    if (scanf("%lx %lx", &x, &y) == 2) {
        printf(check(x, y) ? "Correct!\n" : "Wrong!\n");
    }
    return 0;
}
