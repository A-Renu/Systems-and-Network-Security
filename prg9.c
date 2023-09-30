#include <stdio.h>
#include <gmp.h>

int check_order_exists(mpz_t a, mpz_t m) {
    mpz_t gcd;
    mpz_init(gcd);

    // Calculate the greatest common divisor of a and m
    mpz_gcd(gcd, a, m);

    int exists = mpz_cmp_ui(gcd, 1) == 0;

    mpz_clear(gcd);
    return exists;
}

void find_order(mpz_t a, mpz_t m) {
    if (!check_order_exists(a, m)) {
        gmp_printf("Order doesn't exist because gcd(%Zd, %Zd) != 1\n", a, m);
        return;
    }

    mpz_t order, result;
    mpz_init(order);
    mpz_init(result);

    // Initialize the order
    mpz_set_ui(order, 1);

    // Iterate to find the order
    while (1) {
        mpz_powm(result, a, order, m);
        if (mpz_cmp_ui(result, 1) == 0) {
            break;
        }
        mpz_add_ui(order, order, 1);
    }

    // Print the order
    gmp_printf("Order of %Zd modulo %Zd is %Zd\n", a, m, order);

    mpz_clear(order);
    mpz_clear(result);
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

    // Find and print the order
    find_order(a, m);

    mpz_clear(a);
    mpz_clear(m);

    return 0;
}

