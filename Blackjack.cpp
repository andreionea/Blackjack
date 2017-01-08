#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;

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


int main(int argc, char* args[])
{
	system("color a");

	bool quit = false;

	cout << "Generating deck..." << endl;
	generateDeck();
	cout << "Deck generated!" << endl;

	system("pause");

	while (!quit)
	{

		system("cls");

		cout << "Shuffling deck..." << endl;

		random_device rd;

		int firstBreak = rd() % 22 + 15;
		int secondBreak = rd() % 22 + 15; 
		int riffleBreak = rd() % 22 + 15;

		for (unsigned int count = 0; count <= 2; count++)
		{
			cutDeck(firstBreak);
			cutDeck(secondBreak);
			riffleShuffle(riffleBreak);
		}

		unsigned int noOfPlayers;

		do
		{
			cout << "How many players? (max. 4) ";
			cin >> noOfPlayers;
		} while (noOfPlayers < 1 || noOfPlayers > 4);

		for (unsigned int i = 0; i < noOfPlayers; i++) newPlayer(table[i]);

		unsigned int cardIndex = 0; 
		unsigned int playerIndex = 0;

		while (playerIndex <= noOfPlayers)
		{
			bool stand = false;
			bool splitPossible = false;
			bool split = false;
			unsigned int pocketIndex = 0;

			dealCard(table[playerIndex], cardIndex, pocketIndex);
			dealCard(table[playerIndex], cardIndex, pocketIndex);

			while (stand == false && bust(table[playerIndex]) == false)
			{
				showPocket(table[playerIndex], pocketIndex);
				cout << "(SCORE: " << table[playerIndex].score << ')' << ' ' << endl;
				if (pocketIndex == 2)
				{
					if (table[playerIndex].pocket[0].rank == table[playerIndex].pocket[1].rank) splitPossible = true;
					cout << "your options: | 1. Hit | 2. Stand | 3. Double Down |";
					if (splitPossible) cout << " 4. Split |";
				}

				else cout << "your options: | 1. Hit | 2. Stand |";
				cout << endl;
				unsigned short option;
				cin >> option;

				switch (option)
				{
				case 1: dealCard(table[playerIndex], cardIndex, pocketIndex);
					break;
				case 2: stand = true;
					break;
				case 3:
					{
						  dealCard(table[playerIndex], cardIndex, pocketIndex);
						  stand = true;
					}
					break;
				}
				if (table[playerIndex].score > 21)
				{	
					showPocket(table[playerIndex], pocketIndex);
					cout << ' ' << "(SCORE: " << ' ' << table[playerIndex].score << ')';
					cout << endl;
					cout << table[playerIndex].name << ", you are busted!" << endl;
				}
				system("pause");
			}

			
			playerIndex++;
		}
		system("pause");
	}

	return 0;
}
