#include "Point.h"
Point::Point(int x_new, int y_new) : x(x_new), y(y_new)

bool Point::operator==(Point p) {
	return (this->x == p.x) && (this->y == p.y);
}

Point Point::operator+(Point p) {
	if (p == POINT_O)
		return *this;
	if (this == POINT_O)
		return p;fdssf
	int m, x3, y3;
	if (*this == p) {
		m = 3 * this->x * this->x;
	}
	else if (this->x == p.x) {
		return POINT_O;
	}
	else {
		
	}
	return POINT_O;
}

std::string print() {
	return "(" + this->x + ", " + this->y + ")";
}