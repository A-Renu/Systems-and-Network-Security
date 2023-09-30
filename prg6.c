#include <stdio.h>
#include <gmp.h>

void extendedGCD(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t gcd) {
    if (mpz_cmp_ui(a, 0) == 0) {
        mpz_set_ui(x, 0);
        mpz_set_ui(y, 1);
        mpz_set(gcd, b);
        return;
    }

    mpz_t x1, y1;
    mpz_inits(x1, y1, NULL);

    mpz_mod(x1, b, a);
    mpz_mod(y1, a, b);

    mpz_t x0, y0;
    mpz_inits(x0, y0, NULL);

    extendedGCD(x1, a, x0, y0, gcd);

    mpz_t temp;
    mpz_init(temp);

    mpz_fdiv_q(temp, b, a);

    mpz_mul(x1, temp, x0);
    mpz_sub(x, y0, x1);

    mpz_set(y, x0);

    mpz_clears(x0, y0, x1, y1, temp, NULL);
}

void Inverse(const mpz_t a, const mpz_t m) {
    mpz_t x, y, gcd, inverse;
    mpz_inits(x, y, gcd, inverse, NULL);

    extendedGCD(a, m, x, y, gcd);

    if (mpz_cmp_ui(gcd, 1) != 0) {
        printf("Modular inverse does not exist.\n");
        mpz_clears(x, y, gcd, NULL);
    } else {
        mpz_set(inverse, x);
        if (mpz_cmp_ui(inverse, 0) < 0) {
            mpz_add(inverse, inverse, m);
        }
        gmp_printf("Modular inverse of %Zd mod %Zd is: %Zd\n", a, m, inverse);
    }

    mpz_clears(x, y, gcd, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <a> <m>\n", argv[0]);
        return 1;
    }

    mpz_t a, m;
    mpz_init(a);
    mpz_init(m);

    // Set values of a and m from command-line arguments
    mpz_set_str(a, argv[1], 10);
    mpz_set_str(m, argv[2], 10);

    Inverse(a, m);

    mpz_clears(a, m, NULL);

    return 0;
}
