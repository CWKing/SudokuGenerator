#include "grid.h"
#include <iostream>

using std::cout; using std::endl;

void main() {
	grid newGrid;
	while (newGrid.getpoteCellSize() > 0) {
		newGrid.workThroughQueue();
		//newGrid.assignRandom();
	};
	newGrid.printGrid();
	/*for (short i = 0; i < 81; ++i) {
		cout << (*newGrid.access)[i] << endl;
	};
	*/
};