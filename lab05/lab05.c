/* EE2310 Lab05. Permutations
107061112, 王昊文
Date: 2018.10.22
*/

#include <stdio.h>
#define N 7						// macro N to determine the array

int main(void) {
    int i, j, k, a[N], temp, counter = 0;
    int last = 0, found = 0;   // flag for last pemutation and found permutation
    /* i, j, k are loop index for the permutation,
       a[N] will store the array, 
       temp is for swapping
       counter is for recording the number of permutation
    */
    printf("permutation #%d: ", ++counter);	// first line
    for (i = 0; i < N; i++) {
        a[i] = i + 1;
        printf("%d ", a[i]);        // print out first permutation
    }
    printf("\n");
    while (!last) {                 // if not last permutation
        found = 0;
        // starting from the back to find largest j
        for (j = N - 2; j >= 0 && !found; j--) {
            if (a[j] < a[j + 1]) {      // a[j] < a[j + 1]
            // staring from the back to find the largest k
                for (k = N - 1; k >= 0 && !found; k--) {
                    if (a[j] < a[k]) {  // a[j] < a[k]
                        found = 1;      // set flag to found
                        temp = a[j];    // swap a[j] with a[k]
                        a[j] = a[k];
                        a[k] = temp;
                        // reversing the series
                        for (i = j + 1; i <= (N + j) / 2; i++) {
                            temp = a[i];
                            a[i] = a[N - i + j];
                            a[N - i + j] = temp;
                        }
                    }
                }   // print out the permutation
                printf("permutation #%d: ", ++counter);    
                for (i = 0; i < N; i++) {
                    printf("%d ", a[i]);
                }
                printf("\n");
            }
        }
        if (!found)         // if no j found, it is the last permutation
            last = 1;       // set last flag
    }
    printf("  Total number of permutations is %d", counter);
    return 0;
}
