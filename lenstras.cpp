#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <climits>
#include <random>
#include <chrono>
#include <iostream>
#include "Point.h"

void get_new_input(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t n, mpz_t max) {
	std::random_device rand_dev;
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, rand_dev());
	mpz_t temp;
	mpz_init(temp);
	
	//Set a, x, y to random number in [0, n-1]
	mpz_urandomm(a, state, max);
	mpz_urandomm(x, state, max);
	mpz_urandomm(y, state, max);

	
	//b = y^2 - x^3 - a*x (mod n)
	mpz_pow_ui(b, y, 2);
	mpz_pow_ui(temp, x, 3);
	mpz_sub(b, b, temp);
	mpz_mul(temp, a, x);
	mpz_sub(b, b, temp);
	my_mpz_mod(b, n);
	
	mpz_clear(temp);
}

void lenstras(mpz_t n, mpz_t max) {
	mpz_t f1, f2;
	mpz_init(f1); mpz_init(f2);
	int bound = 3, reps = 0;
	mpz_t a, b, x, y;
	mpz_init(a); mpz_init(b); mpz_init(x); mpz_init(y); 
	
	while (++reps <= bound) {
		get_new_input(a, b, x, y, n, max);
		Point p(x, y, a, n);
		
		printf("\nEquation: y^2 = x^3 + ");
		mpz_out_str(stdout, 10, p.a);
		printf("x + ");
		mpz_out_str(stdout, 10, b);
		printf(" (mod ");
		mpz_out_str(stdout, 10, p.p);
		printf(")\n");
		printf("Point:  ");
		p.print();
		
		mpz_pow_ui(f1, a, 3);
		mpz_mul_ui(f1, f1, 4);
		mpz_pow_ui(f2, b, 2);
		mpz_mul_ui(f2, f2, 27);
		mpz_add(f1, f1, f2); //Find discriminant
		mpz_gcd(f1, f1, n);
		//if gcd(discriminant, n) > 1 && is a non-trivial factor
		if (mpz_cmp_si(f1, 1) > 0 && mpz_cmp(f1, n) == 0) {
			mpz_tdiv_q(f2, n, f1);
			printf("n = ");
			mpz_out_str(stdout, 10, f1);
			printf(" * ");
			mpz_out_str(stdout, 10, f2);
			printf("\n");
			break;
		}
		
		if (p.multiply(10) < 0) {
			if (mpz_cmp(p.p, p.factor1) == 0)	//check for non-trivial factor
				continue;
			printf("n = ");
			mpz_out_str(stdout, 10, p.factor1);
			printf(" * ");
			mpz_out_str(stdout, 10, p.factor2);
			printf("\n");
			break;
		}
		p.print();
	}
	mpz_clear(f1);
	mpz_clear(f2);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Incorrect number of arguments!  Run program as follows:\n");
		printf("./lenstras <number_to_be_factored>");
		return -1;
	}
	mpz_t n, max;
	mpz_init_set_str(n, argv[1], 10);
	if (mpz_cmp_si(n, 2) < 0) {
		printf("Input is less than 2!");
		return -1;
	}
	mpz_init_set(max, n);
	mpz_sub_ui(max, max, 1);
	
	lenstras(n, max);
	
	return 0;
}
