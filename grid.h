#ifndef GRID_H
#define GRID_H

#include "cell.h"
//#include "others.h" //Might not need this
#include <queue>

///THE ONLY SEMI-GLOBAL VARIABLE
extern bool debug;
///DO NOT PANIC

///
class CellNum {
	CellNum(cell* _CELL, short _NUMBER) : CELL(_CELL), NUMBER(_NUMBER) {};
	cell* CELL;
	short NUMBER;

	friend class grid;
};
///

///potentialSumContainer helper class declaration
///Intention is to be used for FSoP checking
class potentialSumContainer {
	potentialSumContainer();
	short hasOne();	//Might not be necessary
	bool hasSubfamSignature(short);
	void reset();
	potentialSumContainer& operator+=(const cell*);
	short sum[9];

	friend class grid;
};
///end potenailSumContainer class declaration

class grid {
	public:
		grid();
		void printGrid() const;
		void checkRowsFSoP(const cell&);					///Wrapper for checkFamilyFSoP to check row families
		void checkColumnsFSoP(const cell&);					///Wrapper for checkFamilyFSoP to check column families
		void checkBlocksFSoP(const cell&);					///Wrapper for checkFamilyFSoP to check block families
		void checkRowsFSoN(const cell&);					///Wrapper for checkFamilyFSoN to check row families
		void checkColumnsFSoN(const cell&);					///Wrapper for checkFamilyFSoN to check column families
		void checkBlocksFSoN(const cell&);					///Wrapper for checkFamilyFSoN to check block families
		short getpoteCellSize() const;						///To get the number of potential cells which still need to have a number assigned
		short getpoteCellIndex(const cell&) const;			///Get the index of a cell in the poteCells vector; used for deleting those from the vector
		void workThroughQueue();							///Iterate through the awaiting assignment queue, assigning numbers to cells
		void assignRandom();								///Assign a random cell from poteCells one of its random potentials
		void initiateAllChecks(const cell*);				///Initiate all checks on a given cell and its families

	private:
		void initializeGrid();								///Main handler for constructing the sudoku grid
		void FSoPChangePotentials(std::vector<cell*>&, RCB);
		void FSoPsubFamCheck(std::vector<cell*>&, RCB);
		void FSoPHelper(cell**, std::vector<cell*>&, RCB, short, short);
		void checkFamilyFSoP(cell**, RCB);					///Main FSoP check handler
		void checkFamilyFSoN(cell**);						///Main FSoN check handler
		void changePotentials(cell&);						///Takes a reference to a cell and changes the potentials of all the cells in the passed cells families
															///to exclude that cells held number
		void changePotentials(short, short, short, short);	///To change the potentials of all cells in the families associated with the first 3 shorts (R, C, B)
															///to exclude the number passed by the fourth short
		cell* GRIDRF[9][9];									///Grid Row First (ie, first index is row, second index is column)
		cell* GRIDCF[9][9];									///Grid Column First (ie, first index is column, second index is row. Simplifies FSoP checking; trust me)
		cell* GRIDBB[9][9];									///Grid By Block (ie, first index is block, second index is the subindex in the block)
		std::vector<cell> GRID;								///Grid as just an 81 cell vector; the elements of both GRIDRF and GRIDBB point to the elements in this
		std::vector<cell*> poteCells;						///Vector of pointers to cells containing the remaining potential occupiable cells; when doing the random
															///assigning of numbers, first a cell is chosen from here and then one of its potentials is randomly chosen
		std::queue<CellNum> awaiting_assignment;			///To hold a tuple of a cell and number; the cell is awaiting assignment of that number

		friend class cell;	//Might not be necessary
};

#endif // !GRID_H
/*
	Blocks and block subindecies are designated left-to-right, row-by-row
	in the example below, the number in  each cell is the block subindex of
	that cell

	+---------+---------+---------+ 
	|[0][1][2]|[0][1][2]|[0][1][2]|
	|[3][4][5]|[3][4][5]|[3][4][5]|
	|[6][7][8]|[6][7][8]|[6][7][8]|
	+---------+---------+---------+
	|[0][1][2]|[0][1][2]|[0][1][2]|
	|[3][4][5]|[3][4][5]|[3][4][5]|
	|[6][7][8]|[6][7][8]|[6][7][8]|
	+---------+---------+---------+
	|[0][1][2]|[0][1][2]|[0][1][2]|
	|[3][4][5]|[3][4][5]|[3][4][5]|
	|[6][7][8]|[6][7][8]|[6][7][8]|
	+---------+---------+---------+

	In the grid below, the cells contain the number of their associated block

	+---------+---------+---------+
	|[0][0][0]|[1][1][1]|[2][2][2]|
	|[0][0][0]|[1][1][1]|[2][2][2]|
	|[0][0][0]|[1][1][1]|[2][2][2]|
	+---------+---------+---------+
	|[3][3][3]|[4][4][4]|[5][5][5]|
	|[3][3][3]|[4][4][4]|[5][5][5]|
	|[3][3][3]|[4][4][4]|[5][5][5]|
	+---------+---------+---------+
	|[6][6][6]|[7][7][7]|[8][8][8]|
	|[6][6][6]|[7][7][7]|[8][8][8]|
	|[6][6][6]|[7][7][7]|[8][8][8]|
	+---------+---------+---------+
*/
