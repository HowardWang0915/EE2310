/* EE2310 Lab07, Matrix Determinants
   107061112, 王昊文
   Date: 2018 / 11 / 7
*/
#include <stdio.h>

#if !defined(N)
#define N 8
#endif

/* global variables*/
int B[N];       // the one dimensional matrix for calculation
int sgn = 1;        // for the sgn
/* prototypes */
int Pandita(int B[N]);	// this function does the permutation

/********************************************************************
* main: in main, input an matrix, it generate the B[N] array for the*
* permutation. it will call the funciont needed for calculating the *
* determinant. Finally, it will print out the input matrix and the  *
* determinant.                                                      *
********************************************************************/
int main(void) {
    int i, j;	// loop index
    int A[N][N];    // the intput matrix
    long int product = 1;           // product of each term adding together
	long int determinant = 0;	// initial determinant value
	for (i = 0; i < N; i++) {	// input matrix
		for (j = 0; j < N; j++) {
			scanf("%ld", &A[i][j]);
		}
	}
    for (i = 0; i < N; i++) {	// generate B[N] for permutation
		B[i] = i;
	}
    // calculating the product of each term
    do {
        product = 1;
        for (i = 0; i < N; i++) {	
		    product *= A[i][B[i]];      // calculating the terms using Pandita
	    }
        product *= sgn;
	    determinant += product;
        sgn = Pandita(B);       // call the Pandita for permutation and sgn
    } while(sgn != 0);          // until no permutation found
    // print out the matrix
    printf("Input Matrix is\n");
	for (i = 0; i < N; i++) {	// print
        printf("  ");
		for (j = 0; j < N; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
    printf("Det = %ld\n", determinant); // print answer
    return 0;
}
/********************************************************************
* Pandita: this function is from lab05, it will do the Pandita      *
* algorithm                                                         *
********************************************************************/
int Pandita(int B[N]) {
    int i, j, k, temp;            // loop index, temp for swap
    int found = 0;          // found flag
    int swap_Count = 0;         // swap Count calculation
    // starting from the back to find largest j
    for (j = N - 2; j >= 0 && !found; j--) {
        if (B[j] < B[j + 1]) {      // a[j] < a[j + 1]
        // staring from the back to find the largest k
            for (k = N - 1; k >= 0 && !found; k--) {
                if (B[j] < B[k]) {  // a[j] < a[k]
                    found = 1;      // set flag to found
                    swap_Count++;   // swap Count += 1
                    temp = B[j];    // swap a[j] with a[k]
                    B[j] = B[k];
                    B[k] = temp;
                    // reversing the series
                    for (i = j + 1, k = N - 1; i < k; i++, k--, swap_Count++) {
                        temp = B[i];
                        B[i] = B[k];
                        B[k] = temp;
                    }
                }
            }   
        }
    }
    if (!found)
        return 0;        // permutation ends
    else if (swap_Count % 2 == 0)
        return sgn;		// sgn(m) = (-1)^swap_Count * sgn(m - 1)
    else    
        return -1 * sgn;
}
