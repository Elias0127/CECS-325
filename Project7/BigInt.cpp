#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
#include "BigInt.h"

using namespace std;

BigInt::BigInt()
{
    v.push_back('0');
}

BigInt::BigInt(int num)
{
    while (num)
    {
        v.push_back(num % 10 + '0');
        num /= 10;
    }
    reverse(v.begin(), v.end());
}

BigInt::BigInt(string num)
{
    for (const char &c : num)
    {
        v.push_back(c);
    }
}

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

BigInt BigInt::operator++()
{
    *this = *this + BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int)
{
    BigInt temp = *this;
    *this = *this + BigInt(1);
    return temp;
}

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

bool BigInt::isOdd()
{
    return (v.back() - '0') % 2 != 0;
}

bool BigInt::isEven()
{
    return !isOdd();
}

bool BigInt::operator==(BigInt other)
{
    return v == other.v;
}
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
