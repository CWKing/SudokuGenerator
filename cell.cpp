#include "cell.h"
#include <cassert>

using std::cout; using std::endl; using std::ostream;


///Definition cell class constructor
cell::cell(short R, short C, short B) : number(0), row(R), column(C), block(B), byNecessity(false){
	for(short i = 0; i < 9; ++i) potentials[i] = true;
};
///End cell class constructor

///Definition public member function cell class getColumn
short cell::getColumn() const {
	assert(column >= 0 && column <= 8);
	return column;
};
///End public member function cell class getColumn

///Definition public member function cell class getRow
short cell::getRow() const {
	assert(row >= 0 && row <= 8);
	return row;
};
///End public member function cell class getRow

///Definition public member function cell class getBlock
short cell::getBlock() const {
	assert(block >= 0 && block <= 8);
	return block;
};
///End public member function cell class getBlock

///Definition public member function cell class getNumber
short cell::getNumber() const {
	assert(number >= 0 && number <= 9);
	return number;
};
///End public member function cell class getNumber

///Definition public member function cell class getPotentials
bool* cell::getPotentials() {
	return potentials;
};
///End public member function cell class getPotentials

///Definition public member function cell class getNecessity
bool cell::getNecessity() const {
	return byNecessity;
};
///End public member function cell class getNecessity

///Definition public member function cell class setNumber
void cell::setNumber(short num) {
	assert((num >= 1 && num <= 9) && getPotentials()[num - 1]);
	number = num;
	for (short i = 0; i < 9; ++i) this->setPotentialFalse(i);
};
///End public member function cell class setNumber

///Definition public member function cell class setPotentialFalse
void cell::setPotentialFalse(short index) {
	assert(index >= 0 && index <= 8);
	potentials[index] = false;
};
///End public member function cell class setPotentialFalse

///Definition public member function cell class setNecessityTrue
void cell::setNecessityTrue() {
	byNecessity = true;
};
///End public member function cell class setNecessityTrue

///Definition cell class non-member operator<< overload
ostream& operator<<(ostream& s, cell C) {
	s << "Number: " << C.getNumber() << " "
		<< "Row: " << C.getRow() << " "
		<< "Column: " << C.getColumn() << " "
		<< "Block: " << C.getBlock() << endl;
	return s;
};
///End cell class operator<< overload