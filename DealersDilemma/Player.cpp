#include "stdafx.h"
#include "Player.h"
#include <iomanip>


Player::Player(string player) : playerName(player), hand()
{}

Player::~Player()
{}

void Player::setHand(const int wHand[][13])
{
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			Player::hand[i][j] = wHand[i][j];
		}
	}
}

void Player::addHand(const int wHand[][13])
{
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			if(hand[i][j]){}
			else{Player::hand[i][j] = wHand[i][j];}
		}
	}
}

void Player::getHand(const char *wFace[], const char *wSuit[])
{
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			if(1 == hand[i][j])
			{
				cout << setw(6) << setiosflags(ios::left) << wFace[j] << setw(3) << " of " <<
						setw(6) << wSuit[i] << endl;
			}
		}
	}
}

int Player::checkHand(const char *wFace[], const char *wSuit[], int turn)
{
	int straight = checkStraight(wFace, wSuit, turn);
	int flush = checkFlush(wFace, wSuit, turn);
	int kinds = checkKinds(wFace, wSuit, turn);
	int twoPair = checkTwoPair(wFace, wSuit);

	if(200 == straight){return straight;}
	else if(120 == flush){return flush;}
	else if(80 == kinds){return kinds;}
	else if(60 == kinds){return kinds;}

	if(1 == straight && 20 == kinds){if(!(3 % rand())){return straight;}else{return kinds;}}
	else if(1 == straight){return straight;}

	if(1 == flush && 20 == kinds){if(!(3 % rand())){return flush;}else{return kinds;}}
	else if(1 == flush && 40 == twoPair){if(!(3 % rand())){return flush;}else{return twoPair;}}
	else if(1 == flush && 1 == straight){if(!(2 % rand())){return flush;}else{return straight;}}
	else if(1 == flush){return flush;}
	
	if(40 == twoPair){return twoPair;}
	else if(20 == kinds){return kinds;}
	else if(3 == kinds){return kinds;}
	else if(2 == kinds){return kinds;}

	if(1 == turn)
	{
		int counter = 0;
		while(counter != 3)
		{
			int i = rand() % 4;
			int j = rand() % 13;

			if(1 == hand[i][j])
			{
				hand[i][j] = 0;
				cout << "Discard " << wFace[j] << " of " << wSuit[i] << endl;
				counter++;
			}
		}
		return 3;
	}
	
	return 0;
//	return 0;
}
int Player::checkTwoPair(const char *wFace[], const char *wSuit[])
{
	int face[5] = {};
	int counter = 0;
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			if(hand[i][j] == 1)
			{
				face[counter] = j;
				counter++;
			}
		}
	}

	int cardCount[13] = {};

	for(int i = 0; i < 5; i++)
	{
		cardCount[face[i]]++;
	}

	for(int i = 0; i < 5; i++)
	{
		if(2 == cardCount[face[i]])
		{
			cardCount[face[i]] = 0;
			for(int j = 0; j < 5; j++)
			{
				if(2 == cardCount[face[j]])
				{
					cout << endl << "Congratulations! Two Pair! " << wFace[face[i]] << "'s" << " and " << wFace[face[j]] << "'s" << endl; 
					return 40;
				}
			}
		}
	}

	return 0;
}
int Player::checkKinds(const char *wFace[], const char *wSuit[], int turn)
{
	int face[5] = {};
	int counter = 0;
	int discardCounter = 0;
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			if(hand[i][j] == 1)
			{
				face[counter] = j;
				counter++;
			}
		}
	}

	int cardCount[13] = {};

	for(int i = 0; i < 5; i++)
	{
		cardCount[face[i]]++;
	}

	for(int i = 0; i < 5; i++)
	{
		if(4 == cardCount[face[i]])
		{
			cout << endl << "Congratulations! Four " << wFace[face[i]] << "'s" << endl; 
			return 80;
		}
		if(3 == cardCount[face[i]])
		{
			cout << endl << "Congratulations! Trip " << wFace[face[i]] << "'s!" << endl; 
			if(1 == turn)
			{
				cout << endl << "Why not try for Four of a Kind? Shoot for another " << wFace[face[i]] << endl;
				cout << "And discard these cards: " << endl;
				for(int j = 0; j < 4; j++)
				{
					for(int k = 0; k < 13; k++)
					{
						if(k != face[i] && 1 == hand[j][k])
						{
							cout << wFace[k] << " of " << wSuit[j] << endl; 
							hand[j][k] = 0; 
						}
					}
				}
				return 2;
			}
			return 60;
		}
		if(2 == cardCount[face[i]])
		{
			cout << endl << "Congratulations! Pair of " << wFace[face[i]] << "'s!" << endl; 
			if(1 == turn)
			{
				cout << endl << "Why not try for Three or Four of a Kind? Shoot for more " << wFace[face[i]] << "'s" << endl;
				cout << "And discard these cards: " << endl;
				for(int j = 0; j < 4; j++)
				{
					for(int k = 0; k < 13; k++)
					{
						if(k != face[i] && 1 == hand[j][k])
						{
							cout << wFace[k] << " of " << wSuit[j] << endl; 
							hand[j][k] = 0; 
						}
					}
				}
				return 3;
			}
			return 20;
		}
	}

	return 0;
}
int Player::checkFlush(const char *wFace[], const char *wSuit[], int turn)
{
	int suit[5] = {};
	int counter = 0;
	for(int i = 0; i <= 3; i++)
	{
		for(int j = 0; j <= 12; j++)
		{
			if(hand[i][j] == 1)
			{
				suit[counter] = i;
				counter++;
			}
		}
	}

	int cardCount[13] = {};

	for(int i = 0; i < 5; i++)
	{
		cardCount[suit[i]]++;
	}

	for(int i = 0; i < 5; i++)
	{
		if(5 == cardCount[suit[i]])
		{
			cout << endl << "Congratulations! Flush with " << wSuit[suit[i]] << "'s" << endl; 
			return 120;
		}
		else if(4 == cardCount[suit[i]])
		{
			if(1 == turn)
			{
				cout << endl << "So Close! You should discard the ";
				for(int j = 0; j < 4; j++)
				{
					for(int k = 0; k < 13; k++)
					{
						if(j != suit[i] && 1 == hand[j][k])
						{
							cout << wFace[k] << " of " << wSuit[j] << endl; 
							hand[j][k] = 0; 
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}
int Player::checkStraight(const char *wFace[], const char *wSuit[], int turn)
{
	void bubbleSort(int *array, const int size);
	int face[5] = {};
	int counter = 0;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			if(hand[i][j] == 1)
			{
				face[counter] = j+1;
				counter++;
			}
		}
	}

	bubbleSort(face, 5);

	if(face[4] == face[3]+1 && face[3] == face[2]+1 && face[2] == face[1]+1 && face[1] == face[0]+1)
	{
		cout << "Straight!" << " " << wFace[face[0]-1] << ", " << wFace[face[1]-1] << ", " << wFace[face[2]-1] << ", " 
			<< wFace[face[3]-1] << ", " << wFace[face[4]-1] << "." << endl;
		return 200;
	}
	else if(face[3] == face[2]+1 && face[2] == face[1]+1 && face[1] == face[0]+1)
	{
		if(1 == turn)
		{
			cout << "You should pick up 1 card, and discard " << wFace[face[4]-1] << " of ";
			for(int i = 0; i < 4; i++){if(hand[i][face[4]-1] == 1){cout << wSuit[i] << endl;}}
			
			for(int i = 0; i < 4; i++)
			{
				if(hand[i][face[4]-1] == 1)
				{
					hand[i][face[4]-1] = 0;
					return 1;
					break;
				}
			}
		}
	}
	else if(face[4] == face[3]+1 && face[3] == face[2]+1 && face[2] == face[1]+1)
	{
		if(1 == turn)
		{
			cout << "You should pick up 1 card, and discard " << wFace[face[0]-1] << " of ";
			for(int i = 0; i < 4; i++){if(hand[i][face[0]-1] == 1){cout << wSuit[i] << endl;}}
			
			for(int i = 0; i < 4; i++)
			{
				if(hand[i][face[0]-1] == 1)
				{
					hand[i][face[0]-1] = 0;
					return 1;
					break;
				}
			}
		}
	}

	return 0;
}

void bubbleSort(int *array, const int size)
{
	void swap(int *element1Ptr, int *element2Ptr);
	for(int i = 0; i < size - 1; i++)
	{
		for(int j = 0; j < size - 1; j++)
		{
			if(array[j] > array[j+1]){swap(&array[j], &array[j+1]);}
		}
	}
}

void swap(int *element1Ptr, int *element2Ptr)
{
	int hold = *element1Ptr;
	*element1Ptr = *element2Ptr;
	*element2Ptr = hold;
}