//  Elias Woldie
// CECS 325 Sec02
#include <iostream>
#include <stdexcept>

using namespace std;

struct Stats
{
    int start;
    int steps;
    int max;
    int odds;
    int evens;
};

Stats collatz_threeN(int n, int steps, int max, int odds, int evens, int &last_n)
{
    // Print the current value of n
    cout << "->(" << n << ")";

    // Base case: if n is 1, return the computed stats
    if (n == 1)
    {
        return {n, steps, max, odds, evens};
    }

    int next_n;
    if (n % 2 == 0)
    {
        // If n is even, set the next value to n/2 and increment the number of even numbers
        next_n = n / 2;
        evens++;
    }
    else
    {
        if (n > (2147483647 - 1) / 3)
        {
            // If n is odd and the next value is too large, throw an overflow error
            cout << "->(###overflow###)" << endl;
            throw std::overflow_error("Integer overflow");
        }
        // If n is odd, set the next value to 3n+1 and increment the number of odd numbers
        next_n = 3 * n + 1;
        odds++;
    }

    // Update the stats and the last computed value of n
    max = std::max(max, next_n);
    steps++;
    last_n = next_n;

    // call collatz_threeN recursively with the next value of n
    return collatz_threeN(next_n, steps, max, odds, evens, last_n);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Enter a 3n+1 candidate number" << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        int n = atoi(argv[i]);
        int last_n = n; // used to store the last computed value of n in case of an overflow error

        try
        {
            cout << "Solving 3n+1 - starting value: " << n << endl;
            Stats stats = collatz_threeN(n, 0, n, 0, 0, last_n);
            cout << endl;
            cout << " start: " << n << endl;
            cout << " steps: " << stats.steps << endl;
            cout << " max: " << stats.max << endl;
            cout << " odds: " << stats.odds << endl;
            cout << " evens: " << stats.evens << endl;
        }
        catch (const std::overflow_error &e)
        {
            // If an overflow error was thrown print this stats
            cout << "overflow detected for n: " << last_n << endl;
            cout << "3n + 1: " << 3 * last_n + 1 << endl;
            cout << "something broke dude" << endl;
            cout << "overflow" << endl;
        }

        cout << "----------------------------------------" << endl;
    }

    return 0;
}
