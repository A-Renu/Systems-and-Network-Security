#include <stdio.h>
#include <gmp.h>

void power_mod(const mpz_t a, const mpz_t x, const mpz_t n, mpz_t result) {
    mpz_t base;
    mpz_init(base);
    mpz_set(base, a);

    mpz_t exp;
    mpz_init(exp);
    mpz_set(exp, x);

    mpz_t mod;
    mpz_init(mod);
    mpz_set(mod, n);

    mpz_t result_tmp;
    mpz_init(result_tmp);
    mpz_set_ui(result_tmp, 1);

    mpz_t p_minus_1;
    mpz_init(p_minus_1);
    mpz_sub_ui(p_minus_1, mod, 1); // p - 1

    mpz_t exp_mod;
    mpz_init(exp_mod);
    mpz_mod(exp_mod, exp, p_minus_1); // x mod (p - 1)

    mpz_t remainder;
    mpz_init(remainder);
    mpz_fdiv_r(remainder, a, mod);

    if (mpz_cmp_ui(remainder, 0) == 0) {
        mpz_set_ui(result_tmp, 0);
        mpz_set_ui(exp_mod, 0);
    }

    while (mpz_cmp_ui(exp_mod, 0) > 0) {
        if (mpz_odd_p(exp_mod)) {
            mpz_mul(result_tmp, result_tmp, base);
            mpz_mod(result_tmp, result_tmp, mod);
        }

        mpz_mul(base, base, base);
        mpz_mod(base, base, mod);

        mpz_fdiv_q_ui(exp_mod, exp_mod, 2);
    }

    mpz_set(result, result_tmp);

    mpz_clear(base);
    mpz_clear(exp);
    mpz_clear(mod);
    mpz_clear(result_tmp);
    mpz_clear(p_minus_1);
    mpz_clear(exp_mod);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <value_a> <value_x> <value_n>\n", argv[0]);
        return 1;
    }

    mpz_t a, x, n, result;
    mpz_inits(a, x, n, result, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(x, argv[2], 10);
    mpz_set_str(n, argv[3], 10);

    power_mod(a, x, n, result);

    gmp_printf("%Zd ^ %Zd equiv %Zd (mod %Zd)\n", a, x, result, n);

    mpz_clears(a, x, n, result, NULL);

    return 0;
}

