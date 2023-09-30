#include <stdio.h>
#include <gmp.h>

void congruence_solution(const mpz_t a, const mpz_t b, const mpz_t m) {
    mpz_t g, a1, b1, u1, multiplicative_inverse_a1, first_solution, solution_count;
    mpz_inits(g, a1, b1, u1, multiplicative_inverse_a1, first_solution, solution_count, NULL);

    mpz_gcd(g, a, m);
    mpz_divexact(a1, a, g);
    mpz_divexact(b1, b, g);
    mpz_divexact(u1, m, g);

    if (mpz_divisible_p(b, g)) {
        mpz_invert(multiplicative_inverse_a1, a1, u1);

        mpz_mul(first_solution, multiplicative_inverse_a1, b1);
        mpz_mod(first_solution, first_solution, u1);

        mpz_set_ui(solution_count, mpz_get_ui(g));

        gmp_printf("Solution exists (Number of solutions: %Zd)\n", solution_count);
        gmp_printf("Solutions:\n");
        mpz_t solution;
        mpz_t mulsolution;
        mpz_init(solution);
        mpz_init(mulsolution);
        for (unsigned long i = 0; i < mpz_get_ui(solution_count); ++i) {
            mpz_mul_ui(mulsolution, u1, i);
            mpz_add(solution, mulsolution, first_solution);
            mpz_mod(solution, solution, m);
            if (mpz_cmp(solution, m) < 0) {
                gmp_printf("%Zd\n", solution);
            }
        }
        mpz_clear(solution);
    } else {
        gmp_printf("No solution exists.\n");
    }

    mpz_clears(g, a1, b1, u1, multiplicative_inverse_a1, first_solution, solution_count, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <value_a> <value_b> <value_m>\n", argv[0]);
        return 1;
    }

    mpz_t a, b, m;
    mpz_inits(a, b, m, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(b, argv[2], 10);
    mpz_set_str(m, argv[3], 10);

    congruence_solution(a, b, m);

    mpz_clears(a, b, m, NULL);

    return 0;
}

