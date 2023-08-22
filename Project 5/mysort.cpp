//  Elias Woldie
//  Class (CECS 325-02)
//  04/06/2023
//  I certify that this program is my own original work. I did not copy any part of this program from
//  any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <thread>

using namespace std;

const int NUM_THREADS = 8;
const int NUM_NUMBERS = 1000000;
const int SECTION_SIZE = 125000;

// Sort the subarray using Quick Sort
void quick_sort(int *array, int start, int end)
{
    if (start < end)
    {
        int pivot = array[end];
        int i = start - 1;

        for (int j = start; j <= end - 1; ++j)
        {
            if (array[j] <= pivot)
            {
                i++;
                swap(array[i], array[j]);
            }
        }
        swap(array[i + 1], array[end]);
        int partition_index = i + 1;

        quick_sort(array, start, partition_index - 1);
        quick_sort(array, partition_index + 1, end);
    }
}
// Pass the subarray to the bubble sort
void sort_section(int *array, int start, int end)
{
    quick_sort(array, start, end);
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
    if (argc < 2)
    {
        cout << "Please enter 1 parameters: \n";
        cout << "   Parameter 1: input file name. \n";
        cout << "Example: mysort numbers.dat \n";
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

    // Create and initialize threads
    thread threads[NUM_THREADS];

    // Divide the array into sections and create threads to sort each section
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = i * SECTION_SIZE;
        int end = (i + 1) * SECTION_SIZE - 1;
        threads[i] = thread(sort_section, numbers, start, end);
    }

    // Wait for all threads to finish sorting their respective sections
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads[i].join();
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

    // Output the sorted numbers to stdout
    for (int i = 0; i < NUM_NUMBERS; ++i)
    {
        cout << numbers[i] << endl;
    }

    return 0;
}
