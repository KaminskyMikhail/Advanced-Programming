#include <iostream>

class smart_array {
private:
	int SIZE;
	int* arr;
	int count;
public:
	smart_array(int var) : SIZE(var), count(0) {
		arr = new int[SIZE];
		for (int i = 0; i < SIZE - 1; i++) {
			arr[i] = 0;
		}
	}

	void add_element(int el){
		if (count > SIZE - 1) {
			throw std::runtime_error ("Размер массива не соответствует количеству вносимых элементов!");
		}
		arr[count++] = el;
	}
	
	int get_element(int index) {
		if (index > SIZE - 1) {
			throw std::runtime_error("Индекс вне диапазона массива!");
		}

		return arr[index];

	}

	~smart_array() {
		delete[] arr;
	}
};


int main() {
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		//arr.add_element(16);
		std::cout << arr.get_element(2) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}