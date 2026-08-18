#include <iostream>

template<class T>
class Matrix {

private:
	T** arr = nullptr;
	int rows, cols;
public:
	Matrix(int rows, int cols) : arr(new T*[rows]), rows(rows), cols(cols) {
		for (int i = 0; i < rows; i++)
		{
			arr[i] = new T[cols];
		}
	}

	T* operator[](int row) const{
		return arr[row];
	}

	T* operator[](int row){
		return arr[row];
	}

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] arr[i];
		}
		delete[] arr;

	}
};
	int main() {
	
		auto arr = Matrix<int>(3, 4);
		arr[0][0] = 4;
		std::cout << arr[0][0] << std::endl;
	
	}

