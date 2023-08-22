#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <vector>
#include <string>
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
#endif