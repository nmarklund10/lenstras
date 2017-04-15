#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <climits>
#include <random>
#include <chrono>
#include <iostream>
#include "Point.h"

std::random_device rand_dev;
gmp_randstate_t state;
std::vector<int> primes;
std::vector<std::string> output;
mpz_t temp;

void get_primes_less_than(const int& limit, std::vector<int>& table) {
	//erathosthen_sieve to get all primes less than limit
	//use to calculate lcm of all integers less than limit
	std::vector<bool> is_prime(limit, true);
	is_prime[0] = false;
	is_prime[1] = false;
	for (int i = 2; i < limit; ++i) {
		if (is_prime[i]) {
			table.push_back(i);
			for (int j = i; j < limit; j += i) {
				is_prime[j] = false;
			}
		}
	}
}

void get_new_input(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t n, mpz_t max) {
	//Set a, x, y to random number in [0, n-1]
	mpz_urandomm(a, state, max);
	mpz_urandomm(x, state, max);
	mpz_urandomm(y, state, max);
}

int lenstras(mpz_t n, mpz_t max) {
	if (mpz_cmp_si(n, 2) == 0) {
		output.push_back(std::string("2"));
		return 0;
	}
	int bound = 5, reps = 0;
	mpz_t a, b, x, y;
	mpz_init(a); mpz_init(b); mpz_init(x); mpz_init(y);
	mpz_set_si(temp, 1);
	mpz_and(temp, n, temp);
	if ((mpz_cmp_si(temp, 0) == 0)) {
		mpz_tdiv_q_ui(a, n, 2);
		output.push_back(std::string("2"));
		lenstras(a, max);
		return 0;
	}
	
	while (++reps <= bound) {
		get_new_input(a, b, x, y, n, max);
		Point p(x, y, a, n);
		
		//Lenstra's, calculate up to lcm of (limit)! * P
		for (auto it = primes.begin(); it != primes.end(); ++it) {
			//Addition failed
			if (p.multiply(*it) < 0) {
				//check for non-trivial factor
				if (mpz_cmp(p.p, p.factor1) != 0) {				
					lenstras(p.factor1, max);
					lenstras(p.factor2, max);
					return 0;
				}
			}
		}
	}
	char* f2 = mpz_get_str(NULL, 10, n);
	output.push_back(std::string(f2));
	free(f2);
	return -1;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Incorrect number of arguments!  Run program as follows:\n");
		printf("./lenstras <number_to_be_factored> <desired_limit>\n");
		return -1;
	}
	mpz_t n, max;
	mpz_init_set_str(n, argv[1], 10);
	if (mpz_cmp_si(n, 2) < 0) {
		printf("Number to be factored is less than 2 or non-numeric!\n");
		return -1;
	}
	mpz_init_set(max, n);
	mpz_sub_ui(max, max, 1);
	char* end_ptr;
	int limit = strtol(argv[2], &end_ptr, 10);
	if (*end_ptr != '\0') {
		printf("Desired limit is non-numeric!\n");
		return -1;
	}
	if ((limit == LONG_MAX || limit == LONG_MIN) && errno == ERANGE) {
		printf("Desired limit is too large!\n");
		return -1;
	}
	if (limit < 2) {
		printf("Desired limit is less than 2!\n");
		return -1;
	}
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, rand_dev());
	get_primes_less_than(limit, primes);
	mpz_init(temp);
	
	printf("\n");
	mpz_out_str(stdout, 10, n);
	printf(" = ");
	if (lenstras(n, max) == -1) {
		mpz_out_str(stdout, 10, n);
		printf(" * 1\n");
	}
	else {
		for (auto it = output.begin(); it != output.end(); ++it) {
		std::cout << *it << " * ";
		}
		printf("\b\b\b  \b\b\n");
	}
	mpz_clear(temp);
	return 0;
}
