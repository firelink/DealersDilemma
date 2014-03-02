#pragma once
#include <string>
#include <iostream>

using namespace std;

class Player
{

private:
	string playerName;
	int score;
	int hand[4][13];
	int face[13];
	int suit[4];

public:
	Player(string player);
	~Player();
	string getName(){return playerName;};
	void getHand(const char *wFace[], const char *wSuit[]);
	int getScore(){return score;};
	void setHand(const int wHand[][13]);
	void addHand(const int wHand[][13]);
	void setScore(int s){score = s;};
	int checkHand(const char *wFace[], const char *wSuit[], int turn);
	int checkTwoPair(const char *wFace[], const char *wSuit[]);
	int checkKinds(const char *wFace[], const char *wSuit[], int turn);
	int checkFlush(const char *wFace[], const char *wSuit[], int turn);
	int checkStraight(const char *wFace[], const char *wSuit[], int turn);

};