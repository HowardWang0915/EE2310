/* EE2310 Lab07, Matrix Determinants
   107061112, 王昊文
   Date: 2018 / 11 / 7
*/
#include <stdio.h>

#if !defined(N)
#define N 3
#endif

/* global varaibles */
long int A[N][N];	// input matrix
long int B[N];		// array for permutation
int sgn = 1;	// the sgn value

/* prototypes */
int Pandita();	// this function does the permutation
int sgn_Calculator(int swap_Count);	// sgn function 7.2
long int Product(int sgn);		// multiplies the elements
void print_Matrix();		// simply prints the input

/********************************************************************
* main: in main, input an matrix, it generate the B[N] array for the*
* permutation. it will call the funciont needed for calculating the *
* determinant. Finally, it will print out the input matrix and the  *
* determinant.                                                      *
********************************************************************/
int main(void)
{
	int i, j;	// loop index
	long int determinant = 0;	// initial determinant value
	int swap;		// if swap is 0, means no more permutations found
	for (i = 0; i < N; i++) {	// input matrix
		for (j = 0; j < N; j++) {
			scanf("%ld", &A[i][j]);
		}
	}
	for (i = 0; i < N; i++) {	// generate B[N] for permutation
		B[i] = i;
	}
	determinant += Product(1);	// the first element-selecting 
	swap = Pandita();			// then do the Pandita
	do  {
		sgn = sgn_Calculator(swap);	// calculate sgn
		determinant += Product(sgn); // add the product to determinant
		swap = Pandita();			// then Pandita again
	}	while (swap);	
	// if there are no more permtation found, then print result
	print_Matrix();	// print result
	printf("\bDet = %ld\n", determinant);
	return 0; 
}

/********************************************************************
* Pandita: this function is from lab05, it will do the Pandita      *
* algorithm                                                         *
********************************************************************/
int Pandita()
{
	int i, j, k;	// loop index
	int temp;		// for swapping
	int stay;		// a variable for jumping out the loop
	int swap_Count = 0;	// swap_Count for calculating sgn
	for (i = N - 2, stay = 1, j = -1; i >= 0 && stay == 1; i--) {
		/* let i count from the back and count down. the first
	   	   B[i] < B[i + 1] is the biggest B[j]. Once found, stay == 2
		   will jump out the for loop. we initialize j == -1, since
		   it is impossible for j == -1, if no j found, the value remains
		   and it's time to jump out the while loop */
		
		if (B[i] < B[i + 1]) {	
			j = i;
			stay++;
		}
	}
	if (j == -1)
		return 0;	// no more permutations found
	for (k = N - 1; k >= 0 && stay == 2; k--) {
		/* count k from the back, the first one to find is the
		   biggest B[k] > B[j], then swap */
		
		if (B[k] > B[j]) {	
			temp = B[k];	// swapping
			B[k] = B[j];
			B[j] = temp;
			swap_Count++;	// also counts the times of swapping
			stay++;			// jump out
		}
	}
	for (i = j + 1, k = N - 1; i < k; i++, k--, swap_Count++) {
		/* we want to swap from B[j + 1] to B[N - 1], let the
		   B[j + 1] and B[N - 1] swap first, then B[j + 2] and B[N - 2]
			.... and so on, until the two arrays are the same
			or neighboring */
		
		temp = B[i];	// swapping
		B[i] = B[k];
		B[k] = temp;
	}
	return swap_Count;	// return swap_Count for sgn_Calculator
}

/******************************************************************** 
* sgn_Calculator: this is function 7.2 in the assignment. sgn is    *
* initialized as 1. It will return sgn of the selected elements.	*
********************************************************************/
int sgn_Calculator(int swap_Count)
{
	// function only depends on swap_Count is odd or even
	if (swap_Count % 2 == 0)	
		return sgn;		// sgn(m) = (-1)^swap_Count * sgn(m - 1)
	else
		return -1 * sgn;
}

/********************************************************************
* Product: this function will multiply all the selected element for *
*          the determinant.	It will retrun the result.				*
********************************************************************/
long int Product(int sgn)
{
	int i;	// loop index
	long int product = 1;	// product is initialized as 1 
	// selecting elements by the permutation result
	for (i = 0; i < N; i++) {	
		product *= A[i][B[i]];
	}
	product *= sgn;	// positive or negative is determined by sgn
	return product;
}

/********************************************************************
* print_Matrix: this function simply prints the input Matrix. 		*
********************************************************************/
void print_Matrix() 
{ 
	int i, j;	// loop index
	printf("Input Matrix is\n ");
	for (i = 0; i < N; i++) {	// print
		for (j = 0; j < N; j++) {
			printf("% d", A[i][j]);
		}
		printf("\n ");
	}
}
