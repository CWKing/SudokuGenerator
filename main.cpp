#include "grid.h"
#include <iostream>
#include <stdlib.h>

using std::cout; using std::endl;

void main() {
	grid newGrid;
	while (newGrid.getpoteCellSize() > 0) {
		newGrid.workThroughQueue();
		newGrid.assignRandom();
	};
	newGrid.printGrid();

};

/*
int main() {
	short resp, resp1;
	int seed;
	cout << "Run debugging? 1)Yes 2)No: ";
	cin >> resp;
	if (resp == 2) {
		cout << "Print a filled sudoku? 1)Yes 2)No: ";
		cin >> resp1;
		if (resp1 == 1) printCompleted = true;
	}
	cout << "\nPlease specify an integer seed: ";
	cin >> seed;
	srand(seed);
	if (resp == 1) debug = true;
	grid theGrid = main_initializer();
	while (theGrid.poteCells.size() > 0) {
		//if (debug) cout << "Calling randomCellNum\n";
		randomCellNum(theGrid);
		//if (debug) cout << "Calling soleCell\n";
		soleCell(theGrid);
	}
	printGrid(theGrid);
	cout << "Sudoku for seed: " << seed << "\nPress any key to exit";
	cin.ignore();   //Flushes nullspace from cin
	cin.get();	  //To stop the prog from exiting immediately on completion
	return 0;
}
*/