#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform merge operation in merge sort
void merge(FILE* input_file, FILE* temp_file, long left, long middle, long right) {
    fseek(input_file, left, SEEK_SET);
    long i = left;
    long j = middle + 1;

    while (i <= middle && j <= right) {
        long num_i, num_j;
        fscanf(input_file, "%ld", &num_i);
        fseek(input_file, j, SEEK_SET);
        fscanf(input_file, "%ld", &num_j);

        if (num_i <= num_j) {
            fprintf(temp_file, "%ld\n", num_i);
            i++;
        } else {
            fprintf(temp_file, "%ld\n", num_j);
            j++;
        }
    }

    while (i <= middle) {
        long num_i;
        fscanf(input_file, "%ld", &num_i);
        fprintf(temp_file, "%ld\n", num_i);
        i++;
    }

    while (j <= right) {
        long num_j;
        fseek(input_file, j, SEEK_SET);
        fscanf(input_file, "%ld", &num_j);
        fprintf(temp_file, "%ld\n", num_j);
        j++;
    }

    fseek(temp_file, 0, SEEK_SET);
    i = left;
    while (!feof(temp_file)) {
        long num;
        fscanf(temp_file, "%ld", &num);
        fseek(input_file, i, SEEK_SET);
        fprintf(input_file, "%ld\n", num);
        i++;
    }
}

// Function to perform merge sort on data in a file
void mergeSortFile(FILE* input_file, FILE* temp_file, long left, long right) {
    if (left < right) {
        long middle = left + (right - left) / 2;
        mergeSortFile(input_file, temp_file, left, middle);
        mergeSortFile(input_file, temp_file, middle + 1, right);
        merge(input_file, temp_file, left, middle, right);
    }
}

// Function to perform binary search in a sorted file
long binarySearchFile(FILE* input_file, long left, long right, long key) {
    while (left <= right) {
        long middle = left + (right - left) / 2;
        fseek(input_file, middle, SEEK_SET);
        long num;
        fscanf(input_file, "%ld", &num);

        if (num == key) {
            return middle; // Key found
        } else if (num < key) {
            left = middle + 1; // Search the right half
        } else {
            right = middle - 1; // Search the left half
        }
    }
    return -1; // Key not found
}

int main() {
    srand(time(NULL));
    FILE* dataFile = fopen("data.txt", "w+");

    if (dataFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Generate and write random numbers to the file
    for (int i = 0; i < 100; i++) { // Generating 100 random numbers
        long num = rand() % 1000; // Assuming a range of 0 to 999
        fprintf(dataFile, "%ld\n", num);
    }

    // Sort the data in the file using merge sort
    FILE* tempFile = tmpfile();
    fseek(dataFile, 0, SEEK_SET);
    mergeSortFile(dataFile, tempFile, 0, 99);

    // Prompt the user for a key to search for
    long key;
    printf("Enter a number to search for: ");
    scanf("%ld", &key);

    // Perform binary search on the sorted data in the file
    long result = binarySearchFile(dataFile, 0, 99, key);

    if (result != -1) {
        printf("Element found at line %ld.\n", result + 1);
    } else {
        printf("Element not found in the file.\n");
    }

    fclose(dataFile);
    fclose(tempFile);

    return 0;
}












/*





To perform merge sort and binary search on data stored in a file in C without using arrays, you can read and write data directly to the file while sorting. Here's a program that generates random numbers, stores them in a file, sorts the numbers using merge sort without arrays, and performs a binary search based on user input:


In this program, we use temporary files for the merge operation in merge sort and perform binary search directly on the file without reading the data into arrays. Make sure to create a file named "data.txt" to store the random numbers before running the program.









rm * -fr 

vi search.c 


gcc search.c -o search


./search



watch ls -lath 





*/










