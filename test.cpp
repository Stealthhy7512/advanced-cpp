#include <iostream>

#include "vector.hpp"

int main() {
	//Custom::Vector<int> vec{};

	//vec.push_back(2);
	//vec.push_back(3);
	//vec.push_back(2);

	Custom::Vector<char> vec{};
	vec.push_back('a');
	vec.push_back('b');

	std::cout << vec.size() << '\n';

	for (size_t i{}; i < vec.size(); ++i) {
		std::cout << vec[i] << ' ';
	}
	std::cout << '\n';

	auto res{ vec.at(3) };

	if (res) {
		std::cout << *res << '\n';
	} else {
		std::cout << res.error() << '\n';
	}

	return 0;
}