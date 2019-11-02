/*
	Binarnic Project

	(c) 2019
*/

#ifndef OPERATIONS_H
#define OPERATIONS_H

#define OP_NOT(x) (x == 1 ? 0 : 1)
#define OP_AND(x,y) (x & y)
#define OP_OR(x,y) (x || y) 
#define OP_IMP(x,y) ((x == 1 && y == 0) ? 0 : 1)
#define OP_EQ(x,y) (x == y ? 1 : 0) 

#endif