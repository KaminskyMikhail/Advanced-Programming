#include <iostream>
#include <vector>
#include <algorithm>

class functor {
private:
	int sum, count;
public:
	
	functor() : sum(0), count(0){}

	void operator()(int num) {
		if (num % 3 == 0) {
			sum += num;
			count++;
		}
		
	}

	int get_sum() const { return sum; }

	int  get_count() const { return count; }
};

int main() {

	std::vector<int> V{ 4, 1, 3, 6, 25, 54 };

	std::cout << "[IN]: ";

	for (auto x : V) { std::cout << x << " "; } std::cout << std::endl;

	functor F;

	F = std::for_each(V.begin(), V.end(), F);

	std::cout << "[OUT]: get_sum() = " << F.get_sum() << std::endl;
	std::cout << "[OUT]: get_count() = " << F.get_count() << std::endl;

	return 0;

}
