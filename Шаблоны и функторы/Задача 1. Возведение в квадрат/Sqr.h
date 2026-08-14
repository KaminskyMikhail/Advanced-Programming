#pragma once
#include<vector>
#include<iostream>
template<typename T>

T sqr(T el) {

	std::cout << "[IN}: " << el << std::endl;
	return el * el;
	
}

template<>
std::vector<int>sqr (std::vector<int> arr) {

	bool first = true;

		for (auto x : arr)
		{
			if (first) {
				std::cout << "\n[IN]: ";
				first = false;
			}
			else {
				std::cout << ", ";
			}
			std::cout << x;
		}

	for (int i = 0; i < arr.size(); i++) {
		arr[i] *= arr[i];
	}

	return arr;
}