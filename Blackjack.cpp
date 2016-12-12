#include<iostream>
#include<string.h>
#include "card.h"
#include "card_queue.h"
#include "deck.h"
using namespace std;


int main(int argc, char* args[])
{
	system("color 40");
	bool quit = false;

	cout << "Generating deck...";
	generateDeck();

	while (!quit)
	{
		system("cls");
		cutDeck(26);
		cutDeck(13);
		riffleShuffle(26);
		dealDeck();
		system("pause");
	}

	return 0;
}









