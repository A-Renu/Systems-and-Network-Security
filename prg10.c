#include <stdio.h>
#include <gmp.h>

int gcd_check(mpz_t a, mpz_t m) {
    mpz_t gcd_result;
    mpz_init(gcd_result);
    mpz_gcd(gcd_result, a, m);

    int result = mpz_cmp_ui(gcd_result, 1) == 0;

    mpz_clear(gcd_result);
    return result;
}

unsigned int calculate_phi(mpz_t m) {
    unsigned int phi = 0;

    mpz_t num;
    mpz_init(num);

    for (mpz_set_ui(num, 1); mpz_cmp(num, m) < 0; mpz_add_ui(num, num, 1)) {
        if (gcd_check(num, m)) {
            phi++;
        }
    }

    mpz_clear(num);
    return phi;
}

int calculateOrder(mpz_t a, mpz_t m) {
    mpz_t order, result;
    mpz_init(order);
    mpz_init(result);

    mpz_set_ui(order, 1);
    mpz_set(result, a);

    while (mpz_cmp_ui(result, 1) != 0) {
        mpz_mul(result, result, a);
        mpz_mod(result, result, m);
        mpz_add_ui(order, order, 1);

        if (mpz_cmp(order, m) >= 0) {
            mpz_clear(order);
            mpz_clear(result);
            return -1; // Order does not exist within modulo m
        }
    }

    int order_int = mpz_get_si(order);
    mpz_clear(order);
    mpz_clear(result);
    return order_int;
}

void find_primitive_roots(mpz_t m) {
    unsigned int phi_m = calculate_phi(m);

    mpz_t count;
    mpz_init(count);

    mpz_set_ui(count, 0);
    gmp_printf("Primitive Roots of %Zd: {", m);
    int first_element = 1;

    mpz_t a;
    mpz_init(a);
    for (mpz_set_ui(a, 2); mpz_cmp(a, m) < 0; mpz_add_ui(a, a, 1)) {
        if (gcd_check(a, m) && calculateOrder(a, m) == phi_m) {
            if (!first_element) {
                printf(", ");
            }
            gmp_printf("%Zd", a);
            mpz_add_ui(count, count, 1);
            first_element = 0;
        }
    }
    mpz_clear(a);

    printf("}\n");
    gmp_printf("Total number of primitive roots of %Zd: %Zd\n", m, count);

    mpz_clear(count);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <value_m>\n", argv[0]);
        return 1;
    }

    mpz_t m;
    mpz_init(m);

    mpz_set_str(m, argv[1], 10);

    if (mpz_cmp_ui(m, 2) < 0) {
        printf("Please enter an integer greater than or equal to 2.\n");
    } else {
        find_primitive_roots(m);
    }

    mpz_clear(m);

    return 0;
}

