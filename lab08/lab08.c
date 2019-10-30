/* EE2310 Lab08. Poker Hands
   107061112, 王昊文
   Date: 2018 / 11 / 12
*/

#include <stdio.h>
#include <stdlib.h>
#define N 10000000		// tests 10000000 times
/* global variables */
int cards_Suit[5] = {0};	// stores the suits
int cards_Number[5] = {0};	// stores the numbers (rank)
int straight_Flush = 0;		// counter of straight flush
int four_Of_A_Kind = 0;		// counter of four of a kind
int full_House = 0;			// counter of full house
int flush = 0;				// counter of flush
int straight = 0;			// counter of straight
int three_Of_A_Kind = 0;	// counter of three of a kind
int two_Pairs = 0;			// counter od two pairs
int one_Pair = 0;			// counter of one pair
int high_Card = 0;			// counter of high card
/* prototypes */			
void get_Cards();			// simulates a round
// stores the cards in ascending order
void store_By_Ranking();	   
void check_Cards();			// check the cards 

/******************************************************************************
* main: calls the get_Cards, check_Cards function, and will print the result  *
******************************************************************************/
int main(void) 
{
	double gameplay;	// counts how many round
	for (gameplay = 1; gameplay <= N; gameplay++) {
		get_Cards();		
		check_Cards();
	}
	gameplay--;		// at the end of the for loop, gameplay = N + 1
	printf("Categories      Probability\n");	// print result
	printf("Straight flush    %g%%\n", 100 * straight_Flush / gameplay);
	printf("Four of a kind    %g%%\n", 100 * four_Of_A_Kind / gameplay);
	printf("Full House        %g%%\n", 100 * full_House / gameplay);
	printf("Flush             %g%%\n", 100 * flush / gameplay);
	printf("Straight          %g%%\n", 100 * straight / gameplay);
	printf("Three of a kind   %g%%\n", 100 * three_Of_A_Kind / gameplay);
	printf("Two pairs         %g%%\n", 100 * two_Pairs / gameplay);
	printf("One pair          %g%%\n", 100 * one_Pair / gameplay);
	printf("High card         %g%%\n", 100 * high_Card / gameplay);
	return 0;
}

/******************************************************************************
* get_Cards: stimulates a round. each round will get five cards. We use two   *
* arrays to store the number and suit. Also, we will check if there is two    *
* same cards																  *
******************************************************************************/
void get_Cards() 
{
	int i, round;			// i: loop index, round: round counter
	int random_Number;		// to store the given number
	int random_Suit;		// to store the given suit
	for (i = 0; i < 5; i++) {	// clears hand card every time
		cards_Number[i] = 0;
		cards_Suit[i] = 0;
	}
	for (round = 1; round <= 5; round++) {	// generates random poker hands
		random_Number = (rand() / 1000) % 13;
		random_Suit = (rand() / 1000) % 4;
		for (i = 0; i < round - 1; i++) {	// check if there is same cards
			while (random_Number == cards_Number[i] && random_Suit == cards_Suit[i]) {		
				random_Number = (rand() / 1000) % 13;
				random_Suit = (rand() / 1000) % 4;
			}
		}
		cards_Number[round - 1] = random_Number;	// asign to cards
		cards_Suit[round - 1] = random_Suit;
	}
}

/******************************************************************************
* store_By_Ranking: to store the cards in an ascending way. It makes it easier*
* for checking																  *
******************************************************************************/
void store_By_Ranking()
{
	int i, j;	// lopp index
	int temp_Num;	// a temp for swapping
	for (i = 0; i < 5; i++) {
		for (j = i + 1; j < 5; j++) {	
		// once a bigger card found, then swap
			if (cards_Number[i] > cards_Number[j]) {
				temp_Num = cards_Number[i];
				cards_Number[i] = cards_Number[j];
				cards_Number[j] = temp_Num;
			}
		}
	}
}

/******************************************************************************
* check_Cards: In this program, we will check the type of the cards.          *
******************************************************************************/
void check_Cards()
{
	int i;	// loop index
	int flush_Check = 0;	// to check straight flush
	int flush_Continue = 0;	// a counter to check flush
	int straight_Check = 0;	// to check straight flush
	int straight_Continue = 0;	// a counter to check flush
	store_By_Ranking();	// store by ranking can make it easier to check
	/* check for flush */
	for (i = 0; i < 4 && cards_Suit[i] == cards_Suit[i + 1]; i++) {
			flush_Continue++;
	}
	if (flush_Continue == 4)
		flush_Check = 1;
	/* check for straight */
	for (i = 0; i < 4 && cards_Number[i + 1] - cards_Number[i] == 1; i++) {
			straight_Continue++;
	}
	/* because ACE is considered as 1 in the array, there might be a 
		special condition, that is: 10, J, Q, K, A. So 1, 10, 11, 12
		, 13 is also a straight. */
	if (cards_Number[0] == 1 && cards_Number[1] == 10 && cards_Number[2] == 11
	&& cards_Number[3] == 12 && cards_Number[4] == 13)	
		straight_Continue = 4;
	if (straight_Continue == 4)
		straight_Check = 1;
	/* check for straight flush */
	if (straight_Check && flush_Check) {
		straight_Flush++;
		return;
	}
	/* check for four of kind */
	if (cards_Number[0] == cards_Number[3] || cards_Number[1] == cards_Number[4]) 
	{
		four_Of_A_Kind++;
		return;
	}
	/* check for full house */
	if ((cards_Number[0] == cards_Number[2] && cards_Number[3] == cards_Number[4])|| 
	(cards_Number[0] == cards_Number[1] &&cards_Number[2] == cards_Number[4])) 
	{
		full_House++;
		return;
	}
	/* flush */
	if (flush_Check) {
		flush++;
		return;
	}
	/* straight */
	if (straight_Check) {
		straight++;
		return;
	}
	/* check for three of a kind */
	if (cards_Number[0] == cards_Number[2] || cards_Number[1] == cards_Number[3]
	|| cards_Number[2] == cards_Number[5])
	{
		three_Of_A_Kind++;
		return;
	}
	/* check for two pairs */
	if ((cards_Number[0] == cards_Number[1] && cards_Number[2] == cards_Number[3])
	|| (cards_Number[1] == cards_Number[2] && cards_Number[3] == cards_Number[4])
	|| (cards_Number[0] == cards_Number[1] && cards_Number[3] == cards_Number[4]))
	{
		two_Pairs++;
		return;
	}
	/* check for one pair */
	if (cards_Number[0] == cards_Number[1] || cards_Number[1] == cards_Number[2] ||
	cards_Number[2] == cards_Number[3] || cards_Number[3] == cards_Number[4])
	{
		one_Pair++;
		return;
	}
	high_Card++;	// if non of the above, then it is a high card
	return;
}
