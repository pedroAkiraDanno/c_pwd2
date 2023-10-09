#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>




#define MAX_NAME_LENGTH 100
#define MAX_DATA        1000
#define MAX_SED         100




/*
void printDefault(int parameter) {
    if (parameter == 1) {
        printf("Generating data...\n");
    } else if (parameter == 2) {
        printf("Sorting data...\n");
    } else {
        printf("Invalid parameter!\n");
    }
}
*/



void printDefault(int parameter) {
    switch (parameter) {
        case 1:
            printf("Generating data...\n");
            break;
        case 2:
            printf("Sorting data...\n");
            break;
        case 3:
            printf("Writing bin file to txt file...\n");
            break;
        default:
            printf("Invalid parameter!\n");
    }
}







// Struct for the data
typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    long phone;
} Record;

// Function to generate random data
void generateRandomData(const char* filename, long size) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < size; i++) {
        Record record;
        //sprintf(record.name, "Name%d", rand() );          // 1 to 9999
        sprintf(record.name, "Name%d", rand() % MAX_SED);          // 1 to 9999        
        record.age = rand() % 100;
        record.phone = rand() % 10000;

        fwrite(&record, sizeof(Record), 1, file);
    }

    fclose(file);
}

// Function to compare two records for quicksort
int compareRecords(const void* a, const void* b) {
    return strcmp(((Record*)a)->name, ((Record*)b)->name);
}

// Function to perform quicksort on the file
void quicksortFile(const char* filename, long left, long right) {
    if (left < right) {
        FILE* file = fopen(filename, "rb+");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        Record pivot, temp;
        fseek(file, left * sizeof(Record), SEEK_SET);
        fread(&pivot, sizeof(Record), 1, file);

        long i = left;
        long j = right;

        while (i < j) {
            while (strcmp(pivot.name, temp.name) >= 0 && i < right) {
                i++;
                fseek(file, i * sizeof(Record), SEEK_SET);
                fread(&temp, sizeof(Record), 1, file);
            }

            while (strcmp(pivot.name, temp.name) < 0) {
                j--;
                fseek(file, j * sizeof(Record), SEEK_SET);
                fread(&temp, sizeof(Record), 1, file);
            }

            if (i < j) {
                fseek(file, i * sizeof(Record), SEEK_SET);
                fwrite(&temp, sizeof(Record), 1, file);

                fseek(file, j * sizeof(Record), SEEK_SET);
                fwrite(&pivot, sizeof(Record), 1, file);
            }
        }

        fseek(file, left * sizeof(Record), SEEK_SET);
        fwrite(&temp, sizeof(Record), 1, file);

        fseek(file, j * sizeof(Record), SEEK_SET);
        fwrite(&pivot, sizeof(Record), 1, file);

        fclose(file);

        quicksortFile(filename, left, j - 1);
        quicksortFile(filename, j + 1, right);
    }
}

// Function to perform binary search on the file
int binarySearchFile(const char* filename, const char* targetName) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file) / sizeof(Record);

    long left = 0;
    long right = size - 1;
    long mid;
    Record record;

    while (left <= right) {
        mid = left + (right - left) / 2;
        fseek(file, mid * sizeof(Record), SEEK_SET);
        fread(&record, sizeof(Record), 1, file);

        int cmp = strcmp(targetName, record.name);

        if (cmp == 0) {
            fclose(file);
            return mid;
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    fclose(file);
    return -1;
}









// Function to write data to a .txt file in human-readable format
void writeDataToTxtFile(const char* filename, long size) {
    FILE* binFile = fopen(filename, "rb");
    FILE* txtFile = fopen("sorted_data.txt", "w");

    if (binFile == NULL || txtFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Record record;

    for (long i = 0; i < size; i++) {
        fseek(binFile, i * sizeof(Record), SEEK_SET);
        fread(&record, sizeof(Record), 1, binFile);

        fprintf(txtFile, "Name: %s, Age: %d, Phone: %ld\n", record.name, record.age, record.phone);
    }

    fclose(binFile);
    fclose(txtFile);
}









int main() {
    srand(time(NULL));

    const char* filename = "data.bin";
    long size = MAX_DATA; // Define your desired size

    // Generate random data
    printDefault(1);    
    generateRandomData(filename, size);

    // Sort the data
    printDefault(2);    
    quicksortFile(filename, 0, size - 1);


    // Write sorted data to a text file
    printDefault(3);    
    writeDataToTxtFile(filename, size);



    // Search for a record
    const char* targetName = "Name9999"; // Define your desired target name
    int result = binarySearchFile(filename, targetName);

    if (result != -1) {
        printf("Record found at index %d\n", result);
    } else {
        printf("Record not found\n");
    }









// Implement binary search on the sorted data with while 
char target2[MAX_NAME_LENGTH];  // Define target2 as an array of characters
int searchAgain = 1;

while (searchAgain) {
     printf("Enter a target to search for: ");
     scanf("%s", target2);

     int result2 = binarySearchFile(filename, target2);

    if(result2 != -1) {
        printf("Element %s found at index %d\n", target2, result2);
    } else {
        printf("Element %s not found\n", target2);
    }

     printf("Do you want to search again? (1 for yes, 0 for no): ");
     scanf("%d", &searchAgain);
}














    return 0;
}









/*


programing in c in file in linux:
Generate random data and write it to a file. (name, age, phone)
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
NO USE ARRAY, just maliputation file 


Certainly! Below is an example C program that generates random data (name, age, phone), writes it to a file, performs quicksort, writes the sorted data back to the file, and implements binary search without using an array, but by directly manipulating the file:







In this program, Record is a struct that represents a data entry with a name, age, and phone number. The functions generateRandomData, quicksortFile, and binarySearchFile work directly with the file to generate random data, perform quicksort, and implement binary search respectively.



*/





















