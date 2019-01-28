#include "grid.h"

using std::cout; using std::endl;

///Definition function unitStepFunction
short unitStepFunction(short number, short switchpoint) {
	if (number >= switchpoint) return 1;
	else return 0;
};
///End function unitStepFunction

///Definition grid class default constructor
///Need to use initializer list to initialize the constant pointer to a constant cell vector access
grid::grid() : access(&GRID) {
	GRID.reserve(81); //Need to preemptively reserve space BUT not initialize the cells to prevent both const problems and vector memory relocation
	initializeGrid();
};
///End grid class constructor

///Definition public member function grid class printGrid
void grid::printGrid() const {
	for (int row = 0; row < 9; row++) {
		if (row % 3 == 0) cout << "+---------+---------+---------+\n";
		for (int col = 0; col < 9; col++) {
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

///Definition public member function grid class checkColumns
///Checks the columns of the grid for a distinct potential
void grid::checkColumns() {
	
};
///End public member function grid class checkColumns

///Definition public member function grid class checkRows
///Checks the rows of the grid for a distinct potential
void grid::checkRows() {

};
///End public member function grid class checkRows

///Definition public member function grid class checkBlocks
///Checks the blocks of the grid for a distinct potential
void grid::checkBlocks() {

};
///End public member function grid class checkBlocks

///Definition private member function grid class checkPotentials
///Checks the potentials of the passed cell and if it can only contain one number, assigns that number to it 
void grid::checkPotentialsSoleNum(cell &C) {
	short truthCount = 0, tempIndex = -1;
	for (short i = 0; i < 9; ++i)
		if (C.getPotentials[i]) {
			++truthCount;
			tempIndex = i;
		};
	if (truthCount == 1) {
		C.setNumber(tempIndex + 1);
		C.setNecessityTrue();
	};
};
///End private member function grid class checkPotentials

///Definition private member function grid class initializeGrid
///Initializes the grid; called by the default constructor
void grid::initializeGrid() {
	short blockNum, blockSubIndex, blockIt = 0;
	for (short ROW = 0; ROW < 9; ++ROW)
		for (short COL = 0; COL < 9; ++COL) {
			blockNum = (static_cast<int>(blockIt / 3.) % 3) + (3 * static_cast<int>(static_cast<int>(blockIt / 9.) / 3.));
			blockSubIndex = (blockIt % 3) + 3 * (static_cast<int>(static_cast<int>(blockIt / 3.) / 3.) % 3 * (1 - unitStepFunction(blockIt, 27) + unitStepFunction(blockIt, 36)));
			GRID.push_back(cell(ROW, COL, blockNum));
			GRIDRF[ROW][COL] = (GRIDBB[blockNum][blockSubIndex] = &GRID[blockIt]);
			poteCells.push_back(RowCol(ROW, COL));
			blockIt += 1;
		};
	GRID.shrink_to_fit();
};
///End private member function grid class initializeGrid

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
