
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
