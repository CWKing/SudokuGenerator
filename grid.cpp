#include "grid.h"

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
bool potentialSumContainer::hasSubfamSignature(short subFamSize) {
	short hit_count = 0;
	for (short i = 0; i < 9; ++i) {
		if (this->sum[i] == 1) return false;
		else if (this->sum[i] == 0) continue;
		else ++hit_count;
	}
	if (hit_count != subFamSize) return false;
	else return true;
};
///

///
void potentialSumContainer::reset() { for (short i = 0; i < 9; ++i) sum[i] = 0; };
///	

///
///Piecewise addition of the potentials in the cells used for generating cell set signatures which are intended ot be used in the FSoP checker
potentialSumContainer& potentialSumContainer::operator+=(const cell* rhs) { for (short i = 0; i < 9; ++i) this->sum[i] += rhs->getPotential(i); return *this; };
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
		if (row % 3 == 0) std::cout << "+---------+---------+---------+\n";
		for (short col = 0; col < 9; col++) {
			if (col % 3 == 0) std::cout << "|";
			std::cout << "[";
			//debug
			if (debug && GRIDRF[row][col]->getNumber()) std::cout << GRIDRF[row][col]->getNumber();
			else if (debug && !(GRIDRF[row][col]->getNumber())) std::cout << " ";
			//
			else if (this->GRIDRF[row][col]->getNecessity()) std::cout << " ";
			else std::cout << GRIDRF[row][col]->getNumber();
			std::cout << "]";
		};
		std::cout << "|" << std::endl;
	};
	std::cout << "+---------+---------+---------+\n";
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

///
short grid::getpoteCellIndex(const cell& toCheck) const {
	for (short i = 0; i < this->getpoteCellSize(); ++i)
		if (this->poteCells[i]->getRow() == toCheck.getRow() && this->poteCells[i]->getColumn() == toCheck.getColumn())
			return i;
	return -1;	//This should never be passed, but if it does the prog should crash... hopefully.
};
///

///Definition public member function grid class workThroughQueue
void grid::workThroughQueue() {
	while (!(this->awaiting_assignment.empty())) {
		this->poteCells.erase(this->poteCells.begin() + this->getpoteCellIndex(*(this->awaiting_assignment.front().CELL)));
		(this->awaiting_assignment.front().CELL)->setNumber(this->awaiting_assignment.front().NUMBER);
		(this->awaiting_assignment.front().CELL)->setNecessityTrue();
		this->initiateAllChecks(this->awaiting_assignment.front().CELL);
		this->awaiting_assignment.pop();
	};
};
///End public member function grid class workThroughQueue

///Definition public member function grid class assignRandom
void grid::assignRandom() {
	if (!this->getpoteCellSize()) return;
	short randomIndex = std::rand() % this->getpoteCellSize();
	short row = this->poteCells[randomIndex]->getRow();
	short column = this->poteCells[randomIndex]->getColumn();
	//debug
	if (debug) std::cout << "Current number of remaining cells to fill: " << this->getpoteCellSize() << "\nCell [" << row << ", " << column << "] chosen from poteCells index " << randomIndex << std::endl;
	//
	this->poteCells.erase(poteCells.begin() + randomIndex);
	std::vector<short> potentialNumbers;
	//debug
	if (debug) std::cout << "Cell potentials: ";
	//
	for (short potentialNumber = 0; potentialNumber < 9; ++potentialNumber) {
		//debug
		if (debug) std::cout << this->GRIDRF[row][column]->getPotential(potentialNumber) << " ";
		//
		if (this->GRIDRF[row][column]->getPotential(potentialNumber)) potentialNumbers.push_back(potentialNumber + 1);
	}
	randomIndex = std::rand() % potentialNumbers.size();
	//debug
	if (debug) std::cout << "\nSetting number " << potentialNumbers[randomIndex] << " into cell [" << row << ", " << column << "]" << std::endl;
	//
	this->GRIDRF[row][column]->setNumber(potentialNumbers[randomIndex]);
	this->changePotentials(*(this->GRIDRF[row][column]));
	this->initiateAllChecks(this->GRIDRF[row][column]);
};
///End public member function grid class assignRandom

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

///
void grid::FSoPChangePotentials(std::vector<cell*>& subFamily, RCB rcb) {
	//Implimentation here would take the subFamily passed, record the potentials, and make the appropriate potential changes
};
///

///
void grid::FSoPsubFamCheck(std::vector<cell*>& cellSet, RCB rcb) {
	potentialSumContainer potentialSum;
	for (short i = 0; i < cellSet.size(); ++i) potentialSum += cellSet[i];
	if (potentialSum.hasSubfamSignature(cellSet.size())) FSoPChangePotentials(cellSet, rcb);
};
///

