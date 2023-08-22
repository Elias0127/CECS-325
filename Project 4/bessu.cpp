#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int MAX_SIZE = 1000000;
const int SECTION = 125000;

struct Struct_Arr
{
    int *array;
    int size;
};

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

void merge_arrays(int arr[], int left[], int left_size, int right[], int right_size)
{
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void *sorter(void *ptr)
{
    Struct_Arr *numbers = (Struct_Arr *)ptr;
    bubbleSort(numbers->array, numbers->size);

    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        cout << "   Parameter 1: input file. \n";
        cout << "   Parameter 2: outputfile. \n";
        cout << "Example: §mysort numbers.dat sortout.txt \n";
        exit(EXIT_SUCCESS);
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    if (!inputFile)
    {
        cout << "Unable to open input file.";
        exit(EXIT_FAILURE);
    }

    int arr[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        inputFile >> arr[i];
    }

    inputFile.close();

    Struct_Arr argList[8];

    for (int i = 0; i < 8; i++)
    {
        argList[i].array = arr + (i * SECTION);
        argList[i].size = SECTION;
    }

    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7;

    int iret0 = pthread_create(&thread0, NULL, sorter, (void *)&argList[0]);
    int iret1 = pthread_create(&thread1, NULL, sorter, (void *)&argList[1]);
    int iret2 = pthread_create(&thread2, NULL, sorter, (void *)&argList[2]);
    int iret3 = pthread_create(&thread3, NULL, sorter, (void *)&argList[3]);
    int iret4 = pthread_create(&thread4, NULL, sorter, (void *)&argList[4]);
    int iret5 = pthread_create(&thread5, NULL, sorter, (void *)&argList[5]);
    int iret6 = pthread_create(&thread6, NULL, sorter, (void *)&argList[6]);
    int iret7 = pthread_create(&thread7, NULL, sorter, (void *)&argList[7]);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);

    int merge_size = SECTION;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8 / (2 * (i + 1)); j++)
        {
            int left_start = 2 * j * merge_size;
            int right_start = (2 * j + 1) * merge_size;
            int *left = arr + left_start;
            int *right = arr + right_start;
            merge_arrays(arr + left_start, left, merge_size, right, merge_size);
        }
        merge_size *= 2;
    }

    ofstream outputFile;
    outputFile.open(argv[2]);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        outputFile << arr[i] << endl;
    }
    outputFile.close();

    return 0;
}
