#include <iostream>
#include <vector>
#include "Sqr.h"

int main() {
	int val = 4;
	std::cout << "[IN]: " << val << std::endl;

	val = square(val);

	std::cout << "[OUT]: " << val << std::endl;
	
	std::vector<int> V{ -1, 2, 3, 6 };
	
	std::cout << "[IN]: ";

	for (const auto& x : V) {
		std::cout << x << " ";
	}

	std::cout << "\n[OUT]: ";

	for (auto x : sqr(V)) {
		std::cout << x << " ";
	}

	std::cout << std::endl;

	return 0;

}