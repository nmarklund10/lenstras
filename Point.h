#pragma once

#define POINT_O Point(-1, -1)

class Point {
	public:
		int x;
		int y;
		Point(int x_new, int y_new);
		bool operator==(Point p);
		Point operator+(Point p);
		std::string print();
};
