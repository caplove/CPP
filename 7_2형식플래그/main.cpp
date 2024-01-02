#include <string>
#include <iostream>

/**
 * Main function of the program.
 * It reads an integer in hexadecimal format from the input.
 * If the input is not a valid hexadecimal number, it prints an error message and continues.
 * If the input is a valid hexadecimal number, it prints a success message and continues.
 * The program stops when the input is 0.
 */
int main() {
	int t;
	while (true) {
		// Set the input stream to read hexadecimal numbers
		std::cin.setf(std::ios::hex, std::ios::basefield);
		std::cin >> t;
		std::cout << "입력값: " << t << std::endl;

		// Check if the input was a valid hexadecimal number
		if (std::cin.fail()) {
			// Clear the error state of the input stream
			std::cin.clear();
			// Ignore the next 100 characters or until a newline character is found
			std::cin.ignore(100, '\n');
			std::cout << "잘못된 입력입니다." << std::endl;
			}
		else {
			// Ignore the next 100 characters or until a newline character is found
			std::cin.ignore(100, '\n');
			std::cout << "정상 입력입니다." << std::endl;
			}

		// If the input was 0, break the loop
		if (t == 0) {
			break;
			}
		}

	return 0;
	}


