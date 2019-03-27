#include "grid.h"

using std::cout; using std::endl;

///
potentialSumContainer::potentialSumContainer() : sum{ 0, 0, 0, 0, 0, 0, 0, 0 } {};
///

///
short potentialSumContainer::hasOne() {
	for (short i = 0; i < 9; ++i) if (this->sum[i] == 1) return i;
	return 0;
}
///

///
void potentialSumContainer::reset() { for (short i = 0; i < 9; ++i) sum[i] = 0; };
///	

///
///Piecewise addition of the potentials in the cells used for generating cell set signatures which are intended ot be used in the FSoP checker
potentialSumContainer& potentialSumContainer::operator+=(const cell* rhs) { for (short i = 0; i < 9; ++i) this->sum[i] += rhs->getPotential[i]; };
///

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
void grid::checkRowsFSoP(const cell& C) {
	checkFamilyFSoP(this->GRIDRF[C.getRow()], ROW);
};
///End public member function grid class checkRowsFSoP

///Definition public member function grid class checkColumnsFSoP
///Column family wrapper for checkFamilyFSoP
void grid::checkColumnsFSoP(const cell& C) {
	checkFamilyFSoP(this->GRIDCF[C.getColumn()], COLUMN);
};
///End public member function grid class checkColumnsFSoP

///Definition public member function grid class checkBlocksFSoP
///Block family wrapper for checkFamilyFSoP
void grid::checkBlocksFSoP(const cell& C) {
	checkFamilyFSoP(this->GRIDBB[C.getBlock()], BLOCK);
};
///End public member function grid class checkBlocksFSoP

///Definition public member function grid class checkRowsFSoN
///Row family wrapper for checkFamilyFSoP
void grid::checkRowsFSoN(const cell& C) {
	checkFamilyFSoN(this->GRIDRF[C.getRow()]);
};
///End public member function grid class checkRowsFSoN

///Definition public member function grid class checkColumnsFSoN
///Column family wrapper for checkFamilyFSoP
void grid::checkColumnsFSoN(const cell& C) {
	checkFamilyFSoN(this->GRIDCF[C.getColumn()]);
};
///End public member function grid class checkColumnsFSoN

///Definition public member function grid class checkBlocksFSoN
///Block family wrapper for checkFamilyFSoP
void grid::checkBlocksFSoN(const cell& C) {
	checkFamilyFSoN(this->GRIDBB[C.getBlock()]);
};
///End public member function grid class checkBlocksFSoN

///Definition public member function grid class getpoteCellSize
short grid::getpoteCellSize() const {
	return this->poteCells.size();
};
///End public member function grid class getpoteCellSize

///Definition public member function grid class workThroughQueue
void grid::workThroughQueue() {
	while (!(this->awaiting_assignment.empty())) {
		(this->awaiting_assignment.front().CELL)->setNumber(this->awaiting_assignment.front().NUMBER);
		(this->awaiting_assignment.front().CELL)->setNecessityTrue();
		this->initiateAllChecks(this->awaiting_assignment.front().CELL);
		this->awaiting_assignment.pop();
	};
};
///End public member function grid class workThroughQueue

///
void grid::assignRandom() {

};
///

///Definition public member function grid class initiateAllChecks
void grid::initiateAllChecks(const cell* toCheck) {
	this->checkRowsFSoN(*toCheck);
	this->checkColumnsFSoN(*toCheck);
	this->checkBlocksFSoN(*toCheck);
	this->checkRowsFSoP(*toCheck);
	this->checkColumnsFSoP(*toCheck);
	this->checkBlocksFSoP(*toCheck);
};
///End public member function grid class initiateAllChecks

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
///Main handler for checking FSoN. Takes a family and performs the two FSoN checks on the cells in the family:
/// 1) For each cell in the family, checks if it has only one potential, and if so, pushes into the queue with that number
/// 2) "-----", checks if it is the only cell in the family that can contain a specific number and if so, pushes it into the queue with that number
void grid::checkFamilyFSoN(cell** family) {
	short temp_index = 0, hit_count = 0;
	for (short cellInFamily = 0; cellInFamily < 9; ++cellInFamily) {
		if (family[cellInFamily]->getNumber() || family[cellInFamily]->isAwaitingAssignment()) continue;
		temp_index = hit_count = 0;
		for (short potentialIndex = 0; potentialIndex < 9; ++potentialIndex)
			if (family[cellInFamily]->getPotential[potentialIndex]) {
				temp_index = potentialIndex;
				++hit_count;
			}
		if (hit_count == 1) {
			family[cellInFamily]->setAwaitingAssignmentTrue();
			this->awaiting_assignment.push(CellNum(family[cellInFamily], temp_index + 1));
		}
	}
	for (short potentialIndex = 0; potentialIndex < 9; ++potentialIndex) {
		temp_index = hit_count = 0;
		for (short cellInFamily = 0; cellInFamily < 9; ++cellInFamily) {
			if (family[cellInFamily]->getNumber() || family[cellInFamily]->isAwaitingAssignment()) continue;
			if (family[cellInFamily]->getPotential[potentialIndex]) {
				temp_index = cellInFamily;
				++hit_count;
			}
		}
		if (hit_count == 1) {
			family[temp_index]->setAwaitingAssignmentTrue();
			this->awaiting_assignment.push(CellNum(family[temp_index], potentialIndex + 1));
		}
	}
};
///End private member function grid class checkFamilyFSoN

///Definition private member function grid class changePotentials
///Is past a reference to a cell then changes the potential of the number the cell contains to false of all cells in that cells families
void grid::changePotentials(cell& CELL) {
	for (short i = 0; i < 9; ++i) {
		GRIDRF[CELL.getRow()][i]->setPotentialFalse(CELL.getNumber() - 1);
		GRIDRF[i][CELL.getColumn()]->setPotentialFalse(CELL.getNumber() - 1);
		GRIDBB[CELL.getBlock()][i]->setPotentialFalse(CELL.getNumber() - 1);
	};
};
///End private member function grid class changePotentials
