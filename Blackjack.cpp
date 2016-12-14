#include<iostream>
#include<string.h>
#include "deck.h"
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

		int firstBreak = rd() % 22 + 15; cout << firstBreak << endl;
		int secondBreak = rd() % 22 + 15; cout << secondBreak << endl;
		int riffleBreak = rd() % 22 + 15; cout << riffleBreak << endl;

		for (unsigned int count = 0; count <= 2; count++)
		{
			cutDeck(firstBreak);
			cutDeck(secondBreak);
			riffleShuffle(riffleBreak);
		}

		dealDeck();

		system("pause");
	}

	return 0;
}









