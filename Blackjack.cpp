#include<iostream>
#include<string.h>
//#include "coada.h"
using namespace std;

struct card
{
	short rank;
	char suit[9];
};

card deck[52];

struct listNode_card
{
	card card;
	listNode_card* next;
};

void insert(listNode_card* &front, card addedCard)
{
	if (front == NULL)
	{
		listNode_card* newNode = new listNode_card;
		newNode->card = addedCard;
		newNode->next = NULL;
		front = newNode;
	}
	else
	{
		listNode_card* it = new listNode_card;
		it = front;

		while (it->next != NULL)
			it = it->next;

		listNode_card* newNode = new listNode_card;

		newNode->card = addedCard;
		newNode->next = NULL;

		it->next = newNode;
	}
}
void dismiss(listNode_card* &front)
{
	if (front == NULL) return;
	if (front->next == NULL) front = NULL;
	else
	{

		listNode_card* aux = new listNode_card;
		aux = front;

		front = front->next;

		aux->next = NULL;
		delete aux;
	}
}


void generateDeck();
void dealDeck();
void cutDeck(unsigned int randomBreak);
void riffleShuffle(unsigned int riffleBreak);
bool faceCard(card card);

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

void generateDeck()
{
	for (unsigned short i = 0; i < 13; i++)
	{
		deck[i].rank = i + 1;
		strcpy(deck[i].suit, "spades");
	}

	for (unsigned short i = 13; i < 26; i++)
	{
		deck[i].rank = i - 13 + 1;
		strcpy(deck[i].suit, "hearts");
	}

	for (unsigned short i = 26; i < 39; i++)
	{
		deck[i].rank = i - 26 + 1;
		strcpy(deck[i].suit, "clubs");
	}

	for (unsigned short i = 39; i < 52; i++)
	{
		deck[i].rank = i - 39 + 1;
		strcpy(deck[i].suit, "diamonds");
	}

	cout << "Deck generated!" << endl;

}

void dealDeck()
{
	for (unsigned short i = 0; i < 52; i++)
	{
		switch (deck[i].rank)
		{
		case 1: cout << "Ace ";
			break;
		case 11: cout << "Jack ";
			break;
		case 12: cout << "Queen ";
			break;
		case 13: cout << "King ";
			break;
		default: cout << deck[i].rank << ' ';
		}

		cout << "of" << ' ';
		cout << deck[i].suit << ' ';
		cout << endl;
	}
}

void cutDeck(unsigned int randomBreak)
{
	listNode_card* front;
	front = NULL;

	for (unsigned int i = 0; i < randomBreak; i++) insert(front, deck[i]);
	for (unsigned int i = randomBreak; i < 52; i++) deck[i - randomBreak] = deck[i];
	for (unsigned int i = 52 - randomBreak + 1; i < 52; i++)
	{
		deck[i] = front->card;
		dismiss(front);
	}
}

void riffleShuffle(unsigned int riffleBreak)
{
	listNode_card *front1, *front2;
	front1 = NULL;
	front2 = NULL;

	for (unsigned int i = 0; i < riffleBreak; i++) insert(front1, deck[i]);
	for (unsigned int i = riffleBreak; i < 52; i++) insert(front2, deck[i]);

	//to add random starter (chooses randomly weather to start with front1 or front2)
	//or make random tickTock every step
	//or both...probably both

	bool tickTock = true;
	unsigned int i = 0;

	while (front1 != NULL && front2 != NULL)
	{
		if (tickTock)
		{
			deck[i] = front1->card;
			dismiss(front1);
		}
		else
		{
			deck[i] = front2->card;
			dismiss(front2);
		}

		tickTock = !tickTock;

		i++;
	}


	if (front1 == NULL) 
	while (front2 != NULL)
	{
		deck[i] = front2->card;
		dismiss(front2);
	}
	else
	while (front1 != NULL)
	{
		deck[i] = front1->card;
		dismiss(front1);
	}

}

bool faceCard(card card)
{
	if (card.rank > 10) return true;
	return false;
}

