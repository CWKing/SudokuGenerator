#include "cell.h"

#ifdef DEBUG
#include <cassert>
#endif

using std::cout; using std::endl; using std::ostream;


///Definition cell class constructor
cell::cell(short R, short C, short B) : number(0), row(R), column(C), block(B), byNecessity(false){
	for(short i = 0; i < 9; ++i) this->potentials[i] = true;
};
///End cell class constructor

///Definition public member function cell class getColumn
short cell::getColumn() const {
#ifdef DEBUG
	assert(column >= 0 && column <= 8);
#endif
	return this->column;
};
///End public member function cell class getColumn

///Definition public member function cell class getRow
short cell::getRow() const {
#ifdef DEBUG
	assert(row >= 0 && row <= 8);
#endif
	return this->row;
};
///End public member function cell class getRow

///Definition public member function cell class getBlock
short cell::getBlock() const {
#ifdef DEBUG
	assert(block >= 0 && block <= 8);
#endif
	return this->block;
};
///End public member function cell class getBlock

///Definition public member function cell class getNumber
short cell::getNumber() const {
#ifdef DEBUG
	assert(number >= 0 && number <= 9);
#endif
	return this->number;
};
///End public member function cell class getNumber

///Definition public member function cell class getPotentials
bool* cell::getPotentials() {
	return this->potentials;
};
///End public member function cell class getPotentials

///Definition public member function cell class getNecessity
bool cell::getNecessity() const {
	return this->byNecessity;
};
///End public member function cell class getNecessity

///Definition public member function cell class setNumber
void cell::setNumber(short num) {
#ifdef DEBUG
	assert((num >= 1 && num <= 9) && getPotentials()[num - 1]);
#endif
	this->number = num;
	for (short i = 0; i < 9; ++i) this->setPotentialFalse(i);
};
///End public member function cell class setNumber

///Definition public member function cell class setPotentialFalse
void cell::setPotentialFalse(short index) {
#ifdef DEBUG
	assert(index >= 0 && index <= 8);
#endif
	this->potentials[index] = false;
};
///End public member function cell class setPotentialFalse

///Definition public member function cell class setNecessityTrue
void cell::setNecessityTrue() {
	this->byNecessity = true;
};
///End public member function cell class setNecessityTrue

///Definition public member function cell class NP
short cell::NP() const {
	short numPot = 0;
	for (size_t i = 0; i < 9; ++i) numPot += static_cast<short>(this->potentials[i]);
	return numPot;
};
///End public member function cell class NP

///Definition cell class member operator== overload
bool cell::operator==(const cell& rhs) const {
	if (this->NP() != rhs.NP()) return false;
	for (size_t i = 0; i < 9; ++i) if (this->potentials[i] != rhs.potentials[i]) return false;
	return true;
};
///End cell class operator== overload

///Definition cell class non-member operator<< overload
ostream& operator<<(ostream& out, cell C) {
	out << "Number: " << C.getNumber() << " "
		<< "Row: " << C.getRow() << " "
		<< "Column: " << C.getColumn() << " "
		<< "Block: " << C.getBlock() << endl;
	return out;
};
///End cell class operator<< overload