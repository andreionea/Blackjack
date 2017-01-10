#include<iostream>
using namespace std;

struct player
{
	char name[30];
	unsigned int bankroll;
	unsigned int score;
	unsigned int softScore;
	unsigned int splitScore;
	unsigned int splitSoftScore;
	card pocket[9];
};

void newPlayer(player P)
{
	cout << "New player's name: " << endl;
	cin >> P.name;
	cout << "How much would you like to buy-in for, " << P.name << "?" << endl;
	cin >> P.bankroll;
	cout << "Good luck, " << P.name << "!" << endl;
}

bool bust(player P)
{
	if (P.score > 21) return true;
	return false;
}

void resetScore(player P)
{
	P.score = 0;
	P.softScore = 0;
}

player P[4];