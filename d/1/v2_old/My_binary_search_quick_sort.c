#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>




#define MAX_RANDOM 21100000           //about 4GB the limit is the memory you have in your computer 
//#define MAX_RANDOM 1110000000           //about 4GB the limit is the memory you have in your computer 
#define MAX_SEED 1000000


 int loops = 0; // Added loop counter    to binaryseach()






// Function to generate random data and write it to a file
void generateAndWriteData(const char* filename, int size) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        int random = rand() % MAX_SEED; // Generate a random number between 0 and 9999
        fwrite(&random, sizeof(int), 1, file);
    }

    fclose(file);
}




// Function to read data from the file
int* readDataFromFile(const char* filename, int size) {
    int* data = (int*)malloc(size * sizeof(int));
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fread(data, sizeof(int), size, file);

    fclose(file);
    return data;
}




// Function to perform quicksort
void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int pivotIndex = i + 1;

        quicksort(arr, left, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, right);
    }
}




// Function to implement binary search
/*
int binarySearch(int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;

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
*/




// Function to implement binary search
int binarySearch(int* arr, int size, int target) {




    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;

        loops++; // Increment loop counter

    }

    return -1; // Element not found
}





















int main() {
    const char* filename = "data.dat";
    int size = MAX_RANDOM; // Change this to the desired size of your data

    // Generate and write random data to the file
    generateAndWriteData(filename, size);

    // Read the data from the file
    int* data = readDataFromFile(filename, size);

    // Perform quicksort on the data
    quicksort(data, 0, size - 1);

    // Write the sorted data back to the file
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(data, sizeof(int), size, file);

    fclose(file);

    // Implement binary search on the sorted data
    int target = 42; // Change this to the value you want to search for
    int result = binarySearch(data, size, target);

    if (result != -1) {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d not found\n", target);
    }




    // Implement binary search on the sorted data with while 
    long number = 0;
    long searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);

         long result = binarySearch(data, size, number);

        if(result != -1) {
            printf("Total loops in this search: %d\n", loops); // Print loop count            
            printf("Element %ld found at index %ld\n", number, result);

        } else {
            printf("Total loops in this search: %d\n", loops); // Print loop count            
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%ld", &searchAgain);
    }





    // Free allocated memory
    free(data);

    return 0;
}









/*




programing in c in linux in file 
Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
use malloc 

ChatGPT
Sure! I can help you with that. Below is a C program that does what you described:










This program generates random data, writes it to a file, reads it back, performs quicksort, writes the sorted data back to the file, and then implements a binary search on the sorted data. It uses malloc to dynamically allocate memory for the array.

Please make sure to compile this program with a C compiler, and you may need to link the math library using -lm depending on your compiler and platform. For example, you can compile it using gcc:







*/





