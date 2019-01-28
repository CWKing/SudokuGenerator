#include "cell.h"
#include "others.h"

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
		cell* GRIDRF[9][9];
		cell* GRIDBB[9][9];
		std::vector<cell> GRID;
		std::vector<RowCol> poteCells;
};
