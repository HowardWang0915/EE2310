/* EE2310 Lab10. Academic Competition
   107061112, 王昊文
   2018. 11. 26
*/

#include <stdio.h>

/* external structure */
struct STU {
	char fName[15];	// first name
	char lName[15];	// last name
	double math, sc9, lit;	// subjects
	double total;	// if subject > 80, calculate total 
	int winTotal;	// if won grand prize, wintotal = 1
	int winSubj;	// if won math = 1, sc9 = 2, lit = 3
};
struct STU list[100];
/* prototypes */
void read_input(void);	// reads the .dat and analize grand prize candidates
void grand_prize();		// analyze and print grand prize winners
void subject_prize();	// analyze and print subject winners

/******************************************************************************
* main:	calls all the functions.										      *
******************************************************************************/
int main(void)
{
	read_input();
	grand_prize();
	subject_prize();
	return 0;
}

/******************************************************************************
* read_input: scans text from "lab10.dat", then initialize all the variables  *
*  			  in the structure. also, for every subject > 80, calculate the   *
*			  total of the student											  *
******************************************************************************/
void read_input(void)
{
	char not_used[4];	// consume the first line
	int i;	// loop index
	for (i = 0; i <= 5 ; i++) {
		scanf("%s", &not_used[i]);	// consume
	}
	for (i = 0; i < 100; i++) {		// read input
		scanf("%s", list[i].fName);	
		scanf("%s", list[i].lName);
		scanf("%lf", &list[i].math);
		scanf("%lf", &list[i].sc9);
		scanf("%lf", &list[i].lit);
		// initialize
		list[i].total = 0;
		list[i].winTotal = 0;
		list[i].winSubj = 0;
		// candidates of grand prize, calculate the total of them
		if (list[i].math >= 80 && list[i].sc9 >= 80 && list[i].lit >= 80) 
			list[i].total = list[i].math + list[i].sc9 + list[i].lit;
	}
	return;
}

/******************************************************************************
* grand_prize: in this function, we will find grand_prize winners. Compare    *
* 			   total score and determine who won the prize                    *
******************************************************************************/
void grand_prize(void)
{
	int i, j = 0;	// loop index
	double max;		// highest total
	int max_pos;	// higest total position
	struct STU grand_list[5];	// to store the winners
	// find five winners
	for (i = 0; i < 5; i++) {
		for (j = 0, max = list[0].total; j < 100; j++) {
			// find the largest one and store it in the grand_list
			if (list[j].total > max && list[j].winTotal != 1) {
				max = list[j].total;	
				max_pos = j;	// remember the position of max
			}
		}
		// if it is a winner, it cannot be stored in grand_list again
		list[max_pos].winTotal = 1;	
		grand_list[i] = list[max_pos];	// store in grand_list
	}
	printf("Grand Prize\n");	
	for (i = 0; i < 5; i++) {	// print grand_list
		printf("  %d: %s %s %g\n", i + 1, grand_list[i].fName, \
		grand_list[i].lName, grand_list[i].total);
	}
	return;
}

/******************************************************************************
* subject_prize: this function we will find who won the grand_prize. The      *
*				 method is similar to grand_prize. Students with all subject  *
*				 > 60 and haven't won the grand prize is a candidate          *
******************************************************************************/
void subject_prize(void)
{ 
	int i, j;	// loop index 
	int max_pos;	// max position 	
	double max = 0;	// max temp
	struct STU math[10];	// math winner
	struct STU sc9[10];		// science winner
	struct STU lit[10];		// literature winner
	// finding math winners
	for (i = 0; i < 10; i++) {	// math has five winners
		for (j = 0, max = list[0].total; j < 100; j++) {	// 100 students
			if (list[j].math > max && !(list[j].winTotal) && list[j].winSubj != 1 && 
			list[j].lit > 60 && list[j].sc9 > 60) {
				max = list[j].math;
				max_pos = j;
			}
		}
		list[max_pos].winSubj = 1;
		math[i] = list[max_pos];
	}
	// finding science winners
	for (i = 0; i < 10; i++) {	// science has five winners
		for (j = 0, max = list[0].total; j < 100; j++) {	// 100 students
			if (list[j].sc9 > max && !(list[j].winTotal) && list[j].winSubj != 2 
			&& list[j].math > 60 && list[j].lit > 60) {
				max = list[j].sc9;
				max_pos = j;
			}
		}
		list[max_pos].winSubj = 2;
		sc9[i] = list[max_pos];
	}
	// finding literature winners
	for (i = 0; i < 10; i++) {	// lit has five winners
		for (j = 0, max = list[0].total; j < 100; j++) {	// 100 students
			if (list[j].lit > max && !(list[j].winTotal) && list[j].winSubj != 3 
			&& list[j].math > 60 && list[j].sc9 > 60) {
				max = list[j].lit;
				max_pos = j;
			}
		}
		list[max_pos].winSubj = 3;
		lit[i] = list[max_pos];
	}		
	printf("Math Prize\n");
	for (i = 0; i < 10; i++) {	// print math winners
		printf("  %d: %s %s %g\n", i + 1, math[i].fName, math[i].lName, math[i].math);
	}
	printf("Science Prize\n");
	for (i = 0; i < 10; i++) {	// print sc9_winners
		printf("  %d: %s %s %g\n", i + 1, sc9[i].fName, sc9[i].lName, sc9[i].sc9);
	}
	printf("Literature Prize\n");
	for (i = 0; i < 10; i++) {	// print lit winners
		printf("  %d: %s %s %g\n", i + 1, lit[i].fName, lit[i].lName, lit[i].lit);
	}
	return;
}
