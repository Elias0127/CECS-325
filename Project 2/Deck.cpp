#include "Deck.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
Deck::Deck()
{
    char rank[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suit[] = {'S', 'H', 'D', 'C'};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            // Creates a new card object with the current suit and rank, and assigns it to the current index of the deck array.
            deck[index++].setCard(rank[j], suit[i]);
        }
    }
}
void Deck::resetDeck()
{
    index = 0; // reset the index to 0
    top = 0;
    char rank[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suit[] = {'S', 'H', 'D', 'C'};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            deck[index++].setCard(rank[j], suit[i]); // assign a new card to each index of the deck array
        }
    }
}
Card Deck::deal()
{
    if (isEmpty())
    {
        return Card(); // return a default card if the deck is empty
    }
    else
    {
        return deck[top++]; // return the current top card and increment the top value
    }
}
void Deck::shuffle()
{
    for (int i = 0; i < 52; i++)
    {
        int x = rand() % 52;
        int y = rand() % 52;
        Card temp = deck[x];
        deck[x] = deck[y];
        deck[y] = temp;
    }
}

bool Deck::isEmpty()
{
    return top > 52;
}
void Deck::show()
{
    for (int i = 0; i < 52; i++)
    {
        deck[i].show();
        if ((i + 1) % 13 == 0) // after every 13 cards, go to a new line
        {
            cout << endl;
        }
        else
        {
            cout << ", "; // separate each card with a comma
        }
    }
}
