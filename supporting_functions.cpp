#include "Header.h"

double check_variables(int mode) {
	std::string temp;
	double result;

	while (true) {
		std::cin >> temp;
		try {
			result = stod(temp);
		}
		catch (std::invalid_argument) {
			std::cout << "You should enter only number and \'.\' for real numbers ";
			continue;
		}
		if (mode == 0) {
			if (result < -10000 || result > 10000) {
				std::cout << "Mu should be more or equal to " << -10000 << " and less or equal to " << 10000 << ". Try again: ";
				continue;
			}
		}
		else if (mode == 1) {
			if (result > 10000 || result < 0) {
				std::cout << "Lambda should be more or equal to " << 0 << " and less or equal to " << 10000 << ". Try again: ";
				continue;
			}
		}
		else if (mode == 2) {
			if (result < 0 || result > 10000) {
				std::cout << "Nu should be more or equal to " << 0 << " and less or equal to " << 10000 << ". Try again: ";
				continue;
			}
		}
		else if (mode == 3) {
			if (result < -1 || result > 1) {
				std::cout << "X should be more or equal to " << -1 << " and less or equal to " << 1 << ". Try again: ";
				continue;
			}
		}
		else if (mode == 4) {
			if (result <= 0 || result >= 1) {
				std::cout << "p should be more then " << 0 << " and less then " << 1 << ". Try again: ";
				continue;
			}
		}
		else if (mode == 5) {
			if (result <= 0) {
				std::cout << "n should be more then " << 0 << ". Try again: ";
				continue;
			}
		}
		break;
	}

	return result;
}

void enter(double* args, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << "Enter " << i + 1 << " argument: ";
		args[i] = check_variables(i % 3);
	}
}