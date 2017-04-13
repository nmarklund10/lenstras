#include "Point.h"

Point::Point() {
	mpz_init_set_ui(x, 0);
	mpz_init_set_ui(y, 0);
	mpz_init_set_ui(a, 0);
	mpz_init_set_ui(p, 0);
}

Point::Point(int x_new, int y_new) {
	mpz_init_set_si(x, x_new);
	mpz_init_set_si(y, y_new);
	mpz_init_set_ui(a, 0);
	mpz_init_set_ui(p, 0);
}

Point::Point(std::string x_new, std::string y_new, std::string a_new, std::string p_new) {
	mpz_init_set_str(x, x_new.c_str(), 10);
	mpz_init_set_str(y, y_new.c_str(), 10);
	mpz_init_set_str(a, a_new.c_str(), 10);
	mpz_init_set_str(p, p_new.c_str(), 10);
}

Point::Point(mpz_t x_new, mpz_t y_new, mpz_t a_new, mpz_t p_new) {
	mpz_init_set(x, x_new);
	mpz_init_set(y, y_new);
	mpz_init_set(a, a_new);
	mpz_init_set(p, p_new);
}

bool Point::operator==(Point p) {
	return (mpz_cmp(this->x, p.x) && mpz_cmp(this->y, p.y));
}

void Point::operator+(Point p) {
	if (p == POINT_O || *this == POINT_O)
		return;
	mpz_t m, x3, y3, temp;
	mpz_init(m);
	mpz_init(x3);
	mpz_init(y3);
	mpz_init(temp);
	if (*this == p) {
		mpz_set_ui(m, 3);
		mpz_mul(m, m, this->x);
		mpz_mul(m, m, this->x);
		mpz_add(m, m, this->a);
		mpz_set_ui(temp, 2);
		mpz_mul(temp, temp, this->y);
		mpz_invert(temp, temp, this->p);
		mpz_mul(m, m, temp);
		mpz_mod(m, m, this->p);
	}
	else if (this->x == p.x) {
		mpz_clear(m);
		mpz_clear(temp);
		mpz_clear(x3);
		mpz_clear(y3);
		return;
	}
	else {
		mpz_set(m, p.y);
		mpz_sub(m, m, this->y);
		mpz_set(temp, p.x);
		mpz_sub(temp, temp, this->x);
		mpz_invert(temp, temp, this->p);
		mpz_mul(m, m, temp);
		mpz_mod(m, m, this->p);
	}
	mpz_mul(temp, m, m);
	mpz_sub(temp, temp, this->x);
	mpz_sub(x3, temp, p.x);
	
	mpz_sub(temp, this->x, x3);
	mpz_mul(temp, temp, m);;
	mpz_sub(y3, temp, this->y);
	
	mpz_set(this->x, x3);
	mpz_set(this->y, y3);
	
	mpz_clear(m);
	mpz_clear(temp);
	mpz_clear(y3);
	mpz_clear(x3);
	return;
}

void Point::print() {
	printf("(");
	mpz_out_str(stdout, 10, this->x);
	printf(", ");
	mpz_out_str(stdout, 10, this->y);
	printf(")\n");
}