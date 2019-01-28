#ifndef CELL_H
#define CELL_H
#include <iostream>

///cell class declaration
class cell {
	public:
		cell(short row, short column, short block);
		short getColumn() const;
		short getRow() const;
		short getBlock() const;
		short getNumber() const;
		bool* getPotentials();
		bool getNecessity() const;
		void setNumber(short num);
		void setPotentialFalse(short index);
		void setNecessityTrue();
	private:
		const short column;
		const short row;
		const short block;
		short number;
		bool potentials[9];
		bool byNecessity;
};
///End cell class declaration

///Declaration non-member overload operator<<
std::ostream& operator<<(std::ostream& s, cell C);
///End declaration non-member overload operator<<

#endif //CELL_H