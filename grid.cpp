#include "grid.h"

using std::cout; using std::endl;

///Definition function unitStepFunction
short unitStepFunction(short number, short switchpoint) {
	if (number >= switchpoint) return 1;
	else return 0;
};
///End function unitStepFunction

///Definition grid class default constructor
grid::grid() {
	GRID.reserve(81); //Need to preemptively reserve space BUT not initialize the cells to prevent both const problems and vector memory relocation
	poteCells.reserve(81);
	initializeGrid();
};
///End grid class constructor

///Definition public member function grid class printGrid
void grid::printGrid() const {
	for (short row = 0; row < 9; row++) {
		if (row % 3 == 0) cout << "+---------+---------+---------+\n";
		for (short col = 0; col < 9; col++) {
			if (col % 3 == 0) cout << "|";
			cout << "[";
			if (!(GRIDRF[row][col]->getNecessity())) cout << GRIDRF[row][col]->getNumber();
			else cout << " ";
			cout << "]";
		};
		cout << "|" << endl;
	};
	cout << "+---------+---------+---------+\n";
};
///End public member function grid class printGrid

///Definition public member function grid class checkRowsFSoP
///Row family wrapper for checkFamilyFSoP
void grid::checkRowsFSoP(cell& C) {
	checkFamilyFSoP(this->GRIDRF[C.getRow()], ROW);
};
///End public member function grid class checkRowsFSoP

///Definition public member function grid class checkColumnsFSoP
///Column family wrapper for checkFamilyFSoP
void grid::checkColumnsFSoP(cell& C) {
	checkFamilyFSoP(this->GRIDCF[C.getColumn()], COLUMN);
};
///End public member function grid class checkColumnsFSoP

///Definition public member function grid class checkBlocksFSoP
///Block family wrapper for checkFamilyFSoP
void grid::checkBlocksFSoP(cell& C) {
	checkFamilyFSoP(this->GRIDBB[C.getBlock()], BLOCK);
};
///End public member function grid class checkBlocksFSoP

///Definition public member function grid class checkRowsFSoN
///Row family wrapper for checkFamilyFSoP
void grid::checkRowsFSoN(cell& C) {
	checkFamilyFSoN(this->GRIDRF[C.getRow()], ROW);
};
///End public member function grid class checkRowsFSoN

///Definition public member function grid class checkColumnsFSoN
///Column family wrapper for checkFamilyFSoP
void grid::checkColumnsFSoN(cell& C) {
	checkFamilyFSoN(this->GRIDCF[C.getColumn()], COLUMN);
};
///End public member function grid class checkColumnsFSoN

///Definition public member function grid class checkBlocksFSoN
///Block family wrapper for checkFamilyFSoP
void grid::checkBlocksFSoN(cell& C) {
	checkFamilyFSoN(this->GRIDBB[C.getBlock()], BLOCK);
};
///End public member function grid class checkBlocksFSoN

///Definition public member function grid class getpoteCellSize
short grid::getpoteCellSize() const {
	return this->poteCells.size();
};
///Definition public member function grid class getpoteCellSize

///
void grid::workThroughQueue() {
	while (!(this->awaiting_assignment.empty())) {
		(this->awaiting_assignment.front())->setNumber();
		(this->awaiting_assignment.front())->setNecessityTrue();
		this->awaiting_assignment.pop();
	};
};
///

///Definition private member function grid class initializeGrid
///Initializes the grid; called by the default constructor
///Does this by initializing all cells in the grid with the proper fields
void grid::initializeGrid() {
	short blockNum, blockSubIndex, blockIt = 0;
	for (short ROW = 0; ROW < 9; ++ROW)
		for (short COL = 0; COL < 9; ++COL) {
			blockNum = (static_cast<int>(blockIt / 3.) % 3) + (3 * static_cast<int>(static_cast<int>(blockIt / 9.) / 3.));
			blockSubIndex = (blockIt % 3) + 3 * (static_cast<int>(static_cast<int>(blockIt / 3.) / 3.) % 3 * (1 - unitStepFunction(blockIt, 27) + unitStepFunction(blockIt, 36)));
			GRID.push_back(cell(ROW, COL, blockNum));
			GRIDRF[ROW][COL] = (GRIDCF[COL][ROW] = (GRIDBB[blockNum][blockSubIndex] = &GRID[blockIt]));
			poteCells.push_back(GRIDRF[ROW][COL]);
			blockIt += 1;
		};
	GRID.shrink_to_fit();
};
///End private member function grid class initializeGrid

///Definition private member function grid class checkFamilyFSoP
///Main handler for checking FSoP. Takes a family and performs the more complicated FSoP checks.
///As after changing potentials, previous checks become invalidated (new subfamilies could have been created), we will have to restart the check from the very beginning
///everytime we have a positive result; furthermore, it MAY be possible for a single cell to be in multiple subfamilies (one from each family it belongs), so we need
///to be sure when checking for exclusion based on already being in a subfamily, we know which family we are considering.
///cell** is to be interpreted as an array of pointers to cells
void grid::checkFamilyFSoP(cell** family, RCB rcb) {
	//Impliment FSoP checker here!
};
///End private member function grid class checkFamilyFSoP

///Definition private member function grid class checkFamilyFSoN
///Checks the potentials of the passed cell and if it can only contain one number, pushes into the queue
///If this is not the case, then checks this cell against all cells in each of its three families to see
///if it is the only cell which may contain a particular number
void grid::checkFamilyFSoN(cell** family, RCB rcb) {
	//Impliment FSoN checker here!
};
//Might need to change this to act immediately if issues arrise from a cell waiting with 1 potential being flagged in a subfamily by the FSoP checker
///End private member function grid class checkFamilyFSoN

///Definition private member function grid class changePotentials
///Is past a reference to a cell then changes the potential of the number the cell contains to false of all associated cells
void grid::changePotentials(cell& CELL) {
	for (short i = 0; i < 9; ++i) {
		GRIDRF[CELL.getRow()][i]->setPotentialFalse(CELL.getNumber() - 1);
		GRIDRF[i][CELL.getColumn()]->setPotentialFalse(CELL.getNumber() - 1);
		GRIDBB[CELL.getBlock()][i]->setPotentialFalse(CELL.getNumber() - 1);
	};
};
///End private member function grid class changePotentials
