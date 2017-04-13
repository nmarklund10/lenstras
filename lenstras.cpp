#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <errno.h>
#include <climits>
#include <random>
#include <chrono>
#include <iostream>
#include "gmp.h"
#include "Point.h"

int main(int argc, char** argv) {
	if (argc != 5) {
		
	}
	Point p(0, 3);
	std::cout << p.print() << std::endl;
	return 0;
}
