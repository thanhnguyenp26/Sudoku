/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Thanh Nguyen Pham (Student number: 1166068)
   Dated:     10/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/
#define DOT '.'
#define DASH_LINE "------+-------+------"
#define SPACE ' '
#define VERTICAL_LINE '|'
#define UNKNOWN_VAL 0
#define ROW 0
#define COL 1

void do_stage_1(int A[],int array_len);
void read_int_array(int A[], int maxvals);
void do_stage_2(int A[], int array_len);
void do_stage_3(int A[], int array_len);
int count_unknown_cell(int A[], int array_len);

/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char *argv[]) {
	int sudoku[NCLL] = {0};    
	fill_c2s();
	
	printf("\n");
	
    do_stage_1(sudoku, NCLL);
    
    printf("\n");
    
    do_stage_2(sudoku, NCLL);   
    do_stage_3(sudoku, NCLL);
    
	/* all done, so pack up bat and ball and head home */
	return 0;
}

/****************************************************************/

void
do_stage_1(int A[],int array_len) {
	
    int i, unknowns;  
    
    read_int_array(A, array_len);
    unknowns = count_unknown_cell(A, array_len);
    
    for (i=0; i<array_len; i++) {
    
        // only needs space for the values in the middle
        if (i%NDIG != 0) {
            printf("%c", SPACE);
        }
        
        // dash line every 3 rows
        if (i>0 && i%(NDIM*NDIG) == 0) {            
            printf("%s\n", DASH_LINE);
        }
        
        // and print '.' as an unknown cell
        if (A[i] == UNKNOWN_VAL) {
            printf("%c", DOT); 
            
        // if the cell already has a value, print that value
        } else {
            printf("%d", A[i]);
        }
        
        // a new line if a row has enough 9 values
        if (((i+1)%NDIG) == 0) {
            printf("\n");
        
        // insert a "|" character every 3 values
        } else if ((i+1)%NDIM == 0) {
            printf(" %c", VERTICAL_LINE);
        
        }
    }
    printf("\n");
    printf("%2d cells are unknown", unknowns);
    printf("\n");
}

/****************************************************************/

void 
do_stage_2(int A[], int array_len) {

	// create a counter for every value when looping through a row
	// the values range from 0-9
	int frequency[NDIG + 1];
	int i, j, z, mapped_val;
	int cell;
	int row, column, square, set;
	int diff_vio = 0, violations = 0;
	int set_change;
	
	// loop through 27 sets of the sudoku
	for (i=0; i<NSET;i++) {
		
		// a new set is investigated in every new loop
		set_change = 1;
		
		// initialise all counters to zero
		for (z=0; z <= NDIG; z++) {
				frequency[z] = 0;
		}
		
		// loop through 9 cells in a row
		for (j=0; j<NDIG; j++) {
			cell = s2c[i][j];
			
			// if there is a value in that cell
			if (A[cell] != UNKNOWN_VAL) {
				
					// that value acts as an index to get its frequency					
					mapped_val =  A[cell];
					
					// the frequency of that value increments by 1 since we
					// just find it
					frequency[mapped_val] += 1;
			}
		}
		
		for (mapped_val=0; mapped_val <= NDIG; mapped_val++) {
			
		// only detect violation if frequency is larger than 1			
			if (frequency[mapped_val] > 1) {
				violations += 1;
				
				// if we are in a new set, then increments the 
				// violations count from distinct sets
				if (set_change) {
					diff_vio += 1;
				}
				
				// record which set we are in
				set = i;
				
				// set numbers of rows
				if (set < 9) {
					
					// sets for rows count from 0-8, but rows count from 1-9
					row = set + 1;
					printf("set %2d (row %d): ", set, row);
					
				// set numbers of columns	
				} else if (set >= 9 && set < 18) {
					
					// sets for columns count from 9-17, but columns count 
					// from 1-9
					column = set - 9 + 1;
					printf("set %2d (col %d): ", set, column);
					
				// set numbers of small squares
				} else {
					
					// sets for small squares count from 9-17, but small
					// squares count from 1-9
					square = set - 18 + 1;
					printf("set %2d (sqr %d): ", set, square);
				}
				
				// print the frequency of the values which violate
				printf("%d instances of %d\n",frequency[mapped_val], 
												mapped_val);
				
				// continue to loop through the same set
				set_change = 0;			
			}	
		}			
	}
	
	if (violations) {
		printf("\n%d different sets have violations\n", diff_vio);
		printf("%d violations in total\n", violations);
		exit(EXIT_FAILURE);		
	}		
	
	return;
}	

