#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <climits>
#include <random>
#include <chrono>
#include <iostream>
#include "Point.h"

int main(int argc, char** argv) {
	if (argc != 5) {
		
	}
	Point p1("1", "2", "-1", "7");
	Point p2("4", "1", "-1", "7");
	p1 + p2;
	p1.print();
	return 0;
}
