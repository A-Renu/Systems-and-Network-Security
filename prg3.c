#include <stdio.h>
#include <gmp.h>

void primeFactorization(mpz_t n) {
    mpz_t num, divisor, remainder;
    mpz_inits(num, divisor, remainder, NULL);

    mpz_set(num, n); // Make a copy of the input number

    printf("Prime factorization of ");
    gmp_printf("%Zd", n);
    printf(": ");

    int isFirst = 1; // Flag to handle comma formatting

    // Find and print prime factors
    for (mpz_set_ui(divisor, 2); mpz_cmp_ui(num, 1) > 0; mpz_nextprime(divisor, divisor)) {
        mpz_fdiv_r(remainder, num, divisor);
        if (mpz_cmp_ui(remainder, 0) == 0) {
            while (mpz_cmp_ui(remainder, 0) == 0) {
                if (!isFirst) {
                    printf(" * ");
                }
                isFirst = 0;
                gmp_printf("%Zd", divisor);
                mpz_fdiv_q(num, num, divisor);
                mpz_fdiv_r(remainder, num, divisor);
            }
        }
    }

    printf("\n");

    mpz_clears(num, divisor, remainder, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    mpz_t n;
    mpz_init(n);

    mpz_set_str(n, argv[1], 10);

    primeFactorization(n);

    mpz_clear(n);

    return 0;
}






