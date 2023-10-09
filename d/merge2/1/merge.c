#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function to merge two subarrays of arr[]
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

    // Merge the temporary arrays back into arr[]
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

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

int main() {
    // Create a file with random data (for demonstration)
    FILE* file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.");
        return 1;
    }

    // Generate and write random data to the file
    long n = 1000000;  // Number of elements in the file
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = rand() % 10000;  // Generate random numbers between 0 and 99
        fprintf(file, "%d\n", num);
    }

    fclose(file);

    // Read data from the file into an array
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.");
        return 1;
    }

    int data[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &data[i]);
    }

    fclose(file);

    // Perform merge sort on the data
    mergeSort(data, 0, n - 1);

    // Write the sorted data back to the file
    file = fopen("sorted_data.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", data[i]);
    }

    fclose(file);

    printf("Data has been sorted and saved to sorted_data.txt.\n");

    return 0;
}














/*



merge sort in file 
random data inside program 
with programing c 

ChatGPT
To perform a merge sort on data stored in a file in C programming, you can follow these steps:

Create a file with random data.
Read the data from the file into an array.
Implement the merge sort algorithm to sort the data.
Write the sorted data back to the file.




This program first creates a file "data.txt" with random data, reads the data into an array, performs a merge sort on the array, and then writes the sorted data back to a new file "sorted_data.txt". Make sure to compile and run this program in a C environment.










rm * -fr 

vi test.c 

gcc test.c -o test

./test










*/














