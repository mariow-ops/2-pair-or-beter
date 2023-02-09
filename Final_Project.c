/* Authors: Mario Weiler and Sean Riffe
	
	Final Version of Final Project
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SPADE "\u2660"
#define CLUB "\u2663"
#define DIAMOND "\u2666"
#define HEART "\u2665"

#define USEWORD 0

typedef struct card_s { //have a typedef struct with a suit, a face value, and a node that is next
	char suit;
	int face;
	struct card_s* next;
}card;



void create_deck(card** headp, card** tail) {//input head and tail of the deck
	int i, j;
	card* temp;

	for (i = 3; i <= 6; i++) { //goes through each suit
		for (j = 1; j <= 13; j++) { //goes through each face card
			temp = (card*)malloc(sizeof(card));
			temp->suit = i;
			temp->face = j;
			//linking the nodes
			if (*headp == NULL) {
				*headp = temp; //set temp equal to headp
			}
			else {
				(*tail)->next = temp; //sets the next tail equal to temp
			}
			*tail = temp;
			(*tail)->next = NULL;

		}
	}


}


void delete_head_card(card** h) {// input deck
	card* targetp = *h; // pointer to node to be deleted
	card* prev = *h; // pointer to the head of the list

	if (targetp == NULL) return;
	else {
		if (targetp == *h) // if first node is to be deleted
			*h = targetp->next; // update headp
		else {
			while (prev->next != targetp)
				prev = prev->next; // find the node before the target node

			prev->next = targetp->next; // skip node to be deleted
		}
		free(targetp); // free the memory
	}
}

void delete_card(card** h, card* current_card) { //input player hand or deck and card that needs to be deleted
	card* prev = *h; // pointer to the head of the list

	if (current_card == NULL) return;
	

	if (current_card == *h) { // if first node is to be deleted
		*h = current_card->next; // update headp
		
	}
		
	else {
		while ((prev->next != current_card) && (prev->next != NULL)) {
			prev = prev->next; // find the node before the target node
		}

		if (prev->next == NULL) {
			printf("couldn't find the card"); //if function coudln't find card
		}

		prev->next = current_card->next; // skip node to be deleted
		current_card->next = NULL; 
	}
	free(current_card); //free the memory

}

void player_hand(card** headp, card** handp) {// input player hand and deck
	int i;
	card* temp;
	card temp1;
	card* temp2;

	for (i = 0; i < 5; ++i) { //go through each card in the in hand
		temp = (card*)malloc(sizeof(card));
		temp1 = **headp;

		delete_head_card(headp); //call delete head card function

		*temp = temp1;
		temp->next = NULL;

		if (*handp == NULL) { //if first card is head of deck set equal to temp
			*handp = temp;
		}
		else {
			temp2 = *handp;
			while (temp2->next != NULL) { //goes through the player hand and creates it using temp2
				temp2 = temp2->next;

			}
			temp2->next = temp;
		}

	}


}

void add_card(card** deck, card* current_card, int index_card) {//inputs the player hand, the current card, the position at which we want the card in the hand
	card* temp = *deck;
	int count = 1;

	if (index_card == 0) { //if card is first card in the hand
		current_card->next = *deck;
		*deck = current_card;
	}
	else {
		while (temp != NULL) {//traverses the players hand
			if (count == index_card) { //if count equals index card it adds the card in the players hand
				current_card->next = temp->next;
				temp->next = current_card;
				return;
			}

			temp = temp->next;
			count++;
		}
	}
}



card* get_card(card** deck, int curr_card) { //input is the players hand/deck and the card the user wants to get
	card* temp = *deck;
	int count = 0;

	while (temp != NULL) { //traverses the linked list
		if (count == curr_card) { //if count equals current card it returns the card
			return temp;
		}

		temp = temp->next;
		count++;
	}
}

		


void printDeck(card* deck) { //inputs are the players hand or deck
	int count = 0;


	while (deck != NULL) { // traversing the list
		if (deck->face == 1) { //if card is Ace
			printf("%c%c\t", 'A', deck->suit);
			deck = deck->next;
		}

		else if (deck->face == 11) { //If card is Jack
			printf("%c%c\t", 'J', deck->suit);
			deck = deck->next;
		}

		else if (deck->face == 12) { //If card is Queen
			printf("%c%c\t", 'Q', deck->suit);
			deck = deck->next;
		}

		else if (deck->face == 13) {// If card is King
			printf("%c%c\t", 'K', deck->suit);
			deck = deck->next;
		}

		else {
			printf("%d%c\t", deck->face, deck->suit);
			deck = deck->next;
		}

		count++;
		if ((count == 13) || (count == 26) || (count == 39) || (count == 52)) {
			printf("\n");
		}
	}
}


void Shuffle_Deck(card* h) { //input is the deck
	card* pt1;
	card* pt2;
	char temp1;
	int temp2;

	int i, j, k, t;

	for (i = 0; i < 10000; ++i) { //shuffles the deck 10000 times
		pt1 = h;

		for (j = 0; j < 52; j++) //goes through each card in the deck
		{
			pt2 = h;
			k = rand() % 52; //returns a random number between 1 - 52

			for (t = 0; t < k; ++t) { //goes the deck until it reaches k
				pt2 = pt2->next;
			}

			temp1 = pt1->suit; //switch the cards
			pt1->suit = pt2->suit;
			pt2->suit = temp1;

			temp2 = pt1->face; //switch the cards
			pt1->face = pt2->face;
			pt2->face = temp2;



			pt1 = pt1->next; //goes to the next card in the list
		}

	}
}


void swap(int* x, int* y) { //inputs are face values and suit numbers
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void wager(int bet, int* coins, card* handp) { //inputs are the players bet, coins player has, and the players hand
	int cards[5];
	int suits[5];
	int temps;
	card* temp = handp;
	int i, j;
	int rank = 0;
	int totalwon = 0;

	

	for (i = 0; i < 5; i++) {         //store link list into an array
		cards[i] = temp->face;
		suits[i] = temp->suit;

		temp = temp->next;
	}

	for (i = 0; i < 5; i++) {       //put array in order
		temps = i;
		for (j = i; j < 5; j++) {
			if (cards[j] < cards[temps])
				temps = j;
		}
		swap(&cards[i], &cards[temps]);
		swap(&suits[i], &suits[temps]);
	}
	for (i = 3; i <= 6; i++) {      //checking for flush
		if (suits[0] == i && suits[1] == i && suits[2] == i && suits[3] == i && suits[4] == i) {
			if (cards[0] == 1 && cards[1] == 10 && cards[2] == 11 && cards[3] == 12 && cards[4] == 13) {
				rank = 1;
				break;
			}   //ends royal flush statment
			else if (cards[0] + 1 == cards[1] && cards[1] + 1 == cards[2] && cards[2] + 1 == cards[3] && cards[3] + 1 == cards[4]) {
				rank = 2;
				break;
			}   //ends straight flush statment
			else {
				rank = 5;
				break;
			}   //ends flush statment

		}// ends flush if statment
	} // ends flush loop
	if ((cards[0] == cards[1] && cards[0] == cards[2] && cards[0] == cards[3]) || (cards[1] == cards[2] && cards[2] == cards[3] && cards[1] == cards[4])) {
		rank = 3;
	}   //ends four of a kind if statment
	else if ((cards[0] == cards[1] && cards[0] == cards[2] && cards[3] == cards[4]) || (cards[0] == cards[1] && cards[2] == cards[3] && cards[2] == cards[4])) {
		rank = 4;
	}   //ends full house if statment
	else if ((cards[0] + 1 == cards[1] && cards[1] + 1 == cards[2] && cards[2] + 1 == cards[3] && cards[3] + 1 == cards[4] && rank == 0) || (cards[0] + 9 == cards[1] && cards[1] + 1 == cards[2] && cards[2] + 1 == cards[3] && cards[3] + 1 == cards[4] && rank == 0)) {
		rank = 6;
	}   //ends straight if statment
	else if ((cards[0] == cards[1] && cards[0] == cards[2] && rank == 0) || (rank == 0 && cards[2] == cards[3] && cards[2] == cards[4]) || (rank == 0 && cards[1] == cards[2] && cards[1] == cards[3])) {
		rank = 7;
	}   //ends three of a kind if statment
	else if ((cards[0] == cards[1] && cards[2] == cards[3]) || (cards[1] == cards[2] && cards[3] == cards[4]) || (cards[0] == cards[1] && cards[3] == cards[4])) {
		rank = 8;
	}   //ends two pairs if statment

	switch (rank) { //deciding the winning or losing amount based on the rank number
	case 0:
		*coins = *coins - bet;
		break;
	case 1:
		*coins = *coins + (bet * 250);
		totalwon = bet * 250;
		break;
	case 2:
		*coins = *coins + (bet * 100);
		totalwon = bet * 100;
		break;
	case 3:
		*coins = *coins + (bet * 50);
		totalwon = bet * 50;
		break;
	case 4:
		*coins = *coins + (bet * 25);
		totalwon = bet * 25;
		break;
	case 5:
		*coins = *coins + (bet * 10);
		totalwon = bet * 10;
		break;
	case 6:
		*coins = *coins + (bet * 5);
		totalwon = bet * 5;
		break;
	case 7:
		*coins = *coins + (bet * 4);
		totalwon = bet * 4;
		break;
	case 8:
		*coins = *coins + (bet * 2);
		totalwon = bet * 2;
		break;
	}   //end of switch
	if (rank > 0 && rank < 9) {
		printf("You WON %d coins and you now have %d coins\n", totalwon, *coins);
	}
	else if (rank == 0 || *coins <= 0) {
		printf("You LOST and you now have %d coins\n", *coins);
	}
} // end of wager function



int main(void) {
	int num, bet = 0, bet1 = 0, coins = 100, card_get[5] = { 0,0,0,0,0 }, cardcount1 = 0;
	int i, count = 0, count1 = 0;
	card* headp = NULL, * tail = NULL, * handp = NULL, *temp;
	char player[20];
	char letter = 'a';

	create_deck(&headp, &tail); //creates deck


	srand(time(NULL)); //initailze random number generator
	Shuffle_Deck(headp); //Shuffles the deck


	printf("Enter your name: ");
	fgets(player, 20, stdin);//scanning the name of the player
	if (player[strlen(player) - 1] == '\n') {
		player[strlen(player) - 1] = 0; //gets rid of the newline in fgets
	}

	printf("$$$$$$$$ $$$$$$$$$$$ $$$$$$$$$$$ $$$$$$$$$$$$$ $$$$$$$$$$\n");
	printf("\t$$$$$$$$$ $$$$$$$$$$$$ $$$$$$$$$$$$$\n");

	printf("%s,\n\tLet's Play Two Pairs or Better\n", player);

	printf("\t$$$$$$$$$ $$$$$$$$$$$$ $$$$$$$$$$$$$\n");
	printf("$$$$$$$$ $$$$$$$$$$$ $$$$$$$$$$$ $$$$$$$$$$$$$ $$$$$$$$$$\n");
	printf("$$$$$$$$\t Rank of Winning\t $$$$$$$$$$\n");
	//stars are used to represent the winning suit or face card 
	printf("\t\t\t\t\tPay\n");
	printf("Royal Flush\t 10%c J%c Q%c K%c A%c\t 250*bet\n", 6, 6, 6, 6, 6);
	printf("Straight Flush\t 2%c 3%c 4%c 5%c 6%c\t\t 100*bet\n", 5, 5, 5, 5, 5);
	printf("Four of a Kind\t 9%c 9%c 9%c 9%c *\t\t 50*bet\n", 3, 4, 5, 6);
	printf("Full House\t 9%c 9%c 9%c 3%c 3%c\t\t 25*bet\n", 3, 4, 5, 6, 4);
	printf("Flush\t\t *%c *%c *%c *%c *%c\t\t 10*bet\n", 4, 4, 4, 4, 4);
	printf("Straight\t 2* 3* 4* 5* 6*\t\t 5*bet\n");
	printf("Three of a kind\t 9%c 9%c 9%c * *\t\t 4*bet\n", 3, 4, 5);
	printf("Two Pair\t K%c K%c 6%c 6%c *\t\t 2*bet\n\n", 3, 4, 5, 6);

	while (letter != '\0') { //loop goes when letter is not a NULL character

		printf("******* *********** ************** ************\n");
		printf("******* %s, you have %d coins**************\n", player, coins);
		printf("*********** ********** *********** ***********\n");

		printf("\nPlace your bet (1-%d) coins (-1 to quit playing): ", coins);
		scanf("%d", &bet); //player places bet

		if (bet == -1) { //ends loop and ends the game
			break;
		}

		while ((bet > coins) || (bet < 1)) { //if player bet is outside the acceptable range
		
			printf("Place your bet (1-%d) coins (-1 to quit playing): ", coins);
			scanf("%d", &bet); //player places bet

			if (bet == -1) { //ends loop
				break;
			}
			
		}

		if (bet == -1) {  //ends loop and ends the game
			break;
		}


		printf("\nYou bet %d coins\n\n", bet); //show player's bet

		printf("%s's hand:\n", player);
		
		player_hand(&headp, &handp); //creates player hand

		printDeck(handp); //prints players hand
		printf("\n\n");

		
		cardcount1 = 0;
		count1 = 0;
		
		for (i = 0; i < 5; ++i) { //setting card get array to 0
			card_get[i] = 0;
		}

		while (cardcount1 != -1) { //loop goes until cardcount1 does equal -1
			printf("Pick cards (between 1-5) to hold (-1 to stop):");
			scanf("%d", &cardcount1); //ask player what cards to hold


			if ((cardcount1 > 0) && (cardcount1 <= 5)) { //if player enter a number between 1-5
				card_get[cardcount1 - 1] = 1; //set card to 1
				count1++;
			}

			if (count1 == 5) { //when player holds all five cards break the loop
				break;
			}
			
			//the loop continues until they enter number between 1-5 and continue to go until they hold all five cards or press -1
		}

				
			
		

		for (i = 0; i < 5; ++i) { // go through each card in player's hand

			if (card_get[i] == 0) { //if card get is 0 then the player wants a new card for that card
				temp = get_card(&handp, i); //get card in player hand
				delete_card(&handp, temp); //delete that card
				temp = get_card(&headp, 0); //get card from top of deck
				headp = headp->next; 
				add_card(&handp, temp, i); //add card in player hand where we took the oringinal card
			}

		}

		printf("\n%s's hand:\n", player);
		printDeck(handp); //print player's hand
		printf("\n");

		wager(bet, &coins, handp); //analyze player hand to decide if the hand is a winning hand or not then give or take coins acorrdingly


		for (i = 0; i < 5; ++i) { //discard all cards in player's hand
			temp = get_card(&handp, 0);
			delete_card(&handp, temp);
		}

		count = 0;
		temp = headp;
		while (temp != NULL) { //counts all the cards in the deck currently
			temp = temp->next;
			count++;
		}

		if (count < 20) { //if deck is below 20 cards

			for (i = 0; i < count; ++i) { //delete every card in the deck
				temp = get_card(&headp, 0);
				delete_card(&headp, temp);
			}
			
			create_deck(&headp, &tail); //create a new 52 card deck


			srand(time(NULL)); //call srand
			Shuffle_Deck(headp); //shuffle the deck
		}


		if (coins == 0) { //if player has no coins left they lose and the game ends
			
			printf("\nYou lost all your coins. Game Over!\n");
			break;
		}

		printf("\nHit Enter key to continue: "); //players hits the enter key to continue playing
		scanf("%*c%c", &letter);
		printf("\n");
	}

	printf("Goodbye %s", player); 

	return 0;
}
