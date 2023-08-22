#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "   Parameter 1: total count of numbers you want. \n";
        cout << "   Parameter 2: min value. \n";
        cout << "   Parameter 3: max value. \n";
        cout << "Example: §generate 10000000 100000 999999 \n";
        exit(EXIT_SUCCESS);
    }

    int COUNT = stoi(argv[1]);
    int MIN = stoi(argv[2]);
    int MAX = stoi(argv[3]);

    ofstream fout;
    fout.open("numbers.dat", ios::out | ios::trunc);

    srand(time(nullptr));

    for (int i = 0; i < COUNT; i++)
    {
        int randNums = (rand() % (MAX - MIN + 1) + MIN);
        fout << randNums << endl;
    }

    fout.close();
    return 0;
}
