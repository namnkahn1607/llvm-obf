// Crackme 3: 32-bit integer overflow

#include <stdint.h>
#include <stdio.h>

int check(uint32_t x) { return (x * 0x13371337U) == 0xdeadbeefU; }

int main() {
    uint32_t x;
    printf("Enter a hex: ");
    scanf("%x", &x);
    printf(check(x) ? "Correct!\n" : "Wrong!\n");
    return 0;
}
