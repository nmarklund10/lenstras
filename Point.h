#include <string> 
#include "gmp.h"

#define POINT_O Point(-1, -1)

class Point {
	public:
		mpz_t x, y, a, p;
		Point();
		Point(int x_new, int y_new);
		Point(std::string x_new, std::string y_new, std::string a_new, std::string p_new);
		Point(mpz_t x_new, mpz_t y_new, mpz_t a_new, mpz_t p_new);
		Point(Point p1, std::string a_new, std::string p_new);
		~Point();
		void print();
		void add(Point p1);
		bool equals(Point p1);
};
