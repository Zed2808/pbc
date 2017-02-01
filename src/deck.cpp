#include <algorithm>
#include "deck.hpp"

std::string suit_to_string(Suit suit) {
	switch(suit) {
		case Suit::SPADES:
			return "SPADES";
		case Suit::HEARTS:
			return "HEARTS";
		case Suit::DIAMONDS:
			return "DIAMONDS";
		case Suit::CLUBS:
			return "CLUBS";
		default:
			return "SPADES";
	}
}

std::string suit_to_char(Suit suit) {
	switch(suit) {
		case Suit::SPADES:
			return "\u2660";
		case Suit::HEARTS:
			return "\u2661";
		case Suit::DIAMONDS:
			return "\u2662";
		case Suit::CLUBS:
			return "\u2663";
		default:
			return "\u2660";
	}
}

std::string value_to_char(int value) {
	switch(value) {
		case 10:
			return "T";
			break;
		case 11:
			return "J";
			break;
		case 12:
			return "Q";
			break;
		case 13:
			return "K";
			break;
		case 14:
			return "A";
			break;
		default:
			return std::to_string(value);
	}
}

Card::Card() {
	suit = Suit::SPADES;
	value = 14;
}

Card::Card(Suit suit, int value) {
	this->suit = suit;
	this->value = value;
}

Suit Card::get_suit() {
	return suit;
}

int Card::get_value() {
	return value;
}

std::string Card::to_string() {
	return value_to_char(get_value()) + suit_to_char(get_suit());
}

Deck::Deck(bool filled) {
	if(filled) fill_deck();
}

void Deck::fill_deck() {
	for(int value = 2; value <= 14; value++) {
		deck.push_back(Card(Suit::SPADES, value));
		deck.push_back(Card(Suit::HEARTS, value));
		deck.push_back(Card(Suit::DIAMONDS, value));
		deck.push_back(Card(Suit::CLUBS, value));
	}

	shuffle();

	cards_left = 52;
}

void Deck::shuffle() {
	srand(time(0));
	std::random_shuffle(deck.begin(), deck.end());
}

Card Deck::draw() {
	cards_left--;
	Card card = deck.back();
	deck.pop_back();
	return card;
}

void Deck::add_card(Card card) {
	deck.push_back(card);
}

void Deck::remove_card(int index) {
	deck.erase(deck.begin() + index);
}

int Deck::get_cards_left() {
	return cards_left;
}

int Deck::size() {
	return deck.size();
}

std::string Deck::to_string() {
	std::string output = "";
	for(Card card : deck) {
		output += card.to_string() + " ";
	}
	return output;
}
