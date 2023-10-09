#include <stdio.h>
#include <stdlib.h>

// Function to perform merge operation in merge sort
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort on an array
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

// Function to perform binary search in a sorted array
int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int middle = left + (right - left) / 2;

        // Check if the key is present at the middle
        if (arr[middle] == key)
            return middle;

        // If the key is greater, ignore the left half
        if (arr[middle] < key)
            left = middle + 1;
        // If the key is smaller, ignore the right half
        else
            right = middle - 1;
    }

    // Key not found in the array
    return -1;
}

int main() {
    FILE *file;
    int arr[100]; // Assuming a maximum of 100 elements
    int n, key;

    // Open the file for reading
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read data from the file into the array
    n = 0;
    while (fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }

    fclose(file);

    // Sort the array using merge sort
    mergeSort(arr, 0, n - 1);

    // Open the file for writing the sorted data
    file = fopen("sorted_data.txt", "w");
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    // Write the sorted data to the file
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);

    // Prompt user for a key to search for
    printf("Enter a number to search for: ");
    scanf("%d", &key);

    // Perform binary search on the sorted array
    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1) {
        printf("Element found at index %d.\n", result);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}










