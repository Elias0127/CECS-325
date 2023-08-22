#include <iostream>
#include <fstream>
#include <pthread.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

const int NUM_THREADS = 8;
const int NUM_NUMBERS = 1000000;
const int SECTION_SIZE = NUM_NUMBERS / NUM_THREADS;

struct SortParams
{
    int *array;
    int start;
    int end;
};

void bubble_sort(int *array, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        for (int j = start; j < end - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void *sort_section(void *params)
{
    SortParams *sort_params = (SortParams *)params;
    bubble_sort(sort_params->array, sort_params->start, sort_params->end);
    return NULL;
}

void merge(int *array, int start, int mid, int end)
{
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int left[left_size], right[right_size];

    memcpy(left, &array[start], left_size * sizeof(int));
    memcpy(right, &array[mid + 1], right_size * sizeof(int));

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

    while (i < left_size)
    {
        array[k++] = left[i++];
    }

    while (j < right_size)
    {
        array[k++] = right[j++];
    }
}

int main()
{
    int numbers[NUM_NUMBERS];

    ifstream input("numbers.dat");
    for (int i = 0; i < NUM_NUMBERS; ++i)
    {
        input >> numbers[i];
    }
    input.close();

    pthread_t threads[NUM_THREADS];
    SortParams sort_params[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        sort_params[i] = {numbers, i * SECTION_SIZE, (i + 1) * SECTION_SIZE - 1};
        pthread_create(&threads[i], NULL, sort_section, (void *)&sort_params[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    for (int step = SECTION_SIZE; step < NUM_NUMBERS; step *= 2)
    {
        for (int i = 0; i < NUM_NUMBERS; i += 2 * step)
        {
            int mid = i + step - 1;
            int end = min(i + 2 * step - 1, NUM_NUMBERS - 1);
            merge(numbers, i, mid, end);
        }
    }

    ofstream output("sorted_numbers.dat");
    for (int i = 0; i < NUM_NUMBERS; ++i)
    {
        output << numbers[i] << endl;
    }
    output.close();

    return 0;
}
