#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

int main() {
	
	std::cout << "[IN]:" << std::endl;

	int q = 0; std::cin >> q;

	std::set<int> set_el;

	std::copy_n(std::istream_iterator<int>(std::cin), q, std::inserter(set_el, set_el.begin()));

	std::vector<int> vec(set_el.begin(), set_el.end());

	

	std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
		return b < a;
		});

	std::cout << "[OUT]:" << std::endl;

	for (auto x : vec) {
		std::cout << x << std::endl;
	}
	return EXIT_SUCCESS;
}