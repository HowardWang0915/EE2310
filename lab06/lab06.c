/* EE2310 Lb06. Unfriendly Knights
   107061112, 王昊文
   Date: 2018.10.29
*/

#include <stdio.h>

#define N 6

/* global variables */
int a[N][N] = {{0},{0}};	// The chessboard
int count = 1; 				// assigns every space a value	
int space_Remaining = N * N;	// counts space Remaining
/* prototypes */
void noput();	
void put();		
void print_Board();
int solution();

/********************************************************************
* main: the first testing place a[0][0] is assigned 1 first, which  *
*`		is an odd number. then, find out the 8 spaces that can't    *
*		be assigned a knight.Those spaces are assigned 2, which is  *
*		an even number. Then from those spaces which can't be 		*
*		assigned, Walk a L-shape, and those spaces can be assigned  *
*		a knight. It is obvious we can find the maximum number of   *
*		non-attacking knights by this pattern, because if we want   *
*		the maximum number of non-attacking knights, knights can    *
*       attck only eight spaces. At the end, pick all               *
*		the spaces which are assigned an even number, those are     *
*		spaces knights should be assigned, and others should be     *
*		empty.														*
********************************************************************/		
int main(void)
{
	a[0][0] = count; 	// the first testing space is assigned 1
	while (space_Remaining >= 0) {	// when there is space non-tested
		noput();		// find spaces can't be assigned
		put();			// find sapces can be assigned
	}
	printf("Solution with %d knights on a %dx%d board:\n",
	solution(), N, N); 	// print solution
	print_Board();		// print the board
	return 0;
}

/********************************************************************
* noput: if spaces = count, means they are the testing spaces.      *
*		 Test 8 spaces l-shpaed beside those testing spaces. test   *
*		 if those 8 spaces are outside the board, and be aware      *
*		 whether those sapces are tested or not. At last, give      *
*		 the tested sapces an even value to mark it.                *
********************************************************************/
void noput() {
	int i, j;	// loop index
	/* count % 2 == 1 means current is testing spaces can't 
	put knight */

	for (i = 0; count % 2 == 1 && i < N; i++) {
		for (j = 0; j < N; j++) {
			/* if a[i][j] == count, then a[i][j] is the testing space
			*/
			if (a[i][j] == count) { 
				// test if l-shape exist and not assigned
				if (i - 1 >= 0 && j - 2 >= 0 && a[i - 1][j - 2] == 0)
				{
					a[i - 1][j - 2] = count + 1;	// make it even
					space_Remaining--; 	// tested space + 1
				}
				if (i - 2 >= 0 && j - 1 >= 0 && a[i - 2][j - 1] == 0)
				{
					a[i - 2][j - 1] = count + 1;
					space_Remaining--;
				}
				if (i - 2 >= 0 && j + 1 <= N && a[i - 2][j + 1] == 0)
				{
					a[i - 2][j + 1] = count + 1;
					space_Remaining--;
				}
				if (i - 1 >= 0 && j + 2 <= N && a[i - 1][j + 2] == 0)
				{
					a[i - 1][j + 2] = count + 1;
					space_Remaining--;
				}
				if (i + 1 <= N && j + 2 <= N && a[i + 1][j + 2] == 0)
				{ 
					a[i + 1][j + 2] = count + 1;
					space_Remaining--;
				}
				if (i + 2 <= N && j + 1 <= N && a[i + 2][j + 1] == 0)
				{
					a[i + 2][j + 1] = count + 1;
					space_Remaining--;
				}
				if (i + 2 <= N && j - 1 >= 0 && a[i + 2][j - 1] == 0)
				{
					a[i + 2][j - 1] = count + 1;
					space_Remaining--;
				}
				if (i + 1 <= N && j - 2 >= 0 && a[i + 1][j - 2] == 0)
				{ 
					a[i + 1][j - 2] = count + 1;
					space_Remaining--;
				}
			}
		}
	}
	count++; 	// count brings the checking process to put()
}

/********************************************************************
* put: function finds out sapces where to put the knight. It works  *
* 	   out similarily to noput(). If the knight goes from the space *
* 	   where you can't put the knight, it is the space you can put  *
*	   the knight. We use "count" to mark the spaces. Those sapces  *
*	   value are odd.												*
********************************************************************/
void put() {
	int i, j; // loop index
	/* if count is even means current checking where knight should 
	put */
	for (i = 0; count % 2 == 0 && i < N; i++) {
		for (j = 0; j < N; j++) {
			// if a[i][j] is the current checking space 
			
			if (a[i][j] == count) { 
				// test if l-shaped sides exists
				if (i - 1 >= 0 && j - 2 >= 0 && a[i - 1][j - 2] == 0)
				{ 
					a[i - 1][j - 2] = count + 1; // make it odd
					space_Remaining--;	// tested space + 1
				}
				if (i - 2 >= 0 && j - 1 >= 0 && a[i - 2][j - 1] == 0)
				{
					a[i - 2][j - 1] = count + 1;
					space_Remaining--;
				}
				if (i - 2 >= 0 && j + 1 <= N && a[i - 2][j + 1] == 0)
				{ 
					a[i - 2][j + 1] = count + 1;
					space_Remaining--;
				}
				if (i - 1 >= 0 && j + 2 <= N && a[i - 1][j + 2] == 0)
				{
					a[i - 1][j + 2] = count + 1;
					space_Remaining--;
				}
				if (i + 1 <= N && j + 2 <= N && a[i + 1][j + 2] == 0)
				{
					a[i + 1][j + 2] = count + 1;
					space_Remaining--;
				}
				if (i + 2 <= N && j + 1 <= N && a[i + 2][j + 1] == 0)
				{ 
					a[i + 2][j + 1] = count + 1;
					space_Remaining--;
				}
				if (i + 2 <= N && j - 1 >= 0 && a[i + 2][j - 1] == 0)
				{
					a[i + 2][j - 1] = count + 1;
					space_Remaining--;
				}
				if (i + 1 <= N && j - 2 >= 0 && a[i + 1][j - 2] == 0)
				{
					a[i + 1][j - 2] = count + 1;
					space_Remaining--;
				}
			}
		}
	}
	count++; // count++ brings the process to noput()
}

/********************************************************************
* solution: in the put() funtion, we know every space with an odd   *
* 			value, then it is the place to put the knight. Count    *
*			those spaces and turn it into answer.					*
********************************************************************/
int solution() {
	int i, j, ans = 0;	// i,j are loop index, ans is the result
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (a[i][j] % 2 == 1)	// every odd number is as answer
				ans++;
		}
	}
	return ans;	// it retruns the ans to main
}

/********************************************************************
* print_Board: prints out the result on the board, if the value of  *
*  			   the space is odd, then it is the space to put the    *
*   		   knight. Conversely, it should be an empty space.     *
********************************************************************/
void print_Board() {
	int i, j;	// loop index
	printf("    ");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (a[i][j] % 2 == 1)	// odd number is answer
				printf(" o");
			if (a[i][j] % 2 == 0)	// even number is an empty space
				printf(" .");
		}
		printf("\n");
		printf("    ");
	}
}
