#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <climits>
#include <random>
#include <chrono>
#include <iostream>
#include "Point.h"

void lenstras(Point& p, mpz_t b) {
	printf("Equation: y^2 = x^3 + ");
	mpz_out_str(stdout, 10, p.a);
	printf("x + ");
	mpz_out_str(stdout, 10, b);
	printf(" (mod ");
	mpz_out_str(stdout, 10, p.p);
	printf(")\n");
	printf("Point:  ");
	p.print();
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Incorrect number of arguments!  Run program as follows:\n");
		printf("./lenstras <number_to_be_factored>");
		return -1;
	}
	mpz_t n, a, b, x, y, max, temp;
	mpz_init_set_str(n, argv[1], 10);
	if (mpz_cmp_si(n, 2) < 0) {
		printf("Input is less than 2!");
		return -1;
	}
	mpz_init_set(max, n);
	mpz_sub_ui(max, max, 1);
	mpz_init(a); mpz_init(b); mpz_init(x); mpz_init(y); mpz_init(temp);
	
	std::random_device rand_dev;
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, rand_dev());
	
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
	
	Point p(x, y, a, n);
	lenstras(p, b);
	
	return 0;
}
