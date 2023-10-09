#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_MAX 

// Function to swap two long integers
void swap(long* a, long* b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array for quicksort
int partition(long arr[], int low, int high) {
    long pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to implement quicksort
void quicksort(long arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}












// Function to perform binary search
int binarySearch(long arr[], int left, int right, long target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Element not found
}













int main() {
    srand(time(NULL));
    int n = 1000000; // Change this value for the desired number of elements
    long data[n];

    // Generate random data and write it to a file
    FILE* file = fopen("random_data.txt", "w");
    for (int i = 0; i < n; i++) {
        data[i] = rand();
        fprintf(file, "%ld\n", data[i]);
    }
    fclose(file);

    // Read data from the file
    file = fopen("random_data.txt", "r");
    for (int i = 0; i < n; i++) {
        fscanf(file, "%ld", &data[i]);
    }
    fclose(file);

    // Perform quicksort
    quicksort(data, 0, n - 1);

    // Write the sorted data back to the file
    file = fopen("sorted_data.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%ld\n", data[i]);
    }
    fclose(file);

    // Perform binary search
    long target = data[rand() % n]; // Choose a random target value
    int result = binarySearch(data, 0, n - 1, target);

    if (result != -1) {
        printf("Target %ld found at index %d.\n", target, result);
    } else {
        printf("Target %ld not found.\n", target);
    }

    return 0;
}










/*

To perform quicksort on a file containing random data using C, and then conduct a binary search within the sorted file, you can follow these steps:

Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.





cd /root/c 

rm * -fr 

vi test.c 

gcc test.c -o test

./test













This program generates random long integers, sorts them using quicksort, writes the sorted data to a file, and then performs a binary search for a randomly chosen target value within the sorted data. You can adjust the n variable to control the number of elements in your data.








*/












