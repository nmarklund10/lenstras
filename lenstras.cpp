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
		printf("Incorrect number of arguments!  Run program as follows:\n");
		printf("./lenstras <x1> <y1> <a> <p>");
		return -1;
	}
	Point p1(argv[1], argv[2], argv[5], argv[6]);
	Point p2(argv[3], argv[4], argv[5], argv[6]);
	p1.add(p2);
	p1.print();
	return 0;
}
