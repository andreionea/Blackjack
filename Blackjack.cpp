#include<iostream>
#include<string.h>
#include<string>
#include "deck.h"
#include "player.h"
#include<random>
#include<Windows.h>
using namespace std;


int main(int argc, char* args[])
{
	system("color 0F");
	system("cls");

START:

	bool quit = false;

	cout << "Generating deck..." << endl;
	generateDeck();
	cout << "Deck generated!" << endl;

	initializeTable(table);

	system("pause");
	system("cls");

	unsigned int noOfPlayers;
	string noOfPlayers_dummy;

	addPlayers(noOfPlayers_dummy);
	noOfPlayers = stoi(noOfPlayers_dummy);

	player house;
	house.score = 0;
	house.softScore = 0;

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

			if (table[playerIndex].skip == false)
			{
				bool stand = false;
				bool splitPossible = false;
				bool split = false;
				unsigned int pocketIndex = 0;

				cout << table[playerIndex].name << ", place your bet! ";

				string bet;
				checkValidInput_bet(bet, table[playerIndex].bankroll);
				bets[playerIndex] = stoi(bet);

				table[playerIndex].bankroll -= bets[playerIndex];

				dealCard(table[playerIndex], cardIndex, pocketIndex);
				dealCard(table[playerIndex], cardIndex, pocketIndex);

				if (table[playerIndex].pocket[0].rank == table[playerIndex].pocket[1].rank) splitPossible = true;

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
					getScore(table[playerIndex]);

					getOption(table[playerIndex], pocketIndex, splitPossible);

					string option_dummy;
					checkValidInput_option(option_dummy, pocketIndex, splitPossible);
					unsigned int option = stoi(option_dummy);

					if (!processOption(option, table[playerIndex], bets, cardIndex, pocketIndex, playerIndex, stand)) goto BEGIN_HAND;

					if (bust(table[playerIndex]))
					if(secondChance(table[playerIndex], bets, pocketIndex, playerIndex) == true) goto BEGIN_HAND;

					system("pause");
				}
			}

			playerIndex++;
		}

		bool allPlayersBust = true;
		for (unsigned int i = 0; i < noOfPlayers; i++) if (bets[i]) allPlayersBust = false;

		if (!allPlayersBust)
		{
			system("cls");

			unsigned int housePocketIndex = 0;

			housePlay(house, cardIndex, housePocketIndex);

			if (bust(house))
			if (house.softScore)
			{
				house.score = house.softScore;
				house.softScore = 0;
				
				housePlay(house, cardIndex, housePocketIndex);
			}

			showdown(table, house, bets, noOfPlayers);

			system("pause");
		}

		for (unsigned int i = 0; i < noOfPlayers; i++)
		{
			resetScore(table[i]);
			resetScore(house);
		}

		checkForRebuy(table, noOfPlayers);

		playerIndex = 0;
		cardIndex = 0;

		if (isTableEmpty(table)) 
		if (replay() == true) goto START;
		else
		{
			cout << "Thank you for playing! " << endl;
			quit = true;
		}
			
		system("pause");
	}

	return 0;
}