///
void grid::FSoPHelper(cell** family, std::vector<cell*>& cellSet, RCB rcb, short START_INDEX, short SUBFAMILY_SIZE) {

	if (SUBFAMILY_SIZE == 0) {
		//this->FSoPsubFamCheck(cellSet, rcb);
		return;
	}
	for (short index = START_INDEX; index <= 9 - SUBFAMILY_SIZE; ++index) {
		cellSet.push_back(family[index]);
		this->FSoPHelper(family, cellSet, rcb, index + 1, SUBFAMILY_SIZE - 1);
		cellSet.pop_back();
	}

	/*
	Desired behaviour is that once it has completed all the 2 family checks (which this current code "does", eg, the check DOES check but the result of
	that check is sent to a null function), it moves on to the 3 family checks (where the "fun" begins...), that is, the entire FSoPHelper recursive stack
	has been unwound. When do we know its finished with ANY size check?
	
	
	Currently pushes until we are dealing with a "1-subfamily" (eg, a single cell), then iterates over what that cell could be.
	Once that iteration is completed, it pops the second-to-last cell provided the cellSet is not empty, and returns if it IS empty. Provided it is not
	empty, it then calls itself with an incremented start index and incremented family size
	*/
};
///

///Definition private member function grid class checkFamilyFSoP
///Main handler for checking FSoP. Takes a family and performs the more complicated FSoP checks.
///As after changing potentials, previous checks become invalidated (new subfamilies could have been created), we will have to restart the check from the very beginning
///everytime we have a positive result; furthermore, it MAY be possible for a single cell to be in multiple subfamilies (one from each family it belongs), so we need
///to be sure when checking for exclusion based on already being in a subfamily, we know which family we are considering.
///cell** is to be interpreted as an array of pointers to cells
void grid::checkFamilyFSoP(cell** family, RCB rcb) {
	//For passed family, check for 2-Subfamilies, then 3-subfamilies, etc up to 8-subfamilies
	//To hold our temporary "subfamily" to check its signature
	std::vector<cell*> cellSet;
	for (short subFamilySize = 2; subFamilySize < 9; ++subFamilySize) {
		cellSet.clear();
		this->FSoPHelper(family, cellSet, rcb, 0, subFamilySize);
	}
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
			if (family[cellInFamily]->getPotential(potentialIndex)) {
				temp_index = potentialIndex;
				++hit_count;
			}
		if (hit_count == 1) {
			family[cellInFamily]->setAwaitingAssignmentTrue();
			//Debug
			if (debug) std::cout << "From lone potential check, pushing cell [" << family[cellInFamily]->getRow() << ", " << family[cellInFamily]->getColumn() << "] into queue with number " << temp_index + 1 << std::endl;
			//
			this->changePotentials(family[cellInFamily]->getRow(), family[cellInFamily]->getColumn(), family[cellInFamily]->getBlock(), temp_index + 1);
			this->awaiting_assignment.push(CellNum(family[cellInFamily], temp_index + 1));
		}
	}
	for (short potentialIndex = 0; potentialIndex < 9; ++potentialIndex) {
		temp_index = hit_count = 0;
		for (short cellInFamily = 0; cellInFamily < 9; ++cellInFamily) {
			if (family[cellInFamily]->getNumber() || family[cellInFamily]->isAwaitingAssignment()) continue;
			if (family[cellInFamily]->getPotential(potentialIndex)) {
				temp_index = cellInFamily;
				++hit_count;
			}
		}
		if (hit_count == 1) {
			family[temp_index]->setAwaitingAssignmentTrue();
			//Debug
			if (debug) std::cout << "From isolated value check, pushing cell [" << family[temp_index]->getRow() << ", " << family[temp_index]->getColumn() << "] into queue with number " << potentialIndex + 1 << std::endl;
			//
			this->changePotentials(family[temp_index]->getRow(), family[temp_index]->getColumn(), family[temp_index]->getBlock(), potentialIndex + 1);
			this->awaiting_assignment.push(CellNum(family[temp_index], potentialIndex + 1));
		}
	}
};

///End private member function grid class checkFamilyFSoN

///Definition private member function grid class changePotentials
///Is past a reference to a cell then changes the potential of the number the cell contains to false of all cells in that cells families
void grid::changePotentials(cell& CELL) {
	changePotentials(CELL.getRow(), CELL.getColumn(), CELL.getBlock(), CELL.getNumber());
};
///End private member function grid class changePotentials

///Definition private member function grid class changePotentials
///Is past four shorts (Row, Column, Block, Number) then changes the potential of the number to false of all cells in those families
void grid::changePotentials(short R, short C, short B, short N) {
	for (short i = 0; i < 9; ++i) {
		GRIDRF[R][i]->setPotentialFalse(N - 1);
		GRIDRF[i][C]->setPotentialFalse(N - 1);
		GRIDBB[B][i]->setPotentialFalse(N - 1);
	};
};
///End private member function grid class changePotentials
