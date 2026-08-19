#include <iostream>
#include <vector>
#include <algorithm>

int main() {

	std::vector<int> V{ 1, 1, 2, 5, 6, 1, 2, 4 };

	std::sort(V.begin(), V.end());
	
	std::cout << "[IN]: ";
	
	for (auto x : V) {
		std::cout << x << " ";
	}

	std::cout << std::endl;

	auto vec = std::unique(V.begin(), V.end());

	
	V.erase(vec, V.end());
	
	std::cout << "[OUT]: ";
	
	for (auto x : V) {
		std::cout << x << " ";
	}

	return EXIT_SUCCESS;
}