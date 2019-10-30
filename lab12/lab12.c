/* EE2310 Lab12. Polynomials
   107061112, ¤ý©þ¤å
   Date: 2018.12.10
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct sPoly {
	int degree;			// degree of the node
	double coef;		// the coefficient of the node
	struct sPoly *next;	// pointer to the next node
} POLY;

POLY *oneTerm(int degree, double coef);
	/* This function creates a 1-term polynomial of the
	   form coefB^xdegree and returns the new polynomial. */
POLY *add(POLY *p1, POLY *p2);
	/* This function adds two polynomials p1 and p2 to
	   form a new polynomial and return the new polynomial. */
POLY *sub(POLY *p1, POLY *p2);
	/* This function subtract polynomial p2 from p1 to form
       a new polynomial and return the new polynomial */
POLY *mply(POLY *p1, POLY *p2);
	/* This function multiplies two polynomials p1 and p2
	   to form a new polynomial and return the new polynomial. */
void print(POLY *p1);
    /* This function prints out the polynomial p1 in human
       readable form. See the example output given below for
       more details. */
void release(POLY *p1);
	/*This function releases all nodes of the polynomial
	  p1 and returns them to the heap space. */
int main(void)	// calls all the functions
{
	POLY *p1, *p2;
	POLY *A, *A2, *A3, *A4, *A5;
    POLY *B, *B2, *B3, *B4, *B5;
    POLY *C, *C2, *C3, *C4, *C5;

	p1 = oneTerm(1, 1);
	p2 = oneTerm(0, 1);

	A = add(p1, p2);
    A2 = mply(A, A);
    A3 = mply(A2, A);
    A4 = mply(A3, A);
    A5 = mply(A4, A);

    printf("A = ");
	print(A);
	printf("A2 = ");
	print(A2);
	printf("A3 = ");
	print(A3);
	printf("A4 = ");
	print(A4);

    B = sub(p1, p2);
    B2 = mply(B, B);
    B3 = mply(B2, B);
    B4 = mply(B3, B);
    B5 = mply(B4, B);

    C = add(A, B);
    C2 = mply(A2, B2);
    C3 = mply(A3, B3);
    C4 = mply(A4, B4);
    C5 = mply(A5, B5);

    printf("C = ");
    print(C);
    printf("C2 = ");
    print(C2);
    printf("C3 = ");
    print(C3);
    printf("C4 = ");
    print(C4);
    printf("C5 = ");
    print(C5);
	// free all the linked list
	release(A);
	release(A2);
	release(A3);
	release(A5);
	release(B);
	release(B2);
	release(B3);
	release(B4);
	release(B5);
	release(C);
	release(C2);
	release(C3);
	release(C4);
	release(C5);
	return 0;
}
POLY *oneTerm(int degree, double coef)
{
	POLY *new_node;	// points to the new term
	POLY *head;		// always points to the first node
	new_node = malloc(sizeof(POLY));
	head = new_node;	// assign first node to head
	new_node->degree = degree;	
	new_node->coef = coef;
	new_node->next = malloc(sizeof(POLY));	// give the term an additional link
	new_node = new_node->next;
	new_node->next = NULL;
	return head;
}
POLY *add(POLY *p1, POLY *p2)	// addition
{
    POLY *sum;	
    POLY *head;	// always points to the first node of sum
    sum = (POLY *)malloc(sizeof(POLY));
    head = sum;	// assign head
	/* algorithm: compare the degree of p1, p2, the bigger one is the 
	   next term of sum. If the degree is same, then the term of sum 
	   p1 + p2. Pointer will go right one distance until either p1
	   or p2 reches to the end. */
    while (p1->next && p2->next) {	// if either p1 or p2 reaches to the end
        if (p1->degree > p2->degree) {	// max degree = p1
            sum->degree = p1->degree;	// assign coef and degree as p1
            sum->coef = p1->coef;
            p1 = p1->next;	// p1 shifts
        }
        else if (p1->degree < p2->degree) {	// max degree = p2
            sum->degree = p2->degree;		// assign coef and degree as p2
            sum->coef = p2->coef;		
            p2 = p2->next;				// p2 shifts
        }
        else {		// degree: p1 = p2
            sum->coef = p1->coef + p2->coef;	// sum coef = p1 + p2
            sum->degree = p1->degree;
            p1 = p1->next;	// both p1 and p2 shifts
            p2 = p2->next;
        }
        sum->next = (POLY *)malloc(sizeof(POLY));
        sum = sum->next;	// sum shifts
    }
	/* if p1 shifts to the end, the remaining terms of p2 goes to sum 
	   and vice versa */
	// loop will stop when bith p1, p2 shifts to the end.
   while (p1->next || p2->next) {	
        if (p1->next) {
            sum->degree = p1->degree;
            sum->coef = p1->coef;
            p1 = p1->next;
        }
        if (p2->next) {
            sum->degree = p2->degree;
            sum->coef = p2->coef;
            p2 = p2->next;
        }
        sum->next = (POLY *)malloc(sizeof(POLY));
        sum = sum->next;
   }
   sum->next = NULL;
   return head;
}

