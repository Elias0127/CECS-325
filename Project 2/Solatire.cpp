#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Card
{

public:
    Card();               // create a “default” card
    Card(char r, char s); // constructor to create a card, setting the rank and suit
    char rank;
    char suit;
    void setCard(char r, char s); // set existing card to new values
    int getValue();               // return the point value of the card. Ace = 1, 2 thru 10, Jack = 10, Queen = 10, King = 10
    void show();                  // show the card using 2 fields… Ace of Spade:AS, Ten of Diamond:10D, Queen of Heart:QH, Three of Club:3C.
};

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

class Deck
{
private:
    Card deck[52]; // Length of the deck
    int top;       // To keep track of which card is at the top of the deck
    int index;     // reset the index to 0

public:
    Deck()
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

    void resetDeck()
    {
        index = 0; 
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

    Card deal()
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

    void shuffle()
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

    bool isEmpty()
    {
        return top > 52;
    }

    void show()
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
};

bool isFibo(int num)
{
    int a = 0, b = 1, c = 1;
    while (c < num)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c == num;
}

int main()
{
    Deck deck;
    int choice;
    int count = 0;
    int sum = 0;

    cout << endl
         << "Welcome to Fibonacci Solitaire!" << endl;
    while (true)
    {
        cout << endl
             << "1. Create New Deck" << endl;
        cout << "2. Shuffle Deck" << endl;
        cout << "3. Display Deck" << endl;
        cout << "4. Play Fibo Solitaire" << endl;
        cout << "5. Win Fibo Solitaire" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            deck.resetDeck();
            break;
        case 2:
            deck.shuffle();
            break;
        case 3:
            deck.show();
            break;
        case 4:
            deck.resetDeck(); // reset the deck to its original state
            deck.shuffle();   // shuffle the deck to have a new game
            sum = 0;          // sum of the values of the dealt cards
            count = 0;        // number of piles in which the sum of the values is a fibonacci number

            cout << "Playing Fibonacci Solitaire !!!" << endl;
            cout << endl;

            // loop until the deck is empty
            while (!deck.isEmpty())
            {
                Card current = deck.deal(); // deal a card from the deck
                current.show();             // display the card
                cout << ", ";
                sum += current.getValue(); // add the value of the card to the sum

                // If the sum is a fibonacci number increment the count and display the sum and reset the sum to 0
                if (isFibo(sum))
                {
                    count++;
                    cout << "Fibo: " << sum << endl;
                    sum = 0;
                }
            }
            // If the final sum is 0, displays that the player has won else that the player has lost

            if (sum == 0)
            {
                cout << endl
                     << "\nWinner in " << count << " piles!" << endl;
            }
            else
            {
                cout << endl
                     << "\nLosser in " << count << " piles!" << endl;
            }
            break;
        case 5:
        {
            // counter to keep track of how many games were played
            int gamesPlayed = 0;

            // Keep playing the game until the player wins
            while (true)
            {
                deck.resetDeck();
                deck.shuffle();
                int count = 0;
                int sum = 0;

                // Play the game until the deck is empty
                while (!deck.isEmpty())
                {
                    Card current = deck.deal(); // Deal the top card from the deck
                    sum += current.getValue();  // Add the value of the dealt card to the sum

                    // If it is a Fibonacci number, increment the count and reset the sum to zero
                    if (isFibo(sum))
                    {
                        count++;
                        sum = 0;
                    }
                }
                gamesPlayed++;
                // Check if the final sum is zero (meaning all the cards formed Fibonacci piles)
                if (sum == 0)
                {
                    cout << "Playing Fibonacci Solitaire !!!" << endl;
                    cout << endl;
                    deck.show();
                    cout << endl
                         << "Winner in " << count << " piles!" << endl;
                    cout << endl
                         << "Games played: " << gamesPlayed << endl;
                    break;
                }
            }
            break;
        }

        case 6:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
