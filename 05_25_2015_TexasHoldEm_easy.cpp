#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const std::string SUIT_STR[4] = {"Hearts", "Clubs", "Spades", "Diamonds"};
const std::string FACE_STR[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

int main()
{
    int numPlayers;
    std::cout << "How many players at the table? \n";
    std::cin >> numPlayers;

    Deck d;
    std::vector<Card> flop;
    Card turn;
    Card river;

    std::vector<Player> players;

    for (int i = 0; i < numPlayers; i++)
    {
        std::vector<Card> startingHand;
        startingHand.push_back(d.draw());
        startingHand.push_back(d.draw());
        players[i] = Player(startingHand);
    }

    d.discard();

    for (int i = 0; i < 3; i ++)
    {
        flop.push_back(d.draw());
    }

    d.discard();
    turn = d.draw();
    d.discard();
    river = d.draw();
}

class Card
{
    private:
        int suit, face;
    public:
        Card (int, int);
        int getSuit();
        int getFace();
        std::string toStr();
};

Card::Card(int s, int f)
{
    this->suit = s;
    this->face = f;
}

int Card::getSuit()
{
    return this->suit;
}

int Card::getFace()
{
    return this->face;
}

std::string Card::toStr()
{
    return (FACE_STR[this->face] + " of " + SUIT_STR[this->suit]);
}

class Player
{
    private:
        std::vector<Card> hand;
    public:
        Player(std::vector<Card>);
        std::vector<Card> getHand();
};

Player::Player(std::vector<Card> h)
{
    this->hand = h;
}

std::vector<Card> Player::getHand()
{
    return this->hand;
}

class Deck
{
    private:
        std::vector<Card> inDeck;
        std::vector<Card> discarded;
    public:
        Deck ();
        void shuffle();
        void discard(int);
        Card draw();
        int getCardsLeft();
};

Deck::Deck()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            inDeck.push_back(Card(i, j));
        }
    }
    this->shuffle();
}

void Deck::shuffle()
{
    this->inDeck.reserve(this->inDeck.size() + this->discarded.size());
    this->inDeck.insert(this->inDeck.end(), this->discarded.begin(), this->discarded.end());

    std::random_shuffle(this->inDeck.begin(), this->inDeck.end());
}

Card Deck::draw()
{
    Card c = this->inDeck.front();
    this->discarded.push_back(c);
    this->inDeck.erase(this->inDeck.begin());

    return c;
}

void Deck::discard(int n)
{
    this->inDeck.erase(this->inDeck.begin(), this->inDeck.begin()+n);
}

int Deck::getCardsLeft()
{
    return this->inDeck.size();
}
