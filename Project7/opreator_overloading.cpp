#include <iostream>  // header file for input/output operations
#include <vector>    // header file for vectors
using namespace std; // using the standard namespace

class BigInt // define a class BigInt
{
private:
    vector<char> v; // a vector to store digits of the number

public:
    BigInt(int n) // constructor to initialize the number
    {
        char digit;
        while (n > 9) // while there are more than 1 digit
        {
            digit = n % 10;     // get the rightmost digit
            n /= 10;            // remove the rightmost digit
            v.push_back(digit); // add the rightmost digit to the vector
        }
        digit = n;          // add the last remaining digit
        v.push_back(digit); // to the vector
    }

    friend ostream &operator<<(ostream &out, const BigInt &n) // overload the << operator
    {
        for (int i = 0; i < n.v.size(); i++) // loop through the vector
            cout << (int)n.v[i];             // and output each digit as an integer
        return out;                          // return the output stream
    }
};

int main() // main function
{
    BigInt B1(12345678); // create a BigInt object initialized with an integer
    cout << B1 << endl;  // output the BigInt object using the overloaded << operator
    return 0;            // return 0 to indicate successful execution
}
