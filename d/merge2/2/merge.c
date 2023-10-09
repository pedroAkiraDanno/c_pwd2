#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to merge two segments in a file
void merge(FILE* input, FILE* output, long left, long middle, long right) {
    fseek(input, left * sizeof(int), SEEK_SET);
    fseek(output, left * sizeof(int), SEEK_SET);

    long i = left;
    long j = middle + 1;

    while (i <= middle && j <= right) {
        int num1, num2;

        fread(&num1, sizeof(int), 1, input);
        fread(&num2, sizeof(int), 1, input);

        if (num1 <= num2) {
            fwrite(&num1, sizeof(int), 1, output);
            i++;
        } else {
            fwrite(&num2, sizeof(int), 1, output);
            j++;
        }
    }

    while (i <= middle) {
        int num;
        fread(&num, sizeof(int), 1, input);
        fwrite(&num, sizeof(int), 1, output);
        i++;
    }

    while (j <= right) {
        int num;
        fread(&num, sizeof(int), 1, input);
        fwrite(&num, sizeof(int), 1, output);
        j++;
    }

    fseek(output, left * sizeof(int), SEEK_SET);

    for (long k = left; k <= right; k++) {
        int num;
        fread(&num, sizeof(int), 1, output);
        fseek(input, k * sizeof(int), SEEK_SET);
        fwrite(&num, sizeof(int), 1, input);
    }
}

// Merge sort function
void mergeSort(FILE* input, FILE* output, long left, long right) {
    if (left < right) {
        long middle = left + (right - left) / 2;

        mergeSort(input, output, left, middle);
        mergeSort(input, output, middle + 1, right);

        merge(input, output, left, middle, right);
    }
}

int main() {
    srand(time(NULL));

    // Create a file with random data
    FILE* inputFile = fopen("input_data.txt", "wb+");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    int numElements = 10;  // Number of elements in the file

    for (int i = 0; i < numElements; i++) {
        int num = rand() % 100;  // Generate random numbers between 0 and 99
        fwrite(&num, sizeof(int), 1, inputFile);
    }

    fclose(inputFile);

    // Open the input and output files
    inputFile = fopen("input_data.txt", "rb+");
    FILE* outputFile = fopen("sorted_data.txt", "wb+");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Perform merge sort on the data
    mergeSort(inputFile, outputFile, 0, numElements - 1);

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    printf("Data has been sorted and saved to sorted_data.txt.\n");

    return 0;
}














/*

merge sort in file 
random data inside program 
data file, and sorted file
no use array
generete random data 
with programing c 

ChatGPT
To generate random data and perform a merge sort on it without using arrays in C, you can create two separate files: one for the unsorted data and another for the sorted data. Here's a complete program that demonstrates this:

c


This program generates random data, writes it to "input_data.txt," sorts the data in-place, and saves the sorted data to "sorted_data.txt" without using arrays.











cd /root/c

rm * -fr 

vi test.c 

gcc test.c -o test

./test









*/








