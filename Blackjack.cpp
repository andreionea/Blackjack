#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;


int main(int argc, char* args[])
{
	system("color a");
	system("cls");

START:

	bool quit = false;

	cout << "Generating deck..." << endl;
	generateDeck();
	cout << "Deck generated!" << endl;

	initializeTable(table);

	system("pause");

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

		cout << "Shuffling deck..." << endl;
		shuffleDeck();
		cout << "Deck shuffled!..." << endl;

		system("pause");
		system("cls");


		while (playerIndex < noOfPlayers)
		{
			system("cls");

			if (table[playerIndex].skip == true) goto PLAYER_SKIPPED;

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
		
		PLAYER_SKIPPED:

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

		for (unsigned int i = 0; i < noOfPlayers; i++)
		{
			resetScore(table[i]);
			resetScore(house);
		}

		for (unsigned int i = 0; i < noOfPlayers; i++) 
		if (table[i].bankroll == 0 && table[i].skip == false) removePlayer(table, i, noOfPlayers);

		playerIndex = 0;
		cardIndex = 0;

		cout << isTableEmpty(table) << endl;

		if (isTableEmpty(table))
		{
			system("cls");
			cout << "No more players left. Add players? (y/n) ";
			char answer;
			do
			{
				cin >> answer;
				if (answer == 'y') goto START;
				else if (answer == 'n')
				{
					cout << "Thank you for playing! " << endl;
					quit = true;
				}
				else cout << "Bad input! Please type 'y' or 'n' ";
			} while (answer != 'y' && answer != 'n');
		}

		system("pause");
	}

	return 0;
}
