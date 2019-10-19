#include <stdio.h>
#define NUM 3

int is_prime(int num);

int main(void) {
    int num;
    int i = 1;  // recording the number of prime number pairs
    for (num = 3; num <= 600000; num += 2) {
        if (is_prime(num)) {
            if (is_prime(num + 2))
                printf("Consecutive primes #%d: %d, %d\n", i++, num, num + 2);
        }
    }
} 
// the function to check for prime numbers
int is_prime(int num) {
    int j;      // loop index
    for (j = 2; j * j <= num; j++) {
        if (num % j == 0)
            return 0;   
    }
    return 1;
}
