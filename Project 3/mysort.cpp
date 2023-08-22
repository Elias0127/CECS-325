//  Elias Woldie
//  CECS 325 Sec02

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_SIZE = 1000000;

// Function to perform bubble sort
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // Check if correct number of arguments were passed
    if (argc < 3)
    {
        cout << "Please enter 2 parameters: \n";
        cout << "   Parameter 1: input file name. \n";
        cout << "   Parameter 2: output file name. \n";
        cout << "Example: mysort numbers.dat sorted_numbers.dat \n";
        exit(EXIT_SUCCESS);
    }

    // Open the input file specified in the command line argument
    ifstream numfile;
    numfile.open(argv[1]);

    // Check if file opening was successful
    if (!numfile)
    {
        cout << "Error opening input file.\n";
        exit(EXIT_FAILURE);
    }

    // Read the numbers from the input file into an array
    int arr[MAX_SIZE];
    int n = 0;
    int temp;
    while (numfile >> temp && n <= MAX_SIZE)
    {
        arr[n] = temp;
        n++;
    }

    // Close the input file
    numfile.close();

    // Sort the array using bubble sort
    bubbleSort(arr, n);

    // Open the output file specified in the command line argument
    ofstream fout;
    fout.open(argv[2]);

    // Check if file opening was successful
    if (!fout)
    {
        cout << "Error opening output file.\n";
        exit(EXIT_FAILURE);
    }

    // Write the sorted numbers to the output file
    for (int i = 0; i < n; i++)
    {
        fout << arr[i] << endl;
    }

    // Close the output file
    fout.close();

    // Return success
    return 0;
}
