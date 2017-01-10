#include<iostream>
#include<random>
using namespace std;

struct card
{
	short rank;
	char suit[9];
};

bool faceCard(card card)
{
	if (card.rank > 10) return true;
	return false;
}

struct listNode_card
{
	card card;
	listNode_card* next;
};

card deck[52];

void generateDeck();
void dealDeck();
void cutDeck(unsigned int randomBreak);
void riffleShuffle(unsigned int riffleBreak);
void dismiss(listNode_card* &front);
void insert(listNode_card* &front, card addedCard);


void generateDeck()
{
	for (unsigned short i = 0; i < 13; i++)
	{
		deck[i].rank = i + 1;
		strcpy_s(deck[i].suit, "spades");
	}

	for (unsigned short i = 13; i < 26; i++)
	{
		deck[i].rank = i - 13 + 1;
		strcpy_s(deck[i].suit, "hearts");
	}

	for (unsigned short i = 26; i < 39; i++)
	{
		deck[i].rank = i - 26 + 1;
		strcpy_s(deck[i].suit, "clubs");
	}

	for (unsigned short i = 39; i < 52; i++)
	{
		deck[i].rank = i - 39 + 1;
		strcpy_s(deck[i].suit, "diamonds");
	}

}

void dealDeck()
{
	for (unsigned short i = 0; i < 52; i++)
	{
		cout << i << "." << ' ';
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
	for (unsigned int i = 52 - randomBreak; i < 52; i++)
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

	bool tickTock = 1;
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
		i++;
	}
	else
	while (front1 != NULL)
	{
		deck[i] = front1->card;
		dismiss(front1);
		i++;
	}

}

void shuffleDeck()
{
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
}

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
