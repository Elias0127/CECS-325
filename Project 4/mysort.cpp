//  Elias Woldie
//  CECS 325 Sec02

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>
#include <cstring>

using namespace std;

const int NUM_THREADS = 8;
const int NUM_NUMBERS = 1000000;
const int SECTION_SIZE = 125000;

// Paramaters for sort function
struct ArgVals
{
    int *array;
    int start;
    int end;
};
// Sort the subarray using Bubble Sort
void bubble_sort(int *array, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        for (int j = start; j < end - i + start; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}
// Pass the subarray to the bubble sort
void *sort_section(void *params)
{
    ArgVals *sort_params = (ArgVals *)params;
    bubble_sort(sort_params->array, sort_params->start, sort_params->end);
    return NULL;
}

void merge(int *array, int start, int mid, int end)
{
    // Calculates the sizes of the left (first) and right (second) subarrays
    int left_size = mid - start + 1;
    int right_size = end - mid;

    // Checks if the left and right subarrays have valid sizes, and returns if either has a size of 0 or less
    if (left_size <= 0 || right_size <= 0)
    {
        return;
    }

    int left[left_size], right[right_size];

    // Copy elements from the original array to the left subarray
    for (int i = 0; i < left_size; i++)
    {
        left[i] = array[start + i];
    }

    // Copy elements from the original array to the right subarray
    for (int i = 0; i < right_size; i++)
    {
        right[i] = array[mid + 1 + i];
    }

    // Merges the left and right subarrays back into the original array by comparing their elements and inserting the smallest element first
    int i = 0, j = 0, k = start;
    while (i < left_size && j < right_size)
    {
        if (left[i] <= right[j])
        {
            array[k++] = left[i++];
        }
        else
        {
            array[k++] = right[j++];
        }
    }
    // If there are any remaining elements in the left subarray after the merging process, they are copied back into the priginal array
    while (i < left_size)
    {
        array[k++] = left[i++];
    }
    // If there are any remaining elements in the right subarray after the merging process, they are copied back into the original array:
    while (j < right_size)
    {
        array[k++] = right[j++];
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

    // Open the input file from command line argument
    ifstream input(argv[1]);

    // Check if file opening was successful
    if (!input)
    {
        cout << "Error opening input file.\n";
        exit(EXIT_FAILURE);
    }

    // Read numbers from the input file into an array
    int numbers[NUM_NUMBERS];
    for (int i = 0; i < NUM_NUMBERS; ++i)
    {
        input >> numbers[i];
    }
    input.close();

    // Create and initialize pthreads and SortParams structures
    pthread_t threads[NUM_THREADS];
    ArgVals sort_params[NUM_THREADS];

    // Divide the array into sections and create threads to sort each section
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        sort_params[i].array = numbers;
        sort_params[i].start = i * SECTION_SIZE;
        sort_params[i].end = (i + 1) * SECTION_SIZE - 1;
        pthread_create(&threads[i], NULL, sort_section, (void *)&sort_params[i]);
    }

    // Wait for all threads to finish sorting their respective sections
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Merge sorted sections into a single sorted array
    for (int step = SECTION_SIZE; step < NUM_NUMBERS; step *= 2)
    {
        for (int i = 0; i < NUM_NUMBERS; i += 2 * step)
        {
            int mid = i + step - 1;
            int end = min(i + 2 * step - 1, NUM_NUMBERS - 1);
            merge(numbers, i, mid, end);
        }
    }

    ofstream output(argv[2]);

    // Write the sorted numbers to the output file
    for (int i = 0; i < NUM_NUMBERS; ++i)
    {
        output << numbers[i] << endl;
    }
    output.close();

    return 0;
}
