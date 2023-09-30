#include <stdio.h>
#include <gmp.h>

void extendedGCD(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t gcd) {
    if (mpz_cmp_ui(a, 0) == 0) {
        mpz_set_ui(x, 0);
        mpz_set_ui(y, 1);
        mpz_set(gcd, b);
        return;
    }

    mpz_t x1;
    mpz_inits(x1, NULL);

    mpz_mod(x1, b, a);

    mpz_t x0, y0;
    mpz_inits(x0, y0, NULL);

    extendedGCD(x1, a, x0, y0, gcd);

    mpz_t temp;
    mpz_init(temp);

    mpz_fdiv_q(temp, b, a);

    mpz_mul(x1, temp, x0);
    mpz_sub(x, y0, x1);

    mpz_set(y, x0);

    mpz_clears(x0, y0, x1, temp, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <value_a> <value_b>\n", argv[0]);
        return 1;
    }

    mpz_t a, b, x, y, gcd;
    mpz_inits(a, b, x, y, gcd, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(b, argv[2], 10);

    extendedGCD(a, b, x, y, gcd);

    gmp_printf(" GCD: %Zd\n", gcd);
    gmp_printf("Coefficients x and y: %Zd %Zd\n", x, y);

    mpz_clears(a, b, x, y, gcd, NULL);

    return 0;
}



