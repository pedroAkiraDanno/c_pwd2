#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>











#define MAX_RANDOM 11100000
#define MAX_SEED   10000000

int loops = 0; // Added loop counter to binarySearch()

// Function to generate random data and write it to a file
void generateAndWriteData(const char* filename, int size) {
    FILE* file = fopen(filename, "wb");             //"wb" − open for writing in binary mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++) {

        //int random = rand(); // Generate a random number between 0 and RAND_MAX
        //int random = rand() % 1000000; // Generate random number between 0 and 999999        1.000.000
        int random = rand() % MAX_SEED; // Generate random number between 0 and 9999999        10.000.000        
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




























void writeDataToFile(const char* filename, int* data, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", data[i]);
    }

    fclose(file);
}









bool isFileSorted(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    int prev, current;
    int first = 1;

    while (fscanf(file, "%d", &current) == 1) {
        if (!first && current < prev) {
            fclose(file);
            return false;
        }
        first = 0;
        prev = current;
    }

    fclose(file);
    return true;
}







int main() {

    // Seed the random number generator with the current time
    srand(time(NULL));


    const char* filename = "data.dat";
    int size = MAX_RANDOM; // Change this to the desired size of your data

    // Generate and write random data to the file
    generateAndWriteData(filename, size);

    // Read the data from the file
    int* data = readDataFromFile(filename, size);

    // Perform quicksort on the data
    quicksort(data, 0, size - 1);

    writeDataToFile("sorted_data.txt", data, size);


    if (isFileSorted("sorted_data.txt")) {
        printf("File is sorted.\n");
    } else {
        printf("File is not sorted.\n");
    }



    // Write the sorted data back to the file
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(data, sizeof(int), size, file);

    fclose(file);

    // Implement binary search on the sorted data
    int target = rand() % MAX_SEED ; // Change this to the value you want to search for
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

        if (result != -1) {
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
















