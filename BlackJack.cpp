#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;


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

		system("pause");
	}

	return 0;
}
