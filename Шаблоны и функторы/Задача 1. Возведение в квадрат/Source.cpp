#include <iostream>
#include <vector>
#include "Sqr.h"

int main() {

	auto var = sqr(4);

	std::cout << "[OUT]: " << var << std::endl;
	
	std::vector<int> V{ -1, 2, 3, 6 };
	

	bool first = true;
	for (auto x : sqr(V))
	{
		if (first) {
			std::cout << "\n[OUT]: ";
			first = false;
		}
		else {
			std::cout << ", ";
		}
		std::cout << x;
	}

	std::cout << std::endl;

	return 0;

}