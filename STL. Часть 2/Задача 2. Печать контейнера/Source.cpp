#include <iostream>
#include <set>
#include <list>
#include <vector>

template<typename T>

void print(const T& el) {

	for (auto& const x : el) {
		std::cout << x << " ";
	}
}

int main() {


	std::set<std::string> test_set{ "one", "two", "three", "four" };
	std::list<std::string> test_list = { "one", "two", "three", "four" };
	std::vector<std::string> test_vector = { "one", "two", "three", "four" };

	std::cout << "test_set: ";		print(test_set);		std::cout << std::endl;
	std::cout << "test_list: ";		print(test_list);		std::cout << std::endl;
	std::cout << "test_vector: ";   print(test_vector);		std::cout << std::endl;

	return EXIT_SUCCESS;
}