POLY *sub(POLY *p1, POLY *p2)	// subtraction
{
	POLY *sub;
	POLY *head;	// pointer to the head of the subtraction answer
	sub = malloc(sizeof(POLY));
	head = sub;
	/* the method is similiar to add. The difference is that if degree of p2
	   is bigger than p1, then the term to the ans is -p2. */
	while (p1->next && p2->next) {
		if (p1->degree > p2->degree) {	// degree max = p1
			sub->degree = p1->degree;	// assign p1 to sub
			sub->coef = p1->coef;
			p1 = p1->next;	// p1 shifts
		}
		else if (p1->degree < p2->degree) {	// degree max = p2
			sub->degree = (p2->degree);
			sub->coef = -1 * (p2->coef);	// coef turns to -p2
			p2 = p2->next;
		}
		else {
			sub->coef = p1->coef - p2->coef;	// degree p1 = p2
			sub->degree = p1->degree;
			p1 = p1->next;
			p2 = p2->next;
		}
		sub->next = malloc(sizeof(POLY));	
		sub = sub->next;
	}
	/* either p1 or p2 shifts to the end, we have to determine the 
	   remaining terms. */
	while (p1->next) {	// if remaining term is p1
		sub->coef = p1->coef;
		sub->degree = p1->degree;
		sub->next = malloc(sizeof(POLY));
		sub = sub->next;
		p1 = p1->next;
	}
	while (p2->next) {	// else if the remaining term is p2
		sub->coef = -1 * (p2->coef);	// coef *-1
		sub->degree = p2->degree;
		sub->next = malloc(sizeof(POLY));
		sub = sub->next;
		p2 = p2->next;
	}
	sub->next = NULL;
	return head;
}

/******************************************************************************
* mply: using function oneTerm to generate a term every time, p1 and p2 	  *
*       degree add together, coef multiply together. Then, add each terms     *
*       using the function add.                                               *
******************************************************************************/
POLY *mply(POLY *p1, POLY *p2)	// multiply
{
    POLY *p1_head, *p2_head;	// pointer points to head of p1 p2
	// first_term: generates first term, mply: stores temp terms.
    POLY *first_term, *mply, *ans;	// ans will store the current answer
    int first = 1;	// a flag for first term
    p1_head = p1;	
    p2_head = p2;
	// generate first term
    first_term = oneTerm(p1->degree + p2->degree, p1->coef * p2->coef);
    p2 = p2->next;
	/* after p2 is shifted to the end, p2 will come back to the head
	   and p1 will shift one distance. This is to generate every term
	   while multiplication. The loop will stop when p1 shifts to end. */
    while (p1->next) {
        while (p2->next) {
            if (first) {	// check if it is the first term?
				// generate another term
                mply = oneTerm(p1->degree + p2->degree, p1->coef * p2->coef);
                ans = add(first_term, mply);	// add together
                release(mply);	
				release(first_term);
                first--;	// the first term is generated
            }
            else {
				// generate and add the rest of the terms
                mply = oneTerm(p1->degree + p2->degree, p1->coef * p2->coef);
                ans = add(ans, mply);	
                release(mply);
            }
            p2 = p2->next;
        }
        p1_head = p1_head->next;
        p1 = p1_head;
        p2 = p2_head;
    }
    return ans;
}

// this function will print out the results in a form easy for us to read
void print(POLY *p1)
{
	  while (p1->next != NULL) {	// not last term
        if (p1->coef != 1 && p1->coef != 0) {	
			if (p1->degree > 1)
           	 	printf("%g x^%d ", p1->coef, p1->degree);
			// if degree is one then the degree is not displayed
       		 else if (p1->degree == 1)	
            	printf("%g x ", p1->coef);
			// if degree is 0, then x is not displayed
        	else if (p1->degree == 0)
            	printf("%g ", p1->coef);
		}
		else if (p1->coef == 1) {	// coef not displayed
			if (p1->degree > 1)
           	 	printf("x^%d ",p1->degree);
       		 else if (p1->degree == 1)
            	printf("x ");
        	else if (p1->degree == 0)
            	printf("1 ");
		}
        p1 = p1->next;
        if (p1->next != NULL && p1->coef > 0)
            printf("+");	// determine when to print +
    }
    printf("\n");
    return;
}

// free all the linked lists
void release(POLY *p1)
{
	POLY *clear;	// a pointer to point to the node you want clear
	while (p1 != NULL) {	// not end
		clear = p1;	// the pointer points to current position
		p1 = p1->next;	// shift the leading pointer
		free(clear);	// clear
	}
}
