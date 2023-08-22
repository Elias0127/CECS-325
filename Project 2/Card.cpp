#include <iostream>
#include "Card.h"
#include <string>
#include <iostream>
using namespace std;
Card::Card()
{
    suit = 'X';
    rank = 'X';
}
Card::Card(char r, char s)
{
    rank = r;
    suit = s;
}
void Card::setCard(char r, char s)
{
    rank = r;
    suit = s;
}
int Card::getValue()
{
    if (rank == 'A')
        return 1; // If the rank of the Card is 'A', the point value is 1.
    else if (rank >= '2' && rank <= '9')
        return rank - '0'; // If the rank of the Card is between '2' and '9', the point value is equal to the rank.
    else
        return 10; // If the rank of the Card is 'T', 'J', 'Q' or 'K', the point value is 10.
}
void Card::show()
{
    string a = "";
    if (rank == 'A')
        a += "A";
    else if (rank == 'K')
        a += "K";
    else if (rank == 'Q')
        a += "Q";
    else if (rank == 'J')
        a += "J";
    else if (rank == 'T')
        a += "10";
    else
        a += (char)(rank);
    if (suit == 'S')
        a += "♠";
    else if (suit == 'D')
        a += "♦";
    else if (suit == 'H')
        a += "♥";
    else if (suit == 'C')
        a += "♣";
    cout << a;
}
