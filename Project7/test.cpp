// 3n+1 test driver
#include <iostream>
#include <limits.h>
#include "BigInt.h" // please include the BigInt class in the main file
using namespace std;
// create struct to store all details of 3n+1 sequences
struct ThreeNp1
{
    BigInt start;
    BigInt steps;
    BigInt max;
    BigInt odd;
    BigInt even;
};
// utility function to see details of 3n+1 sequence
// notice that all values are BigInt… cout << BigInt
void print(ThreeNp1 temp)
{
    cout << "start:" << temp.start << endl;
    cout << "steps:" << temp.steps << endl;
    cout << "max:" << temp.max << endl;
    cout << "odds:" << temp.odd << endl;
    cout << "evens:" << temp.even << endl;
}
// recursive function to find all details about 3n+1 sequence
// Function has a default parameter as the 3rd parameter
void findThreeNp1(BigInt n, ThreeNp1 &Np1, bool printSteps = false)
{
    if (printSteps)
    {
        cout << "->" << '(' << n << ')';
    }
    if (Np1.max < n) // BigInt::operator<( )
        Np1.max = n; // No need to overload - C++ provides operator=( )

    if (n == BigInt(1)) // BigInt::operator==( )
    {
        return; // we are done
    }
    else if (n.isEven()) // BigInt::isEven()
    {
        Np1.even++; // BigInt::operator++( )
        Np1.steps++;
        // findThreeNp1(n/2,N, printSteps); // BigInt::operator/( ) - Hard…
        findThreeNp1(n.half(), Np1, printSteps); // BigInt::half( ) - Easy
    }
    else if (n.isOdd()) // BigInt::isOdd( )
    {
        Np1.odd++;
        Np1.steps++;
        BigInt tempN(n);                                            // BigInt constructor
        findThreeNp1(tempN * BigInt(3) + BigInt(1), Np1, printSteps); // BigInt::operator*( )
        // BigInt::operator+( )
    }
    else
    {
        cout << "How the hell did I get here?\n";
        return;
    }
}

        // https://en.wikipedia.org/wiki/Collatz_conjecture
        int main()
        {
            BigInt MAX(INT_MAX);
            cout << "The largest integer is " << MAX << endl;
            cout << "Twice the largest integer is " << MAX + MAX << endl;
            BigInt start(INT_MAX); // BigInt constructor - use for submission
            // BigInt start(12); // BigInt constructor – use for testing
            bool printSteps = false;
            ThreeNp1 N = {start, 0, 0, 0, 0};   // initialize N with the desired start value
            findThreeNp1(start, N, printSteps); // print out the steps
            cout << endl;
            print(N);
            return 0;
        }
