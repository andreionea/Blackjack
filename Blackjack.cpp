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

		player house;
		house.score = 0;

		unsigned int cardIndex = 0; 
		unsigned int playerIndex = 0;
		unsigned int bets[4];

		while (playerIndex < noOfPlayers)
		{
			system("cls");
			bool stand = false;
			bool splitPossible = false;
			bool split = false;
			unsigned int pocketIndex = 0;
			cout << table[playerIndex].name << ", place your bet! ";

			do
			{
				cin >> bets[playerIndex];
			} 
			while (bets[playerIndex] > table[playerIndex].bankroll);

			table[playerIndex].bankroll -= bets[playerIndex];

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
				case 2:
				{
					stand = true;
					if (table[playerIndex].score <= 21)
					{
						showPocket(table[playerIndex], pocketIndex);
						cout << "(SCORE: " << table[playerIndex].score << ')';
						cout << endl;
					}
				}
					break;
				case 3:
					{
						  dealCard(table[playerIndex], cardIndex, pocketIndex);
						  
						  if (table[playerIndex].score <= 21)
						  {
							  showPocket(table[playerIndex], pocketIndex);
							  cout << "(SCORE: " << table[playerIndex].score << ')';
							  cout << endl;
						  }
						  stand = true;
					}
					break;
				}

				if (table[playerIndex].score > 21)
				{	
					showPocket(table[playerIndex], pocketIndex);
					cout << ' ' << "(SCORE: " << ' ' << table[playerIndex].score << ')';
					cout << endl;
					cout << table[playerIndex].name << ", you are busted! (BANKROLL: " <<table[playerIndex].bankroll << ')' << endl;
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
			for (unsigned int i = 0; i < noOfPlayers; i++)
			if (bets[i])
			if (table[i].score > house.score)
			{
				cout << table[i].name << " (" << table[i].score <<"), you win! CONGRATULATIONS!!! ";
				table[i].bankroll = table[i].bankroll + 2 * bets[i];
				cout << "(BANKROLL: " << table[i].bankroll << ')' << endl;
			}

			else if (table[i].score == house.score)
			{
				cout << table[i].name << ", that's a push! ";
				table[i].bankroll += bets[i];
				cout << "(BANKROLL: " << table[i].bankroll << endl;
			}

			else
				cout << table[i].name << " (" << table[i].score << ") you lose! (BANKROLL: " << table[i].bankroll << ')' << endl;

			else cout << table[i].name << ", you lose! (BANKROLL: " << table[i].bankroll << ')' << endl;
		}

		system("pause");
	}

	return 0;
}
