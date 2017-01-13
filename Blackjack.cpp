#include<iostream>
#include<string.h>
#include "deck.h"
#include "player.h"
#include<random>
using namespace std;

void play(unsigned int noOfPlayers, player P[4], bool &quit);
void dealCard(player currentPlayer, unsigned int &cardIndex);
void showPocket(player currentPlayer, unsigned int pocketIndex, unsigned int seat);

int main(int argc, char* args[])
{
	system("color a");

	unsigned int seat = 0;

	while (seat < 4)
	{
		cout << "Add player? (y/n) ";
		char answer;
		cin >> answer;

		if (answer == 'y')
		{
			player new_player;
			new_player.bankroll = 0;
			new_player.score = 0;
			new_player.softScore = 0;
			new_player.splitScore = 0;
			new_player.splitSoftScore = 0;
			newPlayer(new_player);
			P[seat] = new_player;
			seat++;
		}

		else break;

	}

	bool quit;

	if (seat)
	{
		cout << "Generating deck..." << endl;
		generateDeck();
		cout << "Deck generated!" << endl;
		quit = false;
	}

	system("pause");

START:

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

		cout << "Deck shuffled!" << endl;

		play(seat, P, quit);

		system("pause");
	}

	return 0;
}


void play(unsigned int noOfPlayers, player P[4], bool &quit)
{
	unsigned int seat = 0;
	unsigned int cardIndex = 0;

	while (seat < noOfPlayers)
	{
		unsigned int pocketIndex = 0;

		dealCard(P[seat], cardIndex); pocketIndex++;
		if (faceCard(P[seat].pocket[pocketIndex])) P[seat].score += 10;
		else P[seat].score += P[seat].pocket[pocketIndex].rank;
		

		dealCard(P[seat], cardIndex); pocketIndex++;
		if (faceCard(P[seat].pocket[pocketIndex])) P[seat].score += 10;
		else P[seat].score += P[seat].pocket[pocketIndex].rank;
		

		showPocket(P[seat], pocketIndex, seat);

		if (P[seat].score == 21)
		{
			cout << "BLACKJACK!!!" << endl;
			P[seat].bankroll += P[seat].bankroll;
		}

		else
		{
			if ((P[seat].pocket[pocketIndex - 1].rank == P[seat].pocket[pocketIndex].rank) && (P[seat].pocket[pocketIndex - 1].suit == P[seat].pocket[pocketIndex].suit))
			{
				cout << P[seat].name << ", split? (y/n)" << endl;
			}
		}

		seat = 8;
	}

	quit = true;
}

void dealCard(player currentPlayer, unsigned int &cardIndex)
{
	currentPlayer.pocket[cardIndex] = deck[cardIndex];
	cardIndex++;
}


void showPocket(player currentPlayer, unsigned int pocketIndex, unsigned int seat)
{
	cout << currentPlayer.name << ", you hold: ";
	for (unsigned int i = 0; i < pocketIndex; i++)
	{
		switch (currentPlayer.pocket[i].rank)
		{
		case 1: cout << "Ace of" << ' ' << currentPlayer.pocket[i].suit;
			break;
		case 11: cout << "Jack of" << ' ' << currentPlayer.pocket[i].suit;
			break;
		case 12: cout << "Queen of" << ' ' << currentPlayer.pocket[i].suit;
			break;
		case 13: cout << "King of" << ' ' << currentPlayer.pocket[i].suit;
			break;
		default: cout << currentPlayer.pocket[i].rank << ' ' << "of" << ' ' << currentPlayer.pocket[i].suit << ' ';
		}	

		if (i != pocketIndex - 1) cout << ',' << ' ';
	}
	cout <<' ' << '(' << currentPlayer.score << ')';
	cout << endl;
}


