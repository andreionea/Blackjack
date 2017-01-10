#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;

void playerStand(bool &stand, player P, unsigned int pocketIndex)
{
	stand = true;

	if (P.score <= 21)
	{
		showPocket(P, pocketIndex);
		cout << "(SCORE: " << P.score << ')';
		cout << endl;
	}
}

void playerDoubleDown(player &P, unsigned int bets[4], unsigned int playerIndex, unsigned int pocketIndex, unsigned int &cardIndex, bool &stand)
{
	dealCard(P, cardIndex, pocketIndex);

	P.bankroll = P.bankroll - bets[playerIndex];
	bets[playerIndex] = 2 * bets[playerIndex];


	if (P.score <= 21)
	{
		showPocket(P, pocketIndex);
		cout << "(SCORE: " << P.score << ')';
		cout << endl;
	}

	stand = true;
}

bool processOption(unsigned short option, player P, unsigned int bets[4], unsigned int &cardIndex, unsigned int &pocketIndex, unsigned int playerIndex, bool &stand)
{
	switch (option)
	{
	case 1: dealCard(table[playerIndex], cardIndex, pocketIndex);
		break;

	case 2: playerStand(stand, table[playerIndex], pocketIndex);
		break;

	case 3:
		{
			  if (table[playerIndex].bankroll < bets[playerIndex])
			  {
				  cout << "Not enough money for a double down!" << endl;
				  return false;
			  }

			  playerDoubleDown(table[playerIndex], bets, playerIndex, pocketIndex, cardIndex, stand);
		}
		break;

	default:
		{
			   cout << "Invalid option! " << endl;
			   return false;
		}

	}

	return true;
}

int main(int argc, char* args[])
{
	system("color a");

	bool quit = false;

	cout << "Generating deck..." << endl;
	generateDeck();
	cout << "Deck generated!" << endl;

	system("pause");


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

			do
			{
				cin >> bets[playerIndex];
			} while (bets[playerIndex] > table[playerIndex].bankroll);

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

			if (bust(house))
			{
				cout << "House is busted!" << endl;
				for (unsigned int i = 0; i < noOfPlayers; i++)
				if (bets[i])
				{
					table[i].bankroll += 2 * bets[i];
					cout << table[playerIndex].name << ", you won! (BANKROLL: " << table[playerIndex].bankroll << ')' << endl;
				}
			}

			else

			for (unsigned int i = 0; i < noOfPlayers; i++)
			if (bets[i])
			{
				if (table[i].score == house.score)
				{
					cout << table[i].name << ", that's a push! ";
					table[i].bankroll += bets[i];
					cout << "(BANKROLL: " << table[i].bankroll << endl;
				}

				else if (table[i].score > house.score)
				{
					cout << table[i].name << " (" << table[i].score << "), you win! CONGRATULATIONS!!! ";
					table[i].bankroll = table[i].bankroll + 2 * bets[i];
					cout << "(BANKROLL: " << table[i].bankroll << ')' << endl;
				}

				else cout << table[i].name << " (" << table[i].score << ") you lose! (BANKROLL: " << table[i].bankroll << ')' << endl;
			}

			else cout << table[i].name << ", you lose! (BANKROLL: " << table[i].bankroll << ')' << endl;
		}

		system("pause");
	}

	return 0;
}
