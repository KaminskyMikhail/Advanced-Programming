#include <iostream>

class smart_array {
private:
	int SIZE;
	int* arr = new int[SIZE];
	int count;
public:
	smart_array(int var) : SIZE(var), count(0) {}

	void add_element(int el) {
		if (count > SIZE - 1) {
			throw std::runtime_error("Размер массива не соответствует количеству вносимых элементов!");
		}
		arr[count++] = el;
	}

	int get_element(int index) {
		if (index > SIZE - 1) {
			throw std::runtime_error("Индекс вне диапазона массива!");
		}

		return arr[index];

	}
	void operator=(const smart_array& new_array) {
		if (this->SIZE >= new_array.SIZE) {
			for (int i = 0; i < new_array.SIZE; i++)
			{
				this->arr[i] = new_array.arr[i];
			}
		}
		else if (new_array.SIZE > this->SIZE) {
			throw std::runtime_error("Копирование невозможно!");
		}
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

		smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);

		arr = new_array;

		std::cout << arr.get_element(2) << std::endl;
		std::cout << new_array.get_element(0) << std::endl;

	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}