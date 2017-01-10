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


	cout << "Shuffling deck..." << endl;
	shuffleDeck();
	cout << "Deck shuffled!..." << endl;

	unsigned int noOfPlayers;

	addPlayers(noOfPlayers);

	player house;
	house.score = 0;

	unsigned int cardIndex = 0;
	unsigned int playerIndex = 0;
	unsigned int bets[4];


	while (!quit)
	{

		system("cls");

		while (playerIndex < noOfPlayers)
		{
			system("cls");

			bool stand = false;
			bool splitPossible = false;
			bool split = false;
			unsigned int pocketIndex = 0;

			cout << table[playerIndex].name << ", place your bet! ";
			checkValidInput_bet(bets[playerIndex], table[playerIndex].bankroll);

			table[playerIndex].bankroll -= bets[playerIndex];

			dealCard(table[playerIndex], cardIndex, pocketIndex);
			dealCard(table[playerIndex], cardIndex, pocketIndex);

			if (table[playerIndex].score == 21)
			{
				cout << "BLACKJACK!!!!";
				table[playerIndex].bankroll = table[playerIndex].bankroll + bets[playerIndex] * 4;
				table[playerIndex].skip = true;
			}

			while (stand == false && bust(table[playerIndex]) == false && table[playerIndex].skip == false)
			{

			BEGIN_HAND:

				showPocket(table[playerIndex], pocketIndex);
				cout << "(SCORE: " << table[playerIndex].score << ')' << ' ' << endl;

				getOption(table[playerIndex], pocketIndex, splitPossible);

				unsigned short option;
				cin >> option;

				if(!processOption(option, table[playerIndex], bets, cardIndex, pocketIndex, playerIndex, stand)) goto BEGIN_HAND;

				if (table[playerIndex].score > 21)
				{
					showPocket(table[playerIndex], pocketIndex);
					cout << ' ' << "(SCORE: " << ' ' << table[playerIndex].score << ')';
					cout << endl;
					cout << table[playerIndex].name << ", you are busted! (BANKROLL: " << table[playerIndex].bankroll << ')' << endl;
					bets[playerIndex] = 0;
				}

				system("pause");
			}

			playerIndex++;
		}

		bool allPlayersBust = true;
		for (unsigned int i = 0; i < noOfPlayers; i++) if (bets[i]) allPlayersBust = false;

		if (!allPlayersBust)
		{
			system("cls");

			housePlay(house, cardIndex);

			showdown(table, house, bets, noOfPlayers);

		}

		system("pause");
	}

	return 0;
}
