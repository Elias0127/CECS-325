//  Elias Woldie
//  Class (CECS 325-02)
//  05/03/2023
//  I certify that this program is my own original work. I did not copy any part of this program from
//  any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
using namespace std;

class BigInt
{
private:
    vector<char> v; // notice this is a vector of char… not int!!!
public:
    BigInt();                 // default constructor – set value to 0
    BigInt(int);              // int constructor
    BigInt(string);           // string constructor
    BigInt operator+(BigInt); // add 2 BigInts, return the sum
    BigInt operator++();      // prefix increment
    BigInt operator++(int);   // postfix increment
    BigInt operator*(BigInt); // multiply operator
    // BigInt operator /(BigInt); // divide operator – optional.
    // Not needed if half( ) is used.
    BigInt half();                                         // return half the value
    bool isOdd();                                          // true if the number is odd
    bool isEven();                                         // true if the number is even
    bool operator==(BigInt);                               // true if 2 BigInts are equal
    bool operator<(const BigInt &);                        // less than operator
    friend ostream &operator<<(ostream &, const BigInt &); // cout << BigInt
};

// Default constructor, sets value to 0
BigInt::BigInt()
{
    v.push_back('0');
}
// Integer constructor, initializes the BigInt object with an integer value
BigInt::BigInt(int num)
{
    while (num)
    {
        v.push_back(num % 10 + '0');
        num /= 10;
    }
    reverse(v.begin(), v.end());
}
// String constructor, initializes the BigInt object with a string value
BigInt::BigInt(string num)
{
    for (const char &c : num)
    {
        v.push_back(c);
    }
}
// Overloading the addition operator to add two BigInt objects
BigInt BigInt::operator+(BigInt other)
{
    string result = "";
    int carry = 0;
    int len1 = v.size();
    int len2 = other.v.size();
    int diff = abs(len1 - len2);
    if (len1 < len2)
    {
        for (int i = 0; i < diff; i++)
        {
            v.insert(v.begin(), '0');
        }
    }
    else
    {
        for (int i = 0; i < diff; i++)
        {
            other.v.insert(other.v.begin(), '0');
        }
    }
    for (int i = v.size() - 1; i >= 0; i--)
    {
        int temp = (v[i] - '0') + (other.v[i] - '0') + carry;
        carry = temp / 10;
        temp %= 10;
        result = (char)(temp + '0') + result;
    }
    if (carry)
    {
        result = (char)(carry + '0') + result;
    }
    return BigInt(result);
}
// Overloading the pre-increment operator for BigInt objects
BigInt BigInt::operator++()
{
    *this = *this + BigInt(1);
    return *this;
}
// Overloading the post-increment operator for BigInt objects
BigInt BigInt::operator++(int)
{
    BigInt temp = *this;
    *this = *this + BigInt(1);
    return temp;
}
// Overloading the multiplication operator to multiply two BigInt objects
BigInt BigInt::operator*(BigInt other)
{
    int len1 = v.size();
    int len2 = other.v.size();
    BigInt result("0");

    for (int i = len1 - 1; i >= 0; i--)
    {
        string tempStr(len1 - 1 - i, '0');
        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--)
        {
            int temp = (v[i] - '0') * (other.v[j] - '0') + carry;
            carry = temp / 10;
            temp %= 10;
            tempStr = (char)(temp + '0') + tempStr;
        }
        if (carry)
        {
            tempStr = (char)(carry + '0') + tempStr;
        }
        result = result + BigInt(tempStr);
    }
    return result;
}
// Function to return half the value of the current BigInt object
BigInt BigInt::half()
{
    string result = "";
    int temp = 0;
    int idx = 0;
    while (idx < v.size())
    {
        temp = temp * 10 + (v[idx] - '0');
        int quotient = temp / 2;
        if (quotient > 0 || !result.empty())
        {
            result += quotient + '0';
        }
        temp %= 2;
        idx++;
    }
    return BigInt(result);
}
// Function to check if the current BigInt object is odd
bool BigInt::isOdd()
{
    return (v.back() - '0') % 2 != 0;
}
// Function to check if the current BigInt object is even
bool BigInt::isEven()
{
    return !isOdd();
}
// Overloading the equality operator to check if two BigInt objects are equal
bool BigInt::operator==(BigInt other)
{
    return v == other.v;
}
// Overloading the less than operator to compare two BigInt objects
bool BigInt::operator<(const BigInt &other)
{
    if (v.size() != other.v.size())
    {
        return v.size() < other.v.size();
    }
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (v[i] != other.v[i])
        {
            return v[i] < other.v[i];
        }
    }
    return false;
}
// Overloading the stream insertion operator to output BigInt objects
ostream &operator<<(ostream &os, const BigInt &num)
{
    if (num.v.size() <= 8)
    {
        for (const char &c : num.v)
        {
            os << c;
        }
    }
    else
    {
        os << num.v[0] << '.';
        for (size_t i = 1; i < 8; ++i)
        {
            os << num.v[i];
        }
        os << 'e' << num.v.size() - 1;
    }
    return os;
}

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
        BigInt tempN(n);                                              // BigInt constructor
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
