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
