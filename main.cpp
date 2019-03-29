#include "grid.h"
#include <iostream>
#include <stdlib.h>

///THE ONLY two GLOBAL VARIABLE(s)
bool debug = false;
bool crazy = false;
///DO NOT PANIC
///they WILL NOT HURT YOU

char capitalize(char to_capitalize) {
	return (to_capitalize < 123 && 96 < to_capitalize) ? (to_capitalize - 32) : to_capitalize;
};

int main() {
	grid newGrid;
	char A = '\0';
	int seed = 0;
	do {
		std::cout << "Run with debugging? Y/N? ";
		std::cin >> A;
		A = capitalize(static_cast<char>(A));
	} while ((A != 'Y') && (A != 'N'));
	if (A == 'Y') {
		debug = true;
		do {
			std::cout << "Are you crazy about debugging? Y/N? ";
			std::cin >> A;
			A = capitalize(static_cast<char>(A));
		} while ((A != 'Y') && (A != 'N'));
	}
	if (A == 'Y') crazy = true;
	std::cout << "\nPlease specify an integer seed: ";
	std::cin >> seed;
	std::srand(static_cast<unsigned int>(seed));
	while (newGrid.getpoteCellSize() > 0) {
		newGrid.workThroughQueue();
		newGrid.assignRandom();
		if (debug) {
			std::cout << "Press any button to continue...\n";
			std::cin.ignore();
			std::cin.get();
			newGrid.printGrid();
		}
	};
	newGrid.printGrid();
	std::cout << "Sudoku for seed: " << seed << "\nPress any button to exit";
	std::cin.ignore();
	std::cin.get();
	return 0;
};