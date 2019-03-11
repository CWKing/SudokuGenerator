#include "cell.h"
//#include "others.h" //Might not need this
#include <queue>

class grid {
	public:
		grid();
		void printGrid() const;
		void checkColumns();
		void checkRows();
		void checkBlocks();
		std::vector<cell> const * const access; //For accessing but not modifying the contents of GRID; for debugging mostly
	private:
		void checkPotentialsSoleNum(cell &C);
		void initializeGrid();
		void changePotentials(cell& CELL);
		cell* GRIDRF[9][9];						//Grid Row First (ie, first index is row, second index is column)
		cell* GRIDBB[9][9];						//Grid By Block (ie, first index is block, second index is the subindex in the block)
		std::vector<cell> GRID;					//Grid as just an 81 cell vector; the elements of both GRIDRF and GRIDBB point to the elements in this
		std::vector<cell*> poteCells;			//Vector of pointers to cells containing the remaining potential occupiable cells; when doing the random assigning
												//of numbers, first a cell is chosen from here and then one of its potentials is randomly chosen
		std::queue<cell*> N2U;					//Need To Update; to hold cells which need to be updated
};

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
