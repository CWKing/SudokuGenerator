#ifndef OTHERS_H
#define OTHERS_H
#include <vector>

///Row-Column class; in last iterations used in grid initilization
///and value checking proceedures
class RowCol {
public:
	//RowCol() : row(-1), column(-1) {};
	RowCol(short R, short C) : row(R), column(C) {};
	short get_row() const { return row; }
	short get_col() const { return column; }

private:
	short row;
	short column;
};

///Count-For-Number; in last iteration used in value checking proceedures
class C4N {
public:
	C4N() : counter(0) {}

private:
	short counter;
	std::vector<RowCol> indecies;

	friend class grid;
};

#endif //OTHERS_H
