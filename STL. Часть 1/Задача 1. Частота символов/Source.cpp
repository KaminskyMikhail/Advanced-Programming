#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
	std::string text { "Hello world!!" };

	std::cout << "[IN]: " << text << std::endl;

	std::unordered_map<char, int> counts;


	for (auto x : text) {
		counts[x]++;
	}

	std::vector<std::pair<char, int>> sorted_counts(counts.begin(), counts.end());

	std::sort(sorted_counts.begin(), sorted_counts.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	std::cout << "[OUT]:" << std::endl;

	for (const auto& pair : sorted_counts) {
		std::cout << pair.first << " " << pair.second << std::endl;
	}

	return EXIT_SUCCESS;
}