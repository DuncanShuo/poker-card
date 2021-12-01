#ifndef POKER_H
#define POKER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card {
public:
	Card(int, int);
	string toString();
	int getFace();
	int getSuit();
private:
	static string faceNames[13];
	static string suitNames[4];
	int face;
	int suit;
};

class DeckOfCards {
public:
	DeckOfCards();
	void shuffle();
	Card dealCard();
	bool moreCards();
	void reset();
private:
	int currentCard;
	vector<Card> deck;
};

class Hand {
public:
	Hand(DeckOfCards&);
	void print();
	void takeAgain(DeckOfCards&);
	bool pair() const;
	bool twoPair() const;
	bool threeOfAKind() const;
	bool fourOfAKind() const;
	bool flush() const;
	bool fullHouse() const;
	bool straight() const;
private:
	vector<Card> hand;
	int faceCount[13];
	int suitCount[4];
	int two;
	int three;
	int four;
};

#endif