/*
   Elias Woldie
   CECS 325 Sec02
   Prog1 - Fibonacci Solitaire
*/

#include "Deck.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

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