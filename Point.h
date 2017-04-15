#include <string> 
#include <math.h>
#include "gmp.h"

class Point {
	public:
		mpz_t x, y, a, p;
		Point(mpz_t a_new, mpz_t p_new);	//initializes to Point(-1, -1)
		Point(mpz_t x_new, mpz_t y_new, mpz_t a_new, mpz_t p_new);
		Point(Point& p1);
		void operator=(Point& p);
		~Point();
		void print();
		int add(Point& p1);
		int multiply(int n);
		bool equals(Point& p1);
		bool equals_POINT_O();
		mpz_t factor1, factor2;
};
