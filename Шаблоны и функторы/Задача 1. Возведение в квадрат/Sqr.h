#pragma once
#include<vector>
#include<iostream>
template <typename T>

T square(T el) {

	return el * el;
	
}

template <typename T>
std::vector<T> sqr(std::vector<T>& arr) {

	for (auto& x : arr) {
		x = square(x);
	}
	return arr;
}