#include "cell.h"

using std::cout; using std::endl; using std::ostream;

///Definition cell class constructor
cell::cell(short R, short C, short B) : row(R), column(C), block(B), number(0), potentials{true, true, true, true, true, true, true, true, true}, byNecessity(false), inSubfamily{ false, false, false } {};
///End cell class constructor

///Definition public member function cell class getColumn
short cell::getColumn() const {
	return this->column;
};
///End public member function cell class getColumn

///Definition public member function cell class getRow
short cell::getRow() const {
	return this->row;
};
///End public member function cell class getRow

///Definition public member function cell class getBlock
short cell::getBlock() const {
	return this->block;
};
///End public member function cell class getBlock

///Definition public member function cell class getNumber
short cell::getNumber() const {
	return this->number;
};
///End public member function cell class getNumber

///Definition public member function cell class getPotentials
const bool* cell::getPotentials() const {
	const bool* potenials = this->potentials;
	return potenials;
};
///End public member function cell class getPotentials

///Definition public member function cell class getNecessity
bool cell::getNecessity() const {
	return this->byNecessity;
};
///End public member function cell class getNecessity
/*
///Definition public member function cell class setNumber
void cell::setNumber() {
	
};
///End public member function cell class setNumber
*/
///Definition public member function cell class setNumber
void cell::setNumber(short num) {
	this->number = num;
	for (short i = 0; i < 9; ++i) this->setPotentialFalse(i);
};
///End public member function cell class setNumber

///Definition public member function cell class setPotentialFalse
void cell::setPotentialFalse(short index) {
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
	for (short i = 0; i < 9; ++i) numPot += static_cast<short>(this->potentials[i]);
	return numPot;
};
///End public member function cell class NP

///Definition public member function cell class toggleSubfmailyBool
void cell::toggleSubfamilyBool(RCB rcb){
	this->inSubfamily[rcb] = !(this->inSubfamily[rcb]);
};
///End public member function cell class toggleSubfamilyBool

///Definition cell class member operator== overload
bool cell::operator==(const cell& rhs) const {
	if (this->NP() != rhs.NP()) return false;
	for (short i = 0; i < 9; ++i) if (this->potentials[i] != rhs.getPotentials()[i]) return false;
	return true;
};
///End cell class operator== overload

///Definition cell class non-member operator<< overload
ostream& operator<<(ostream& out, const cell& C) {
	out << "Number: " << C.getNumber() << " "
		<< "Row: " << C.getRow() << " "
		<< "Column: " << C.getColumn() << " "
		<< "Block: " << C.getBlock() << endl;
	return out;
};
///End cell class operator<< overload

///Definition cell class non-member operator+ overload
///To be used in FSoP checking
short* operator+(short* lhs, const cell& rhs) {
	for (short i = 0; i < 9; ++i) lhs[i] += static_cast<short>(rhs.getPotentials()[i]);
	return lhs;
};
///End cell class operator+ overload