
#include "stdafx.h"


void shuffle(int wDeck[][13]);
void dealHand(const int wDeck[][13], const char *wFace[], const char *wSuit[], Player &p, int dealAmount, int decision);


int cardCount = 1;


int _tmain(int argc, _TCHAR* argv[])
{
	const char *suit[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	const char *face[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", 
		"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	int deck[4][13] = {0};
	Player p1("Dealer");
	Player p2("Jesse");
	p1.setScore(0);
	p2.setScore(0);

	srand(time(NULL));

	shuffle(deck);
	cout << "Player 1: " << p1.getName() << endl << "------------------------" << endl;
	dealHand(deck, face, suit, p1, 5, 0);
	p1.setScore(p1.checkHand(face, suit, 1));
	if(p1.getScore() > 0 && p1.getScore() < 4)
	{
		dealHand(deck, face, suit, p1, p1.getScore(), 1);
		p1.getHand(face, suit);
		p1.setScore(p1.checkHand(face, suit, 2));
	}
	cout << setw(30) << "" << p1.getName() << "'s score is " << p1.getScore() << endl;
	cout << endl;

	cout << "Player 2: " << p2.getName() << endl << "------------------------" << endl;
	dealHand(deck, face, suit, p2, 5, 0);
	p2.setScore(p2.checkHand(face, suit, 2));
	cout << setw(30) << "" << p2.getName() << "'s score is " << p2.getScore() << endl;
	cout << endl;

	if(p1.getScore() > p2.getScore()){cout << p1.getName() << " wins!" << endl;}
	else if(p1.getScore() < p2.getScore()){cout << p2.getName() << " wins!" << endl;}
	else{cout << "Tie!" << endl;}

	return 0;
}

void shuffle(int wDeck[][13])
{
	int row, column;

	for(int card = 1; card <= 52; card++)
	{
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		}while(wDeck[row][column] != 0);

		wDeck[row][column] = card;
	}
}

void dealHand(const int wDeck[][13], const char *wFace[], const char *wSuit[], Player &p, int dealAmount, int decision)
{
	int i = 0;
	int wHand[4][13] = {0};
	for(int card = cardCount; card < cardCount+dealAmount; card++)
	{
		for(int suit = 0; suit <= 3; suit++)
		{
			for(int face = 0; face <= 12; face++)
			{
				if(wDeck[suit][face] == card)
				{
					if(decision){cout << "You picked up a " <<  wFace[face] <<  " of " << wSuit[suit] << endl;}
					else
					{
						cout << setw(6) << setiosflags(ios::left) << wFace[face] << setw(3) << " of " <<
							setw(6) << wSuit[suit] << endl;
					}
					wHand[suit][face] = 1;
				}
			}
		}
	}
	cout << endl;
	cardCount+=5;
	if(decision){p.addHand(wHand);}
	else{p.setHand(wHand);}
}
