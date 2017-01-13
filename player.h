#include<iostream>
#include<string.h>
using namespace std;

void checkValidInput_bet(unsigned int &input, unsigned int bankroll);
void checkValidInput_buyIn(string &bankroll);
inline bool isInteger(const std::string & s);

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
	cout << "New player's name: ";
	cin.get();
	cin.get(P.name, 30);
	cout << "How much would you like to buy-in for, " << P.name << "? (min. 50, max. 5000) ";
	string answer;
	checkValidInput_buyIn(answer);
	P.bankroll = stoi(answer);
	cout << "Good luck, " << P.name << "!" << endl;
	system("pause");

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

	if (faceCard(P.pocket[pocketIndex]))
	{
		P.score = P.score + 10;
		if (P.softScore) P.softScore += 10;
	}

	else if (P.pocket[pocketIndex].rank == 1)
	{
		if (P.softScore == 0) P.softScore += P.score + 1;
		P.score += 11;
	}

	else
	{
		P.score = P.score + P.pocket[pocketIndex].rank;
		if (P.softScore) P.softScore += P.pocket[pocketIndex].rank;
	}

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

void getScore(player P)
{
	if (P.softScore) 
		cout << "(SCORE: " << P.score << " / soft: " << P.softScore << ") " << endl;
	else cout << "(SCORE: " << P.score << ')' << ' ' << endl;
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



bool processOption(unsigned int option, player P, unsigned int bets[4], unsigned int &cardIndex, unsigned int &pocketIndex, unsigned int playerIndex, bool &stand)
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
			cout << "(BANKROLL: " << table[i].bankroll << ") " << endl;
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

void addPlayers(string &noOfPlayers)
{
	bool ok;
	int noOfPlayers_number;

	do
	{
		ok = true;

		cout << "How many players? (max. 4) ";
		cin >> noOfPlayers;

		if (!isInteger(noOfPlayers))
		{
			cout << "Bad input! " << endl;
			ok = false;
		}

		if (ok == true)
		{
			noOfPlayers_number = stoi(noOfPlayers);

			if (noOfPlayers_number > 4)
			{
				cout << "Maximum 4 players! " << endl;
				ok = false;
			}

			else if (noOfPlayers_number < 1)
			{
				cout << "Must have at least one player! " << endl;
				ok = false;
			}
		}

	} while (ok == false);

	for (unsigned int i = 0; i < noOfPlayers_number; i++) newPlayer(table[i]);
}

inline bool isInteger(const string &s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}


void checkValidInput_bet(string &bet, unsigned int bankroll)
{
	bool ok;

	do
	{
		ok = true;

		cin >> bet;

		if (!isInteger(bet))
		{
			cout << "Please enter a valid bet: ";
			ok = false;
		}

		if (ok == true)
		{
			int bet_number = stoi(bet);

			if (bet_number < 1)
			{
				cout << "Bet must be at least 1! ";
				cout << "Please enter a valid bet: ";
				ok = false;
			}

			if (bet_number > bankroll)
			{
				cout << "You do not have that much money! (BANKROLL: " << bankroll << ") " << endl;
				cout << "Please enter a valid bet: ";
				ok = false;
			}
		}
	} while (ok == false);

}

void checkValidInput_buyIn(string &bankroll)
{
	bool ok;

	do
	{
		ok = true;

		cin >> bankroll;

		if (isInteger(bankroll) == false)
		{
			cout << "Bad input! Please enter a number: ";
			ok = false;
		}

		if (ok == true)
		{
			int bankroll_number = stoi(bankroll);

			if (bankroll_number < 50 || bankroll_number > 5000)
			{
				cout << "Please enter a number between 50 and 5000: ";
				ok = false;
			}
		}

	} while (ok == false);
}

void checkValidInput_option(string &option, unsigned int pocketIndex, bool splitPossible)
{
	bool ok;

	do
	{
		ok = true;
		cin >> option;

		if (pocketIndex == 2)
		{
			if (option.length() > 1)
			{
				cout << "Bad input! Please re-enter option: ";
				ok = false;
			}

			else if (option.compare("1") != 0 && option.compare("2") != 0 && option.compare("3") != 0)
			{
				if (splitPossible && option.compare("4"))
				{
					cout << "Split not yet supported... :( " << endl;
					ok = false;
				}
				else
				{
					cout << "Bad input! Please re-enter option: ";
					ok = false;
				}
			}

			else ok = true;
		}

		else if (option.compare("1") != 0 && option.compare("2") != 0)
		{
			cout << "Bad input! Please re-enter option: ";
			ok = false;
		}

	} while (ok == false);
}

void getOption(player P, unsigned int pocketIndex, bool splitPossible)
{
	if (pocketIndex == 2)
	{
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
	cout << "REMOVING PLAYER: " << table[playerIndex].name << endl;
	emptySeat(playerIndex, table);
	cout << "PLAYER REMOVED " << endl;
}

void checkForRebuy(player table[4], unsigned int noOfPlayers)
{
	for (unsigned int i = 0; i < noOfPlayers; i++)
	if (table[i].bankroll == 0 && table[i].skip == false)
	{
		cout << table[i].name << ", would you like to rebuy? " << endl << " | 1. Yes | 2. No | " << endl;
		string answer;
		do
		{
			cin >> answer;
		} while (answer.compare("1") != 0 && answer.compare("2") != 0);

		if (answer.compare("2") == 0) removePlayer(table, i, noOfPlayers);
		else if (answer.compare("1") == 0)
		{
			cout << "How much would you like to rebuy for? (min. 50, max. 5000) ";
			string answer;
			checkValidInput_buyIn(answer);
			table[i].bankroll = stoi(answer);
		}
	}
}

bool secondChance(player &P, unsigned int bets[4], unsigned int pocketIndex, unsigned int playerIndex)
{
	{
		if (P.softScore)
		{
			P.score = P.softScore;
			P.softScore = 0;
			return true;
		}

		else
		{
			showPocket(P, pocketIndex);
			getScore(P);
			cout << P.name << ", you are busted! (BANKROLL: " << P.bankroll << ')' << endl;
			bets[playerIndex] = 0;
		}
	}
}

bool replay()
{
	system("cls");
	cout << "No more players left. Add players? (y/n) ";
	string answer;
	do
	{
		cin >> answer;
		if (answer.compare("y") == 0) return true;
		else if (answer.compare("n") == 0) return false;
		else cout << "Bad input! Please type 'y' or 'n' ";

	} while (answer.compare("y") != 0 && answer.compare("n") != 0);
}