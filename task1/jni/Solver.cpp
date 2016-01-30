#include "Solver.h"
#include <stdlib.h>
#include <stdio.h>



/**
 * Implementation of Backtrack algorithm
 * Bogdan Vaneev
 * Innopolis University
 */
// pointer to field
typedef int field_ptr[][9];

// unassigned cell value
#define UNASSIGNED (0)

JNIEXPORT jintArray JNICALL Java_Solver_solve (JNIEnv * env, jobject obj, jintArray inp){
	int field[9][9];
	
	const int size = 81;

	jint * cells = env->GetIntArrayElements(inp, NULL);
	for(int i=0;i < size; i++)
	{
		int row = i / 9;
		int col = i % 9;
		field[row][col] = cells[i];
	}

	jintArray result = env->NewIntArray(size);
	jint fill[size];
	if(solve(field)){
		for(int i=0; i<9; i++){
			for(int j=0;j<9; j++){
				fill[i*9 + j] = field[i][j];
			}
		}	
	}
	else{
		// no solution
		for(int i=0; i<size; i++){
			fill[i] = 0;
		}
	}

	env->SetIntArrayRegion(result, 0, size, fill);

	return result;
}

// determines, if number 'element' fits into 'field[row][col]'
bool is_correct(const field_ptr field, int row, int col, int element)
{
	// check row
	for (int i = 0; i < 9; i++) if (field[row][i] == element) return false;
	
	// check column
	for (int i = 0; i < 9; i++) if (field[i][col] == element) return false;

	// check 3x3 box
	int lborder = row - row % 3;
	int tborder = col - col % 3;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			if (field[lborder + i][tborder + j] == element) return false;

	return true;
}

// are there any empty cells?
bool find_unassigned(const field_ptr field, int& row, int &col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (field[row][col] == UNASSIGNED) return true;
	return false;
}

// solve field
bool solve(field_ptr field)
{
	int row, col;
	if (!find_unassigned(field, row, col)) return true;

	for (int n = 1; n <= 9; n++)
	{
		if (is_correct(field, row, col, n))
		{
			field[row][col] = n;

			if (solve(field))
				return true;

			field[row][col] = UNASSIGNED;
		}
	}
	return false;
}
