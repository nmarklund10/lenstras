#include "Point.h"

void my_mpz_mod(mpz_t out, mpz_t modulus) {
	while (mpz_cmp_si(out, 0) < 0)
		mpz_add(out, out, modulus);
	mpz_mod(out, out, modulus);
}

Point::Point(mpz_t a_new, mpz_t p_new) {
	mpz_init_set_si(x, -1);
	mpz_init_set_si(y, -1);
	mpz_init_set(a, a_new);
	mpz_init_set(p, p_new);
	mpz_init(factor1);
	mpz_init(factor2);
}

Point::Point(mpz_t x_new, mpz_t y_new, mpz_t a_new, mpz_t p_new) {
	mpz_init_set(x, x_new);
	mpz_init_set(y, y_new);
	mpz_init_set(a, a_new);
	mpz_init_set(p, p_new);
	my_mpz_mod(x, p);
	my_mpz_mod(y, p);
	my_mpz_mod(a, p);
	mpz_init(factor1);
	mpz_init(factor2);
}

Point::Point(Point& p1) {
	mpz_init_set(x, p1.x);
	mpz_init_set(y, p1.y);
	mpz_init_set(a, p1.a);
	mpz_init_set(p, p1.p);
	mpz_init(factor1);
	mpz_init(factor2);
}

Point::~Point() {
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(a);
	mpz_clear(p);
	mpz_clear(factor1);
	mpz_clear(factor2);
}

void Point::print() {
	printf("(");
	mpz_out_str(stdout, 10, x);
	printf(", ");
	mpz_out_str(stdout, 10, y);
	printf(")\n");
}

bool Point::equals(Point& p1) {
	return ((mpz_cmp(x, p1.x) == 0) && (mpz_cmp(y, p1.y) == 0));
}

bool Point::equals_POINT_O() {
	return ((mpz_cmp_si(x, -1) == 0) && (mpz_cmp_si(y, -1) == 0));
}

int Point::add(Point& p1) {
	if (p1.equals_POINT_O()) {
		return 1;
	}
	if (equals_POINT_O()) {
		mpz_set(x, p1.x);
		mpz_set(y, p1.y);
		my_mpz_mod(x, p);
		my_mpz_mod(y, p);
		return 2;
	}
	mpz_t m, x3, y3, temp, copy;
	mpz_init(m); mpz_init(x3); mpz_init(y3); mpz_init(temp); mpz_init(copy);
	if (equals(p1)) {
		mpz_set_ui(m, 3);
		mpz_mul(m, m, x);
		mpz_mul(m, m, x);
		mpz_add(m, m, a);
		mpz_set_ui(temp, 2);
		mpz_mul(temp, temp, y);
		mpz_set(copy, temp);
		if (mpz_invert(temp, temp, p) == 0) {
			mpz_t copy2;
			mpz_init(copy2);
			mpz_gcd(copy, copy, p);
			mpz_tdiv_q(copy2, p, copy);
			mpz_set(factor1, copy);
			mpz_set(factor2, copy2);
			mpz_clear(m);
			mpz_clear(temp);
			mpz_clear(x3);
			mpz_clear(y3);
			mpz_clear(copy);
			mpz_clear(copy2);
			return -1;
		}
		mpz_mul(m, m, temp);
		my_mpz_mod(m, p);
	}
	else if (mpz_cmp(x, p1.x) == 0) {
		mpz_set_si(x, -1);
		mpz_set_si(y, -1);
		mpz_clear(m);
		mpz_clear(temp);
		mpz_clear(x3);
		mpz_clear(y3);
		mpz_clear(copy);
		return 3;
	}
	else {
		mpz_set(m, p1.y);
		mpz_sub(m, m, y);
		mpz_set(temp, p1.x);
		mpz_sub(temp, temp, x);
		mpz_set(copy, temp);
		if (mpz_invert(temp, temp, p) == 0) {
			mpz_t copy2;
			mpz_init(copy2);
			mpz_gcd(copy, copy, p);
			mpz_tdiv_q(copy2, p, copy);
			mpz_set(factor1, copy);
			mpz_set(factor2, copy2);
			mpz_clear(m);
			mpz_clear(temp);
			mpz_clear(x3);
			mpz_clear(y3);
			mpz_clear(copy);
			mpz_clear(copy2);
			return -1;
		}
		mpz_mul(m, m, temp);
		my_mpz_mod(m, p);
	}
	mpz_mul(temp, m, m);
	mpz_sub(temp, temp, x);
	mpz_sub(x3, temp, p1.x);
	my_mpz_mod(x3, p);
	
	mpz_sub(temp, x, x3);
	mpz_mul(temp, temp, m);;
	mpz_sub(y3, temp, y);
	my_mpz_mod(y3, p);
	
	mpz_set(x, x3);
	mpz_set(y, y3);
	
	mpz_clear(m);
	mpz_clear(temp);
	mpz_clear(x3);
	mpz_clear(y3);
	mpz_clear(copy);
	return 4;
}

void Point::operator=(Point& p1) {
	mpz_set(x, p1.x);
	mpz_set(y, p1.y);
	mpz_set(a, p1.a);
	mpz_set(p, p1.p);
}

int Point::multiply(int n) {
	if (n < 1)
		return -2;
	else if (n == 1)
		return 0;
	Point result(*this);
	Point result_neg(*this);						
	mpz_mul_si(result_neg.y, result_neg.y, -1); //negate y value
	Point temp(result_neg);
	Point temp2(result);
	
	int next_pow_2 = pow(2, ceil(log2(n)));
	int diff = next_pow_2 - n;
	next_pow_2 >>= 1;
	
	while (next_pow_2 > 0) {
		if (diff > 0) {
			if ((diff & 1) == 1) {
				if (add(temp) < 0)
					return -1;
			}
			if (temp.add(result_neg) < 0) {
				mpz_set(factor1, temp.factor1);
				mpz_set(factor2, temp.factor2);
				return -1;
			}
			result_neg = temp;
		}
		next_pow_2 >>= 1;
		diff >>= 1;		
		if (temp2.add(result) < 0) {
			mpz_set(factor1, temp2.factor1);
			mpz_set(factor2, temp2.factor2);
			return -1;
		}
		if (add(result) < -1)
			return -1;
		result = temp2;
	}
	return 0;
}