/****************************************************************/
void
do_stage_3(int A[], int array_len) {
	
	// an array to store the possible values that can fill each unknown cell
	int B[NCLL] = {0};
	
	// create a counter for every value when looping through a row
	// the values range from 0-9
	int frequency[NDIG + 1];
	
	int i;
	int unknowns, beg_unknowns;
	int set_num, cell_num, mapped_val;	
	int possibility;	
	int row, col;
	
	// compute the number of unknown cells
	unknowns = count_unknown_cell(A, array_len);
	
	// if there still exits unfilled cells
	while (unknowns) {
		
		// record the number of unknown cells at the beginning of each loop
		beg_unknowns = unknowns;
		
 		// check every cell
		for (i=0; i<array_len; i++) {
			
			// if go through an unknown cell
			if (A[i] == UNKNOWN_VAL) {
				
				// have not known what possible values for that cell are
				possibility=0;
			
				// initialise all counters to zero
				for (int z=0; z <= NDIG; z++) {
					frequency[z] = 0;
				}
				
				// check 3 sets containing that cell
				for (int j=0; j<NDIM; j++) {
					
					set_num = c2s[i][j];
									
					// compute the total frequencies of each value in 3 sets
					for (int k=0; k<NDIG; k++) {
						
						// record which cell we are checking
						cell_num = s2c[set_num][k];
						
						// the value of that cell acts an index to get its
						// frequency
						mapped_val = A[cell_num];
						
						// not record the unknown value
						if(mapped_val != UNKNOWN_VAL) {
							frequency[mapped_val] += 1;
							
						}
					}
				}
				
				// a value with a frequency 0 is a possibility
				for (mapped_val=1; mapped_val <= NDIG; mapped_val++) {
					
					if (frequency[mapped_val] == 0) {
						
						// at the beginning, the value of the unknown cell 
						// is 0
						if (possibility == 0) {
							
							// now we have a possible value for it
							possibility = mapped_val;							
							
						// if there is another possibility, we would not know
						// which one to choose, so move on to another cell
						} else {
							
							// reset the possibility again							
							possibility = 0;
							break;
						}		
						
					}										
				}
				
		        // if there is only one possible value
				if (possibility) {
					
					// decrease the number of unknown cells
					unknowns -= 1;
					
					// record the possibility to the index corresponding to 
					// the cell number of that unknown cell
					B[i] = possibility;		
				}				
			}	
		}
		
		// having checked through a whole row
		// fill the possibilities into the unknown cells
		
		// after looping through all cells, we can fill some cells, so the
		// number of unknowns decreased
		if (beg_unknowns != unknowns) {
			printf("strategy one\n");
			
			for(int val=0;val < NCLL;val++){
				
				// only fill values for unknown cells
				if (B[val] != 0 && A[val] == UNKNOWN_VAL) {
					A[val] = B[val];		
					
					// sets for rows count from 0-8, but rows count from 1-9
					row = c2s[val][ROW] + 1;
					
					// sets for columns count from 9-17, but columns count 
					// from 1-9
					col = c2s[val][COL] - 9 + 1;
					
					printf("row %d col %d must be %d\n", row, col, A[val]);					
				}	
			}			
			printf("\n");
			
		// if after looping through all cells, we can't find any new
		// possibilities, stop this strategy
		} else {
			break;
		}
		
	}
	
	// print the finished sudoku after strategy one
	do_stage_1(A, array_len);
	
	// if we have filled all the unknown cells
	if (unknowns == 0) {
		printf("\n");
		printf("ta daa!!!\n");
	}
}


/****************************************************************/
// other helper functions 

void
read_int_array(int A[], int maxvals) {	
    int next, n = 0;  
    while (scanf("%d", &next) == 1) {
    	
    	// return if we have looped through the end of the array
        if (n == maxvals) {
            return;
        } else {
        	
        	// read the values given into the array
            if (next != '\n'){
                 A[n] = next;
                 n++;
             }
        }
    }  
}


int
count_unknown_cell(int A[], int array_len) {
	int count = 0;
	for (int i=0; i<array_len; i++) {
		if (A[i] == 0) {
			count += 1;
		}	
	}
	return count;
}


// algorithms are fun
/****************************************************************/
