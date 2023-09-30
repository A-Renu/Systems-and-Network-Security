#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>

void reduced_residue_system(mpz_t m) {
    mpz_t num, gcd_result;
    mpz_init(num);
    mpz_init(gcd_result);

    int count = 0; // Counter for the reduced residue numbers
    bool isfirst = 1;

    // Print header
    printf("Reduced Residue System modulo ");
    mpz_out_str(stdout, 10, m);
    printf(":\n");

    printf("{ ");
    // Iterate through numbers from 1 to m-1
    for (mpz_set_ui(num, 1); mpz_cmp(num, m) < 0; mpz_add_ui(num, num, 1)) {
        mpz_gcd(gcd_result, num, m);
        if (mpz_cmp_ui(gcd_result, 1) == 0) {
            if(!isfirst)
            {
                printf(", ");
            }
            mpz_out_str(stdout, 10, num);
            isfirst = 0;
            count++;
        }
    }
    printf("}\n");

    printf("Count of numbers in reduced residue system: %d\n", count);

    mpz_clear(num);
    mpz_clear(gcd_result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <m>\n", argv[0]);
        return 1;
    }

    mpz_t m;
    mpz_init(m);
    mpz_set_str(m, argv[1], 10);

    reduced_residue_system(m);

    mpz_clear(m);

    return 0;
}

