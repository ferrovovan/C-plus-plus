#include <iostream>
#include <cmath>

void SolveQuadratic(double a, double b, double c) {
	if (a == 0) {
		if (b == 0) {
			std::cout << (c == 0 ? "Infinite solutions\n" : "No solutions\n");
		} else {
			std::cout << "x = " << -c / b << "\n";
		}
		return;
	}
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		std::cout << "No real solutions\n";
	} else if (discriminant == 0) {
		std::cout << "x = " << -b / (2 * a) << "\n";
	} else {
		double x1 = (-b + sqrt(discriminant)) / (2 * a);
		double x2 = (-b - sqrt(discriminant)) / (2 * a);
		std::cout << "x1 = " << x1 << ", x2 = " << x2 << "\n";
	}
}

int main() {
	double a, b, c;
	std::cout << "Enter coefficients a, b, c: ";
	std::cin >> a >> b >> c;
	SolveQuadratic(a, b, c);
	return 0;
}

