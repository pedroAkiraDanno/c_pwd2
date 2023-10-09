#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>





#define MAX_RANDOM 100000000
#define MAX_NAME_LENGTH 50









void generateRandomData(long* arr, long size) {
    for(long i = 0; i < size; i++) {
        arr[i] = rand() % 1000000; // Generate random numbers between 0 and 999999999
    }
}

void writeToFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "wb");
    fwrite(arr, sizeof(long), size, file);
    fclose(file);
}

void readFromFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "rb");
    fread(arr, sizeof(long), size, file);
    fclose(file);
}

void quicksort(long* arr, long left, long right) {
    if(left < right) {
        long pivot = arr[right];
        long i = left - 1;
        for(long j = left; j <= right - 1; j++) {
            if(arr[j] <= pivot) {
                i++;
                long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        long temp = arr[i+1];
        arr[i+1] = arr[right];
        arr[right] = temp;

        long partition = i + 1;

        quicksort(arr, left, partition - 1);
        quicksort(arr, partition + 1, right);
    }
}

long binarySearch(long* arr, long size, long target) {
    long left = 0;
    long right = size - 1;
    while(left <= right) {
        long mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            return mid;
        }
        if(arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    long size = MAX_RANDOM; // Define your desired size
    long* data = (long*)malloc(size * sizeof(long));

    generateRandomData(data, size);
    writeToFile(data, size, "data.bin");

    readFromFile(data, size, "data.bin");

    quicksort(data, 0, size - 1);
    writeToFile(data, size, "sorted_data.bin");

    long target = 100000; // Define your desired target for binary search
    long result = binarySearch(data, size, target);

    if(result != -1) {
        printf("Element %ld found at index %ld\n", target, result);
    } else {
        printf("Element %ld not found\n", target);
    }






    long number = 0;
    int searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);

         long result =binarySearch(data, size, number);

        if(result != -1) {
            printf("Element %ld found at index %ld\n", number, result);
        } else {
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%d", &searchAgain);
    }








    free(data);

    return 0;
}











/*





programing in c in file in linux:
Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
use maloc in array to large size of data 
use long variable 




ChatGPT
Certainly! Here is the modified C program that uses malloc with long variables for a large size of data:



This program now uses long variables and malloc for dynamic memory allocation to handle a larger size of data. It also generates random long numbers, performs quicksort, and implements binary search as per your requirements.
















*/






















