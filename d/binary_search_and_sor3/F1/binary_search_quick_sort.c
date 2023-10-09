#include <stdio.h>
#include <stdlib.h>
#include <time.h>




#define MAX_RANDOM 10000









void swap(FILE *file, long int a, long int b) {
    fseek(file, a * sizeof(int), SEEK_SET);
    int tempA, tempB;
    fread(&tempA, sizeof(int), 1, file);
    fread(&tempB, sizeof(int), 1, file);

    fseek(file, a * sizeof(int), SEEK_SET);
    fwrite(&tempB, sizeof(int), 1, file);
    fseek(file, b * sizeof(int), SEEK_SET);
    fwrite(&tempA, sizeof(int), 1, file);
}

long int partition(FILE *file, long int low, long int high) {
    fseek(file, high * sizeof(int), SEEK_SET);
    int pivot;
    fread(&pivot, sizeof(int), 1, file);

    long int i = low - 1;

    for (long int j = low; j < high; j++) {
        fseek(file, j * sizeof(int), SEEK_SET);
        int current;
        fread(&current, sizeof(int), 1, file);

        if (current < pivot) {
            i++;
            swap(file, i, j);
        }
    }

    swap(file, i + 1, high);
    return i + 1;
}

void quickSort(FILE *file, long int low, long int high) {
    if (low < high) {
        long int pi = partition(file, low, high);

        quickSort(file, low, pi - 1);
        quickSort(file, pi + 1, high);
    }
}

int binarySearch(FILE *file, int target, long int low, long int high) {
    while (low <= high) {
        long int mid = low + (high - low) / 2;

        fseek(file, mid * sizeof(int), SEEK_SET);
        int current;
        fread(&current, sizeof(int), 1, file);

        if (current == target)
            return mid;

        if (current < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main() {
    // Generate random data and write it to a file
    FILE *file = fopen("random_data.txt", "w");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    srand(time(NULL)); // Seed for random numbers

    for (int i = 0; i < MAX_RANDOM; i++) {
        fprintf(file, "%d\n", rand() % 10000); // Generate random numbers between 0 and 9999
    }

    fclose(file);

    // Quick sort the data in the file
    file = fopen("random_data.txt", "r+");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long int numElements = ftell(file) / sizeof(int);
    fseek(file, 0, SEEK_SET);

    quickSort(file, 0, numElements - 1);

    // Binary search
    int target = 536; // The number you're searching for
    int index = binarySearch(file, target, 0, numElements - 1);

    if (index != -1)
        printf("Found %d at index %d\n", target, index);
    else
        printf("Element %d not found\n", target);

    fclose(file);
    return 0;
}















