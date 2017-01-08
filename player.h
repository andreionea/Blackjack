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

void newPlayer(player &P)
{
	cout << "New player's name: " << endl;
	cin >> P.name;
	cout << "How much would you like to buy-in for, " << P.name << "?" << endl;
	cin >> P.bankroll;
	cout << "Good luck, " << P.name << "!" << endl;

	P.score = 0;
	P.softScore = 0;
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

void dealCard(player &P, unsigned int &cardIndex, unsigned int &pocketIndex)
{
	P.pocket[pocketIndex] = deck[cardIndex];
	if (faceCard(deck[cardIndex])) P.score = P.score + 10;
	else P.score = P.score + P.pocket[pocketIndex].rank;
	pocketIndex++;
	cardIndex++;
}

void showPocket(player P, unsigned int pocketIndex)
{
	cout << P.name << ", you hold: | ";
	for (unsigned int i = 0; i < pocketIndex; i++)
	{
		switch (P.pocket[i].rank)
		{
		case 11: cout << "Jack" << ' ';
			break;
		case 12: cout << "Queen" << ' ';
			break;
		case 13: cout << "King" << ' ';
			break;
		case 1: cout << "Ace" << ' ';
			break;
		default: cout << P.pocket[i].rank << ' ';
		}

		cout << "of ";
		cout << P.pocket[i].suit << ' ' << '|' << ' ';
	}
}

void housePlay(player &house, unsigned int &cardIndex)
{
	unsigned int pocketIndex = 0;

	while (house.score < 17)
	{
		dealCard(house, cardIndex, pocketIndex);
		cout << "House holds: | ";
		for (unsigned int i = 0; i < pocketIndex; i++)
		{
			switch (house.pocket[i].rank)
			{
			case 1: cout << "Ace ";
				break;
			case 11: cout << "Jack ";
				break;
			case 12: cout << "Queen ";
				break;
			case 13:
				cout << "King ";
				break;
			default:
				cout << house.pocket[i].rank << ' ';
			}

			cout << "of ";
			cout << house.pocket[i].suit << ' ' << '|' << ' ';
		}

		cout << "(SCORE: " << house.score << ") " << endl;
	}
}




player table[4];