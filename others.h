#ifndef OTHERS_H
#define OTHERS_H
#include <vector>

class RowCol {
public:
	//RowCol() : row(-1), column(-1) {};
	RowCol(short R, short C) : row(R), column(C) {};

private:
	short row;
	short column;
};

class C4N {
public:
	
private:
	short counter = 0;
	std::vector<RowCol> indecies;
};

#endif //OTHERS_H
