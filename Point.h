#include <string> 
#include "gmp.h"

#ifndef MY_MPZ_MOD
#define MY_MPZ_MOD
void my_mpz_mod(mpz_t out, mpz_t modulus);

#endif

class Point {
	public:
		mpz_t x, y, a, p;
		Point();
		Point(mpz_t x_new, mpz_t y_new, mpz_t a_new, mpz_t p_new);
		Point(Point& p1, mpz_t a_new, mpz_t p_new);
		~Point();
		void print();
		int add(Point& p1);
		int multiply(int n, Point& p1);
		bool equals(Point& p1);
		bool equals_POINT_O();
};
