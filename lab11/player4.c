/* EE2310 Lab11. Blackjack Strategy
   107061112, 王昊文
   2018.12.03
*/

/* blackjack player functions
* 4 functions are needed
* bet_init: before cards are dealt, initial bet is made
* hit_or_stand: after cards are dealt, player needs to make a decision
* whether to hit or stand
* shuttle: when the decks of cards are all used, dealer reshuffle
* the decks, and each player is notified
* deal_one_card: when each card is dealt by the dealer, each player is
* notified what card is dealt
*
*/
#include <stdio.h>
#include "card.h"

char play4_name[7] = "me";
static int true_count = 1;	// this variable can determine the betting money
static int count = 0; 		// count the cards
static double cards_remaining = 208;	// cards remaining
static int cards_count[13] = 
{16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};	// for counting

int play4_bet_init(const int credit);	
int play4_hit_or_stand(const struct CARD mycard[], int Nmycard,
					   const struct CARD dealercard[], int Ndealcard);
void play4_shuffle();
void play4_deal_one_card(const struct CARD cd);
// this function places a bet before cards are dealt
// input: the amount of credit left for the user
// output: how much the player want to bet for this round
// algorithm: High and low + true count
int play4_bet_init(const int credit)
{
	if (true_count < 1)	// true count < 1 means low cards are more
		return 3;
	else 
		return 3 * true_count;	// true count * unti = money you bet
}

// this function decides if to hit for more cards or not
// input: player's cards (and number of cards)
// dealer's cards (and number of cards)
// Note, at this time dealer has only one card
// output: 1 to hit; 0 to stand, 2: double (receive only 1 card), 3: surrender
// algorithm: Basic stragegy of blackjack from internet + bustinig percentage
int play4_hit_or_stand(const struct CARD mycard[], int Nmycard,
					   const struct CARD dealercard[], int Ndealercard)
{
	double no_bust;	// possibility to not bust
	int Nsafecard;	// safe card number
	int sum_me;		// sum of my cards
	int sum_deal;	// sum of dealers cards
	int i;			// loop index
	sum_me  = sum_cards(mycard, Nmycard);
	sum_deal = sum_cards(dealercard, Ndealercard);
	if (!with_ace(mycard, Nmycard)) {
		if (sum_me <= 9) 
			return 1;
		else if (sum_me <= 10 && !with_ace(dealercard, Ndealercard) && sum_deal != 10) {
			if (!with_ace(dealercard, Ndealercard && sum_deal) != 10)
				return 2;
			else
				return 1;
		}
		for (i = 0, Nsafecard = 0; i < 21 - sum_me; i++) {
			Nsafecard += cards_count[i];
		}
		no_bust = Nsafecard / cards_remaining;  
		if (sum_me <= 11 && no_bust >= 0.55)
			return 2;
		else if (sum_me <= 12) {
			if ((sum_deal < 3|| sum_deal > 7) && no_bust >= 0.55)
				return 1;
			else 
				return 0;
		}
		else if (sum_me <= 21) {
			if (no_bust >= 0.55)
				return 1;
			else 
				return 0;
		}
	}
	else {
		if (sum_me  <= 13) {
			if (sum_deal < 5 || sum_deal > 6)
				return 1;
			else 
				return 2;
		}
		else if (sum_me <= 15) {
			if (sum_deal < 4 || sum_deal > 6)
				return 1;
			else
				return 2;
		}
		else if (sum_me <= 17) {
			if (sum_deal < 3 || sum_deal > 6)
				return 1;
			else 
				return 2;
		}
		else if (sum_me <= 21) {
			for (i = 0, Nsafecard = 0; i < 21 - sum_me; i++) {
				Nsafecard += cards_count[i];
			}
			no_bust = Nsafecard / cards_remaining;  
			if (no_bust > 0.55)	
				return 1;
			else 
				return 0;
		}
		else 
			return 0;
	}
}
// this function is called when the cards are reshuffled
// input: none
// output: none
// algorithm: when shuffling, make all the counting to zero again
void play4_shuffle()
{
	int i;	// loop index
	for (i = 0; i < 13; i++) {
		cards_count[i] = 16;	// all cards of 16 of them
	}
	count = 0;					// card counting = 0
	cards_remaining = 208;		// there are 208 cards
	return;
}
// this function is called when a card is dealt by the dealer
// input: the card being dealt
// output: none
// algorithm: High and low counting system
void play4_deal_one_card(const struct CARD cd)
{
	cards_count[cd.value]--; // every time card is dealt, card of that value -1
	if (cd.value <= 5 && cd.value != 0)	// 
		count++;	// low card count +1
	if (cd.value >= 9 || cd.value == 1)
		count--;	// high card count -1
	cards_remaining--;	// card remaining -1
	// true count will determine how much to bet = running count / deck remaining
	true_count = count / (cards_remaining / 52) - 1;	
	return;
}
