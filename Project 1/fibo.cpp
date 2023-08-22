#include <iostream>
using namespace std;

// Fibo function
int fibo(int n)
{
 if (n == 1 || n == 0)
    return 1;
 else
    return fibo(n-1) + fibo(n-2); // recursion
}
int main()
{
 for (int i = 1; i <= 20; i++)
    cout << i << ":" << fibo(i) << endl;
 return 0;
}