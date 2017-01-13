#include<iostream>
#include<string.h>
#include<string>
#include "deck.h"
#include "player.h"
#include<random>
#include<Windows.h>
#include<stdlib.h>
using namespace std;

void checkValidInput_gameMode(string &gameMode)
{
	bool ok;

	do
	{
		ok = true;

		cin >> gameMode;
	
		if (gameMode.compare("i") == 0)
		{
			cout << "1. Classic Blackjack: Aces play for high and for low. Blackjack plays 4 to 1. ";
			cout << endl;
			cout << "2. High Risk, High Reward: " << endl;
			cout << '\t' << "- You play against a computer controlled Villain." << endl;
			cout << '\t' << "- If you are busted, you pay 3 to 1. " << endl;
			cout << '\t' << "- If you have higher score than Villain and none of you are busted and you beat the house, you get paid 4 to 1. " << endl;
			cout << '\t' << "- If you have lower score than Villain and none of you are busted, you pay 6 to 1. " << endl;
			cout << '\t' << "- If Villain is busted and you are not and you beat the house, you win 10 to 1. " << endl;
			cout << '\t' << "- Blackjack pays 8 to 1. " << endl;
			cout << '\t' << "- If Villain goes broke, your bankroll gets doubled. " << endl;
			ok = false;
			system("pause");
		}

		else if (gameMode.compare("2") != 0 && gameMode.compare("1") != 0)
		{
			cout << "Bad input! Please re-enter option: ";
			ok = false;
		}

	} while (ok == false);

	system("cls");
}

int main(int argc, char* args[])
{
	system("color 0F");
	system("cls");

START:

	bool quit = false;

	cout << "Welcome! Please choose a game mode: " << endl;
	cout << "| 1. Classic | 2. High Risk, High Reward | (hit 'i' for info) " << endl;

	string gameMode;
	checkValidInput_gameMode(gameMode);
	
	bool highRisk = false;

	if (gameMode.compare("2") == 0) highRisk = true;

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

	player villain;
	strcpy_s(villain.name, "Villain");
	villain.score = 0;
	villain.softScore = 0;
	villain.skip = false;
	villain.bankroll = 5000;

	unsigned int cardIndex = 0;
	unsigned int playerIndex = 0;
	unsigned int bets[4];

	while (!quit)
	{

		system("cls");

		cout << "Shuffling deck..." << endl;
		shuffleDeck();

		Sleep(3000);
		system("cls");


		while (playerIndex < noOfPlayers)
		{
			system("cls");

			if (!isSeatEmpty(table, playerIndex))
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
					showPocket(table[playerIndex], pocketIndex);
					cout << "BLACKJACK!!!!";
					table[playerIndex].bankroll = table[playerIndex].bankroll + bets[playerIndex] * 4;
					cout << "BANKROLL: " << table[playerIndex].bankroll << endl;
					table[playerIndex].skip = true;
					for (unsigned int i = 0; i < 9; i++) systemLighting();
					system("color 0F");
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
					if (secondChance(table[playerIndex], bets, pocketIndex, playerIndex, highRisk) == true) goto BEGIN_HAND;

					system("pause");
				}
			}

			playerIndex++;
		}

		unsigned int scoreToBeat = 17;

		if (highRisk == true)
		{
			system("cls");

			unsigned int villainPocketIndex = 0;
			bool villainStand = false;

			villainPlay(villain, cardIndex, villainPocketIndex, scoreToBeat, villainStand);

			for (unsigned int i = 0; i < noOfPlayers; i++)
			{
				if (bust(table[i]))
				{
					cout << table[i].name << ", you must pay the villain " << 3 * bets[i] << endl;
					villain.bankroll = villain.bankroll + 3 * bets[i];
					table[i].bankroll = table[i].bankroll - 2 * bets[i];
					bets[i] = 0;
				}

				else villainShowdown(villain, table, bets, i);
			}
			cout << "(Villain BANKROLL: " << villain.bankroll << ") " << endl;
		}

		system("pause");

		bool allPlayersBust = true;
		for (unsigned int i = 0; i < noOfPlayers; i++) 
		if (bets[i])
		{
			allPlayersBust = false;

			if (table[i].score > scoreToBeat) scoreToBeat = table[i].score;
		}

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


			Sleep(2000);
			system("cls");

			showdown(table, house, bets, noOfPlayers, highRisk);

		}

		if (villain.bankroll <= 0)
		{
			for (unsigned int i = 0; i < noOfPlayers; i++) table[i].bankroll *= 2;
			villain.bankroll = 5000;
		}

		for (unsigned int i = 0; i < noOfPlayers; i++)
		{
			resetScore(table[i]);
			resetScore(house);
			resetScore(villain);
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
	}

	return 0;
}