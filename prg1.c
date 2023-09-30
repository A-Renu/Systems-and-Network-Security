#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void findCommonDivisors(mpz_t *numbers, int n) {
    mpz_t gcd, div;
    mpz_init(gcd);
    mpz_init(div);

    // Find the GCD of the first two numbers
    mpz_gcd(gcd, numbers[0], numbers[1]);

    // Find the GCD of the remaining numbers with the previously calculated GCD
    for (int i = 2; i < n; i++) {
        mpz_gcd(div, gcd, numbers[i]);
        mpz_set(gcd, div);
    }

    mpz_t divisor;
    mpz_init(divisor);

    printf("Common divisors: ");
    for (mpz_set_ui(divisor, 1); mpz_cmp(divisor, gcd_result) <= 0; mpz_add_ui(divisor, divisor, 1)) {
        if (mpz_divisible_p(gcd_result, divisor)) {
            gmp_printf("%Zd ", divisor);
        }
    }
    printf("\n");

    mpz_clear(gcd_result);
    mpz_clear(divisor);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <integer1> <integer2> ... <integerN>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    mpz_t *numbers = (mpz_t *)malloc(n * sizeof(mpz_t));
    
    for (int i = 0; i < n; i++) {
        mpz_init(numbers[i]);
        mpz_set_str(numbers[i], argv[i + 1], 10);
    }

    findCommonDivisors(numbers, n);

    for (int i = 0; i < n; i++) {
        mpz_clear(numbers[i]);
    }
    free(numbers);

    return 0;
}

