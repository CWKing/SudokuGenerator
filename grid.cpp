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
	poteCells.reserve(81);
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
void grid::checkColumnsFSoP() {
	
};
///End public member function grid class checkColumns

///Definition public member function grid class checkRows
///Checks the rows of the grid for a distinct potential
void grid::checkRowsFSoP() {

};
///End public member function grid class checkRows

///Definition public member function grid class checkBlocks
///Checks the blocks of the grid for a distinct potential
void grid::checkBlocksFSoP() {

};
///End public member function grid class checkBlocks

///Definition private member function grid class checkPotentialsSoleNum
///Checks the potentials of the passed cell and if it can only contain one number, pushes into the queue
void grid::checkPotentialsSoleNum(cell &C) {
	short truthCount = 0, tempIndex = -1;
	for (short i = 0; i < 9; ++i)
		if (C.getPotentials[i]) {
			++truthCount;
			tempIndex = i;
		};
	if (truthCount == 1) {
		this->awaiting_assignment.push(&C);
	};
};
///End private member function grid class checkPotentials

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
			GRIDRF[ROW][COL] = (GRIDBB[blockNum][blockSubIndex] = &GRID[blockIt]);
			poteCells.push_back(GRIDRF[ROW][COL]);
			blockIt += 1;
		};
	GRID.shrink_to_fit();
};
///End private member function grid class initializeGrid

///Definition private member function grid class checkFamilyFSoP
///Main handler for checking FSoP. Takes a family and performs the more complicated FSoP checks.
///As after changing potentials, previous checks become invalidated, we will have to restart the check from the very beginning
///everytime we have a positive result; this will get messy.
void grid::checkFamilyFSoP(cell* family) {
	short Number_of_potentials = 0, hit_count = 0;
	for (size_t i = 0; i < 9; ++i) {
		if (family[i].getNumber() || (9-i) < family[i].NP()) {	//If cell contains a number or the remaining number of cells in the family is less than the number of
			hit_count = 0;										//potentials, go to the next cell (no need to check)
			continue;
		}				
		Number_of_potentials = family[i].NP();					//If not, save the number of potentials it contains; we're gunna start checkin'!
		for (size_t j = i + 1; j < 9; ++j) {
			if ((9 - j) < (Number_of_potentials - hit_count)) { //9-j is the number of cells left in the family to possibly compare to; if this number is less than
				hit_count = 0;									//the number of cells we still need, then there's no point continuing (impossible to get enough hits)
				break;
			}
			if (family[i] == family[j]) ++hit_count;			//Overload of operator== for cells checks for equality in both number of potentials and what those potentials are
		}
		if (hit_count == Number_of_potentials) {				//If after iterating, the hit count is the same as the number of potentials, then we've successfully
			i = -1; hit_count = 0;								//found a subfamily which all cells contain the exact same potentials, so we need to remove those
																//potentials from all the remaining cells in the family. PROBLEM! We need to run the check again to be
																//sure we catch any newly formed subfamilies, but avoid an infinite loop by reidentifying the one we
																//just found... maybe a new field in the cell class designating it as already in a subfamily?
		}
	}
};
///End private member function grid class checkFamilyFSoP

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
