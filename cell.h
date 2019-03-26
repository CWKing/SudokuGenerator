#ifndef CELL_H
#define CELL_H
#include <iostream>

enum RCB { ROW = 0, COLUMN = 1, BLOCK = 2 };

///cell class declaration
class cell {
	public:
		cell(short row, short column, short block);	///Default ctor; assigns the row, column, and block numbers to the cell. Initialized when the main grid is initialized
		short getColumn() const;					///Returns the column number of the cell
		short getRow() const;						///Returns the row number of the cell
		short getBlock() const;						///Returns the block number of the cell
		short getNumber() const;					///Returns the number in the cell
		const bool* getPotentials() const;			///Returns a pointer to the array of potential numbers the cell can contain
		bool getNecessity() const;					///Returns a bool of whether or not the number in the cell was set by necessity (true) or randomly (false)
		//void setNumber();							///Sets the number to be contained in the cell based on a FSoN
		void setNumber(short num);					///Sets the number to be contained in the cell based on what is passed (this is the random assignment)
		void setPotentialFalse(short index);		///Sets the bool in the potential array at the given index to false
		void setNecessityTrue();					///Sets the bool of whether or not the cell was given a specific number by necessity to true
		short NP() const;							///Number of Potentials; returns a short to the number of potentials the cell contains
		void toggleSubfamilyBool(RCB);
		bool operator==(const cell&) const;			///Overload cell operator==

	private:
		const short row;							///The row family the cell is in
		const short column;							///The column family the cell is in
		const short block;							///The block family the cell is in
		short number;								///The number the cell contains
		bool potentials[9];							///Array of bools; the index of each bool is one less than the number that could potentially go in the cell 
		bool byNecessity;							///Bool specifying whether or not the number in the cell was set by necessity (true) or randomly (false)
													///Cells marked byNecessity will not be revealed when the sudoku is printed 
		bool inSubfamily[3];						///Bools specifying whether or not the current cell is in a row/column/block subfamily; used by FSoP checker
};
///End cell class declaration

///Declaration non-member overload operator<<
///Passes to the ostream object s the number, row, column, and block of the cell C
std::ostream& operator<<(std::ostream& s, const cell& C);
///End declaration non-member overload operator<<

///Declaration non-member overload operator+
///Piecewise addition of the potentials in the cells used for generating cell set signatures which are intended ot be used in the FSoP checker
short* operator+(short*, const cell&);
///End declaration non-member overload operator+

#endif //CELL_H