#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

void CommonLettersInWords() {
	std::string word;
	std::set<char> common_chars;
	bool first_word = true;

	std::cout << "To stop output, press ctrl+D" << std::endl;
	while (std::cin >> word) {
		std::set<char> current_word_chars(word.begin(), word.end());
		if (first_word) {
			common_chars = current_word_chars;
			first_word = false;
		} else {
			std::set<char> intersection;
			std::set_intersection(common_chars.begin(), common_chars.end(),
								current_word_chars.begin(), current_word_chars.end(),
								std::inserter(intersection, intersection.begin()));
			common_chars = intersection;
		}
	}

	for (char c : common_chars) {
		std::cout << c;
	}
	std::cout << "\n";
}

int main() {
	CommonLettersInWords();
	return 0;
}

