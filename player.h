#include<iostream>
using namespace std;

void checkValidInput_bet(unsigned int &input, unsigned int bankroll);
void checkValidInput_buyIn(unsigned int &bankroll);
struct player
{
	char name[30];
	unsigned int bankroll;
	unsigned int score;
	unsigned int softScore;
	unsigned int splitScore;
	unsigned int splitSoftScore;
	card pocket[9];
	bool skip;
};

void newPlayer(player &P)
{
	cout << "New player's name: " << endl;
	cin >> P.name;
	cout << "How much would you like to buy-in for, " << P.name << "? (min. 50, max. 5000) " << endl;
	checkValidInput_buyIn(P.bankroll);
	cout << "Good luck, " << P.name << "!" << endl;

	P.score = 0;
	P.softScore = 0;
	P.skip = false;
}

bool bust(player P)
{
	if (P.score > 21) return true;
	return false;
}

void resetScore(player &P)
{
	P.score = 0;
	P.softScore = 0;
}

void dealCard(player &P, unsigned int &cardIndex, unsigned int &pocketIndex)
{
	P.pocket[pocketIndex] = deck[cardIndex];
	if (faceCard(deck[cardIndex])) P.score = P.score + 10;
	else P.score = P.score + P.pocket[pocketIndex].rank;
	pocketIndex++;
	cardIndex++;
}

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

void housePlay(player &house, unsigned int &cardIndex)
{
	unsigned int pocketIndex = 0;

	while (house.score < 17)
	{
		dealCard(house, cardIndex, pocketIndex);
		cout << "House holds: | ";
		for (unsigned int i = 0; i < pocketIndex; i++)
		{
			switch (house.pocket[i].rank)
			{
			case 1: cout << "Ace ";
				break;
			case 11: cout << "Jack ";
				break;
			case 12: cout << "Queen ";
				break;
			case 13:
				cout << "King ";
				break;
			default:
				cout << house.pocket[i].rank << ' ';
			}

			cout << "of ";
			cout << house.pocket[i].suit << ' ' << '|' << ' ';
		}

		cout << "(SCORE: " << house.score << ") " << endl;
	}
}

player table[4];

void emptySeat(unsigned int playerIndex, player table[4])
{
	table[playerIndex].bankroll = 0;
	strcpy_s(table[playerIndex].name, " **empty seat** ");
	for (unsigned int i = 0; i < 9; i++)
	{
		table[playerIndex].pocket[i].rank = 0;
		strcpy_s(table[playerIndex].pocket[i].suit, "*");
	}
	table[playerIndex].score = 0;
	table[playerIndex].softScore = 0;
	table[playerIndex].splitScore = 0;
	table[playerIndex].splitSoftScore = 0;
	table[playerIndex].skip = true;

}

void initializeTable(player table[4])
{
	for (unsigned int i = 0; i < 4; i++) emptySeat(i, table);
}

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

void showdown(player table[4], player house, unsigned int bets[4], unsigned int noOfPlayers)
{
	if (bust(house))
	{
		cout << "House is busted!" << endl;
		for (unsigned int i = 0; i < noOfPlayers; i++)
		if (bets[i])
		{
			table[i].bankroll += 2 * bets[i];
			cout << table[i].name << ", you won! (BANKROLL: " << table[i].bankroll << ')' << endl;
		}
	}

	else

	for (unsigned int i = 0; i < noOfPlayers; i++)
	if (table[i].skip == true) continue;
	else if (bets[i])
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

void addPlayers(unsigned int &noOfPlayers)
{
	do
	{
		cout << "How many players? (max. 4) ";
		cin >> noOfPlayers;
	} while (noOfPlayers < 1 || noOfPlayers > 4);

	for (unsigned int i = 0; i < noOfPlayers; i++) newPlayer(table[i]);
}

void checkValidInput_bet(unsigned int &input, unsigned int bankroll)
{
	bool ok;

	do
	{
		ok = true;
		cin >> input;

		if (std::cin.fail())
		{
			cout << "Bad entry! Please enter a valid bet: ";
			ok = false;
			std::cin.clear();
			std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		else if (input > bankroll) 
		cout << "You do not have that much money! Your bankroll: " << bankroll << endl << "Please enter a valid bet: ";
		else if (input < 1) cout << "Must bet at least 1! ";

	} while (ok == false || input < 1 || input > bankroll);

}

void checkValidInput_buyIn(unsigned int &bankroll)
{
	bool ok;

	do
	{
		ok = true;
		cin >> bankroll;

		if (std::cin.fail())
		{
			cout << "Bad entry! Please enter a number between 50 and 5000: ";
			ok = false;
			std::cin.clear();
			std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		else if (bankroll < 50 || bankroll > 5000) cout << "Please enter a number between 50 and 5000: ";

	} while (ok == false || bankroll < 50 || bankroll > 5000);
}

void getOption(player P, unsigned int pocketIndex, bool splitPossible)
{
	if (pocketIndex == 2)
	{
		if (P.pocket[0].rank == P.pocket[1].rank) splitPossible = true;
		cout << "your options: | 1. Hit | 2. Stand | 3. Double Down |";
		if (splitPossible) cout << " 4. Split |";
	}

	else cout << "your options: | 1. Hit | 2. Stand |";
	cout << endl;
}

bool isSeatEmpty(player table[4], unsigned int playerIndex)
{
	if (strcmp(table[playerIndex].name, " **empty seat** ") == 0) return true;
	else return false;
}

bool isTableEmpty(player table[4])
{
	for (unsigned int i = 0; i < 4; i++) if (isSeatEmpty(table, i) == false) return false;
	return true;
}

void removePlayer(player table[4], unsigned int playerIndex, unsigned int &noOfPlayers)
{
	cout << "REMOVING PLAYER " << table[playerIndex].name << endl;
	emptySeat(playerIndex, table);
	cout << "PLAYER REMOVED " << endl;
}