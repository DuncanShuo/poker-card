#include "Poker.h"

string Card::faceNames[13] = { "Ace", "Deuce", "Three", "Four", "Five",
"Six","Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
string Card::suitNames[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };


Card::Card(int f, int s) :face(f), suit(s) {

}

string Card::toString() {
	string CardName;
	CardName = faceNames[face - 1] + " of " + suitNames[suit - 1];
	return CardName;
}

int Card::getFace() {
	return face;
}

int Card::getSuit() {
	return suit;
}

DeckOfCards::DeckOfCards() {
	for (int i = 1; i <= 13; i++) {
		for (int j = 1; j <= 4; j++) {
			deck.push_back(Card(i, j));
		}
	}
	currentCard = 0;
}

void DeckOfCards::shuffle() {
	srand(time(NULL));
	int max = 52;
	int x;

	Card temp(1, 1);
	for (int i = 0; i < 52; i++) {
		x = rand() % max;
		temp = deck[i];
		deck[i] = deck[x];
		deck[x] = temp;
	}
}

Card DeckOfCards::dealCard() {
	currentCard++;
	return deck[currentCard - 1];
}

bool DeckOfCards::moreCards() {
	return currentCard < 52;
}

void DeckOfCards::reset() {
	currentCard = 0;
}

Hand::Hand(DeckOfCards &deck) {
	for (int i = 0; i < 5; i++) {
		faceCount[i] = 0;
		suitCount[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		if (deck.moreCards() == 0) break;
		hand.push_back(deck.dealCard());
		faceCount[hand[i].getFace()]++;
		suitCount[hand[i].getSuit()]++;
	}
	two = 0;
	three = 0;
	four = 0;
	for (int i = 0; i < 13; i++) {
		if (faceCount[i] == 2) {
			two++;
		}
		else if (faceCount[i] == 3) {
			three++;
		}
		else if (faceCount[i] == 4) {
			four++;
		}
	}
}

void Hand::takeAgain(DeckOfCards &deck) {
	hand.clear();
	for (int i = 0; i < 5; i++) {
		faceCount[i] = 0;
		suitCount[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		if (deck.moreCards() == 0) break;
		hand.push_back(deck.dealCard());
		faceCount[hand[i].getFace()]++;
		suitCount[hand[i].getSuit()]++;
	}
	two = 0;
	three = 0;
	four = 0;
	for (int i = 0; i < 13; i++) {
		if (faceCount[i] == 2) {
			two++;
		}
		else if (faceCount[i] == 3) {
			three++;
		}
		else if (faceCount[i] == 4) {
			four++;
		}
	}
}

void Hand::print() {
	cout << "Hand is:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << hand[i].toString() << endl;
	}
	cout << endl;
}

bool Hand::pair() const {
	return two == 1 && three != 1;
}

bool Hand::twoPair() const {
	return two == 2;
}

bool Hand::threeOfAKind() const {
	return three == 1 && two != 1;
}

bool Hand::fourOfAKind() const {
	return four;
}

bool Hand::flush() const {
	for (int i = 0; i < 4; i++) {
		if (suitCount[i] == 5) return true;
	}
	return false;
}

bool Hand::fullHouse() const {
	return two == 1 && three == 1;
}

bool Hand::straight() const {
	int count = 0;
	for (int i = 1; i < 9; i++) {
		if (faceCount[i] == 1) {
			for (int j = 0; j < 5; j++) {
				count += faceCount[j];
			}
			if (count == 5) return true;
		}
	}
	count = 0;
	for (int i = 9; i < 13; i++) {
		count += faceCount[i];
	}
	if (count + faceCount[0] == 5) return true;
	return false;
}