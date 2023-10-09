#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>




#define SEED_RANDOM 1000
#define MAX_DATA    10000





void generateRandomData(const char* filename, long size) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < size; i++) {
        long randomNum = rand() % SEED_RANDOM;
        fwrite(&randomNum, sizeof(long), 1, file);
    }

    fclose(file);
}

void quicksortFile(const char* filename, long left, long right) {
    if (left < right) {
        long pivot, i, j;
        FILE* file = fopen(filename, "rb+");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        pivot = left;
        i = left;
        j = right;

        while (i < j) {
            long x, y;

            fseek(file, i * sizeof(long), SEEK_SET);
            fread(&x, sizeof(long), 1, file);

            fseek(file, j * sizeof(long), SEEK_SET);
            fread(&y, sizeof(long), 1, file);

            while (x <= pivot && i < right) {
                i++;
                fseek(file, i * sizeof(long), SEEK_SET);
                fread(&x, sizeof(long), 1, file);
            }

            while (y > pivot) {
                j--;
                fseek(file, j * sizeof(long), SEEK_SET);
                fread(&y, sizeof(long), 1, file);
            }

            if (i < j) {
                fseek(file, i * sizeof(long), SEEK_SET);
                fwrite(&y, sizeof(long), 1, file);

                fseek(file, j * sizeof(long), SEEK_SET);
                fwrite(&x, sizeof(long), 1, file);
            }
        }

        pivot = j;

        fseek(file, left * sizeof(long), SEEK_SET);
        fread(&i, sizeof(long), 1, file);

        fseek(file, pivot * sizeof(long), SEEK_SET);
        fread(&j, sizeof(long), 1, file);

        fseek(file, left * sizeof(long), SEEK_SET);
        fwrite(&j, sizeof(long), 1, file);

        fseek(file, pivot * sizeof(long), SEEK_SET);
        fwrite(&i, sizeof(long), 1, file);

        fclose(file);

        quicksortFile(filename, left, pivot - 1);
        quicksortFile(filename, pivot + 1, right);
    }
}

bool binarySearchFile(const char* filename, long target) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    long left = 0;
    fseek(file, 0, SEEK_END);
    long right = ftell(file) / sizeof(long) - 1;

    while (left <= right) {
        long mid = (left + right) / 2;
        long midVal;

        fseek(file, mid * sizeof(long), SEEK_SET);
        fread(&midVal, sizeof(long), 1, file);

        if (midVal == target) {
            fclose(file);
            return true;
        } else if (midVal < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    fclose(file);
    return false;
}











void printDefault(int parameter) {
    switch (parameter) {
        case 1:
            printf("Generating data...\n");
            break;
        case 2:
            printf("Sorting...\n");
            break;
        case 3:
            printf("Read to file...\n");
            break;            
        case 4:
            printf("Searching...\n");
            break;

        default:
            printf("Invalid parameter!\n");
    }
}












bool isFileSorted(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    long prev, current;
    fseek(file, 0, SEEK_SET);
    fread(&prev, sizeof(long), 1, file);

    while (fread(&current, sizeof(long), 1, file) == 1) {
        if (current < prev) {
            fclose(file);
            return false;
        }
        prev = current;
    }

    fclose(file);
    return true;
}







int main() {
    srand(time(NULL));

    const char* filename = "data.bin";
    long size = MAX_DATA;
    long target = rand() % SEED_RANDOM;


    printDefault(1);
    generateRandomData(filename, size);
    printDefault(2);    
    quicksortFile(filename, 0, size - 1);





    // After sorting, check if the file is sorted
    if (isFileSorted(filename)) {
        printf("File is sorted.\n");
    } else {
        printf("File is not sorted.\n");
    }


    

    printDefault(4);        
    if (binarySearchFile(filename, target)) {
        printf("Element %ld found\n", target);
    } else {
        printf("Element %ld not found\n", target);
    }











    // Implement binary search on the sorted data with while 
    long number = 0;
    long searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);

         long result = binarySearchFile(filename, number);

        if(result != -1) {
            printf("Element %ld found at index %ld\n", number, result);
        } else {
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%ld", &searchAgain);
    }












    return 0;
}













/*



programing in c in file in linux:
Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
NO USE ARRAY, just maliputation file 


If you want to perform sorting and searching operations directly on a file without loading its content into an array or linked list, you'll need to implement a more complex algorithm that operates on the file data directly. Here's an example program that achieves this:


In this program, data is generated and written to a file. Then, quicksort is performed directly on the file's data using file operations. Finally, a binary search is implemented on the sorted data within the file.

Keep in mind that this approach involves more complex file operations and is generally less efficient compared to working with data in memory. It's primarily used when dealing with extremely large datasets that cannot fit into memory.










*/





















