#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void extendedEuclidean(mpz_t a, mpz_t b, mpz_t x, mpz_t y) {
    mpz_t temp, quotient, remainder, x1, y1, x2, y2;
    mpz_inits(temp, quotient, remainder, x1, y1, x2, y2, NULL);
    
    mpz_set_ui(x1, 1);
    mpz_set_ui(y1, 0);
    mpz_set_ui(x2, 0);
    mpz_set_ui(y2, 1);

    while (mpz_cmp_ui(b, 0) > 0) {
        mpz_div(quotient, a, b);
        mpz_set(temp, b);
        mpz_mod(b, a, b);
        mpz_set(a, temp);
        
        mpz_set(temp, x2);
        mpz_mul(x2, quotient, x2);
        mpz_sub(x2, x1, x2);
        mpz_set(x1, temp);
        
        mpz_set(temp, y2);
        mpz_mul(y2, quotient, y2);
        mpz_sub(y2, y1, y2);
        mpz_set(y1, temp);
    }

    mpz_set(x, x1);
    mpz_set(y, y1);

    mpz_clears(temp, quotient, remainder, x1, y1, x2, y2, NULL);
}

int areRelativelyPrime(mpz_t *m, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            mpz_t gcd;
            mpz_init(gcd);
            mpz_gcd(gcd, m[i], m[j]);
            if (mpz_cmp_ui(gcd, 1) != 0) {
                mpz_clear(gcd);
                return 0;
            }
            mpz_clear(gcd);
        }
    }
    return 1;
}

int crt(mpz_t *a, mpz_t *b, mpz_t *m, int n, mpz_t result) {

    if (!areRelativelyPrime(m, n)) {
        return 0;
    }
    
    mpz_t M, x, y, t1, t2;
    mpz_inits(M, x, y, t1, t2, NULL);

    mpz_set_ui(result, 0);
    mpz_set_ui(M, 1);

    // Calculate the product of all moduli
    for (int i = 0; i < n; i++) {
        mpz_mul(M, M, m[i]);
    }

    for (int i = 0; i < n; i++) {
        mpz_divexact(y, M, m[i]);
        mpz_set(t1,y);
        extendedEuclidean(y, m[i], x, t2);
        mpz_mul(x, x, t1);
        mpz_mul(x, x, b[i]);

        mpz_add(result, result, x);
        mpz_mod(result, result, M);
    }

    mpz_clears(M, x, y, NULL);

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc % 3 != 1) {
        printf("Usage: %s <a1> <b1> <m1> <a2> <b2> <m2> ... <an> <bn> <mn>\n", argv[0]);
        return 1;
    }

    int n = (argc - 1) / 3;
    mpz_t a[n], b[n], m[n], result;
    
    mpz_init(result);

    for (int i = 0; i < n; i++) {
        mpz_inits(a[i], b[i], m[i], NULL);
        mpz_set_str(a[i], argv[i * 3 + 1], 10);
        mpz_set_str(b[i], argv[i * 3 + 2], 10);
        mpz_set_str(m[i], argv[i * 3 + 3], 10);
    }

    if (crt(a, b, m, n, result)) {
        gmp_printf("Solution exists (Y)\nCommon solution x: %Zd\n", result);
    } else {
        printf("Solution does not exist (N)\n");
    }

    for (int i = 0; i < n; i++) {
        mpz_clears(a[i], b[i], m[i], NULL);
    }
    
    mpz_clear(result);

    return 0;
}

