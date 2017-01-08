#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;

void dealCard(player &P, unsigned int &cardIndex, unsigned int &pocketIndex)
{
	P.pocket[pocketIndex] = deck[cardIndex];
	P.score = P.score + P.pocket[pocketIndex].rank;
	pocketIndex++;
	cardIndex++;
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

		while (playerIndex < noOfPlayers)
		{
			bool stand = false;
			bool split = false;
			unsigned int pocketIndex = 0;

			dealCard(table[playerIndex], cardIndex, pocketIndex);
			dealCard(table[playerIndex], cardIndex, pocketIndex);

			while (stand == false || bust(table[playerIndex]) == false)
			{
				cout << table[playerIndex].name << ", you hold: | ";
				for (unsigned int i = 0; i < pocketIndex; i++)
				{
					switch (table[playerIndex].pocket[i].rank)
					{
					case 11: cout << "Jack" << ' ';
						break;
					case 12: cout << "Queen" << ' ';
						break;
					case 13: cout << "King" << ' ';
						break;
					case 1: cout << "Ace" << ' ';
						break;
					default: cout << table[playerIndex].pocket[i].rank << ' ';
					}

					cout << "of ";
					cout << table[playerIndex].pocket[i].suit <<' ' <<  '|' << ' ';
				}

				cout << "(SCORE: " << table[playerIndex].score << ')' << ' ' << endl;
				cout << "your options: | 1. Hit | 2. Stand |";
				cout << endl;
				system("pause");
			}
		}

		system("pause");
	}

	return 0;
}
