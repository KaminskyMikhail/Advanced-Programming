#include <iostream>

class smart_array {
private:
    int SIZE;
    int* arr;
    int count;
public:
    smart_array(int var) : SIZE(var), count(0) {
        arr = new int[SIZE]();
    }

    smart_array(const smart_array& other)
        : SIZE(other.SIZE), count(other.count) {
        arr = new int[SIZE];
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }
    }

    void add_element(int el) {
        if (count >= SIZE) {
            throw std::runtime_error("Размер массива не соответствует количеству вносимых элементов!");
        }
        arr[count++] = el;
    }

    int get_element(int index) const {
        if (index >= SIZE) {
            throw std::runtime_error("Индекс вне диапазона массива!");
        }
        return arr[index];
    }

    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this; 
        }

        delete[] arr; 

        SIZE = other.SIZE;
        count = other.count;
        arr = new int[SIZE];
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }

        return *this;
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

		std::cout << arr.get_element(1) << std::endl;
		std::cout << new_array.get_element(0) << std::endl;

	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}