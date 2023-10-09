#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


#define MAX_RANDOM 400000000            // 3GB, the limit is the memory in your computer 
#define MAX_SEED   900000
                   





void generateRandomData(long* arr, long size) {
    for(long i = 0; i < size; i++) {
        arr[i] = rand() % MAX_SEED;
                          
    }
}

void writeToFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(arr, sizeof(long), size, file);
    fclose(file);
}

void readFromFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
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
    long size = MAX_RANDOM;
    long* data = (long*)malloc(size * sizeof(long));
    if (data == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    generateRandomData(data, size);
    writeToFile(data, size, "data.bin");

    readFromFile(data, size, "data.bin");

    quicksort(data, 0, size - 1);
    writeToFile(data, size, "sorted_data.bin");

    long target = 420000;
    long result = binarySearch(data, size, target);

    if(result != -1) {
        printf("Element %ld found at index %ld\n", target, result);
    } else {
        printf("Element %ld not found\n", target);
    }
























    free(data);

    return 0;
}







/*








I understand your concern. To avoid potential segmentation faults when working with a large amount of data, it's important to be mindful of memory allocation and deallocation. Additionally, using dynamic memory allocation functions like malloc and ensuring proper error handling is crucial.

Here is a revised version of the C program, with added error handling for memory allocation and file operations:






In this revised version, I've added error handling for memory allocation and file operations. This should help in avoiding segmentation faults, especially when working with large amounts of data.





















mkdir /root/c

cd /root/c 










rm * -rf 

vi test.c

gcc test.c -o test

./test














*/

























