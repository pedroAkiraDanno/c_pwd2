#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "large_data.txt"
#define NUM_ELEMENTS 1000 // Adjust the number of elements as needed








// Function to perform binary search in the file
int binarySearch(FILE *file, int key) {
    int low = 0, high = -1, mid, value;
    fseek(file, 0, SEEK_END);
    high = (ftell(file) / sizeof(int)) - 1;
    fseek(file, 0, SEEK_SET);

    while (low <= high) {
        mid = low + (high - low) / 2;
        fseek(file, mid * sizeof(int), SEEK_SET);
        fread(&value, sizeof(int), 1, file);

        if (value == key) {
            return mid; // Key found
        } else if (value < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Key not found
}

// Function to perform quicksort in the file
void quicksort(FILE *file, int low, int high) {
    if (low < high) {
        int pivot, temp, i = low - 1;

        fseek(file, high * sizeof(int), SEEK_SET);
        fread(&pivot, sizeof(int), 1, file);

        for (int j = low; j <= high - 1; j++) {
            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&temp, sizeof(int), 1, file);

            if (temp < pivot) {
                i++;
                fseek(file, i * sizeof(int), SEEK_SET);
                fwrite(&temp, sizeof(int), 1, file);

                fseek(file, j * sizeof(int), SEEK_SET);
                fwrite(&pivot, sizeof(int), 1, file);
            }
        }

        fseek(file, (i + 1) * sizeof(int), SEEK_SET);
        fwrite(&pivot, sizeof(int), 1, file);

        int pi = i + 1;

        // Recursively sort elements before and after partition
        quicksort(file, low, pi - 1);
        quicksort(file, pi + 1, high);
    }
}

int main() {
    FILE *file;
    int key, position;

    // Generate a random data file
    srand(time(NULL));
    file = fopen(FILENAME, "w");
    if (!file) {
        perror("File open error");
        return 1;
    }

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        int randomValue = rand() % 100; // Adjust the range as needed
        fprintf(file, "%d\n", randomValue);
    }

    fclose(file);

    // Open the file for sorting and sorting
    file = fopen(FILENAME, "rb+");
    if (!file) {
        perror("File open error");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    int numElements = ftell(file) / sizeof(int);
    fseek(file, 0, SEEK_SET);

    quicksort(file, 0, numElements - 1);

    // Reopen the file for binary search
    fclose(file);
    file = fopen(FILENAME, "rb");
    if (!file) {
        perror("File open error");
        return 1;
    }

    printf("Enter the key to search: ");
    scanf("%d", &key);

    // Perform binary search on the sorted data in the file
    position = binarySearch(file, key);

    if (position != -1) {
        printf("Key %d found at position %d.\n", key, position);
    } else {
        printf("Key %d not found in the file.\n", key);
    }

    fclose(file);

    return 0;
}

























/*


rm * -fr


vi quick_sort_and_binary_search_large_file.c 


gcc quick_sort_and_binary_search_large_file.c -o quick_sort_and_binary_search_large_file

./quick_sort_and_binary_search_large_file



*/
















