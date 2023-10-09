#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>



#define MAX_RANODM  100000000 // Change this to your desired number of records      - ABOUT 7GB





// Define the structure for a data record
struct Record {
    char name[50];
    int age;
    char phone[20];
};




// Function to generate random data and write it to a binary file
void generateRandomData(const char* filename, int numRecords) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < numRecords; i++) {
        struct Record record;
        snprintf(record.name, sizeof(record.name), "Name%d", i);
        record.age = rand() % 50 + 20; // Random age between 20 and 69
        snprintf(record.phone, sizeof(record.phone), "Phone%d", i);

        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file);
}

// Quick Sort implementation for records in a binary file
void quickSort(FILE* file, long left, long right) {
    if (left < right) {
        long pivotIndex = left + (right - left) / 2;
        fseek(file, pivotIndex * sizeof(struct Record), SEEK_SET);
        struct Record pivotRecord;
        fread(&pivotRecord, sizeof(struct Record), 1, file);

        long i = left, j = right;
        struct Record temp;

        do {
            fseek(file, i * sizeof(struct Record), SEEK_SET);
            fread(&temp, sizeof(struct Record), 1, file);
            while (strcmp(temp.name, pivotRecord.name) < 0) {
                i++;
                fseek(file, i * sizeof(struct Record), SEEK_SET);
                fread(&temp, sizeof(struct Record), 1, file);
            }

            fseek(file, j * sizeof(struct Record), SEEK_SET);
            fread(&temp, sizeof(struct Record), 1, file);
            while (strcmp(temp.name, pivotRecord.name) > 0) {
                j--;
                fseek(file, j * sizeof(struct Record), SEEK_SET);
                fread(&temp, sizeof(struct Record), 1, file);
            }

            if (i <= j) {
                fseek(file, i * sizeof(struct Record), SEEK_SET);
                fwrite(&temp, sizeof(struct Record), 1, file);

                fseek(file, j * sizeof(struct Record), SEEK_SET);
                fwrite(&pivotRecord, sizeof(struct Record), 1, file);

                i++;
                j--;
            }
        } while (i <= j);

        if (left < j) {
            quickSort(file, left, j);
        }
        if (i < right) {
            quickSort(file, i, right);
        }
    }
}

// Function to perform a binary search on the sorted binary file
void binarySearch(const char* filename, const char* targetName) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    long recordSize = sizeof(struct Record);
    long numRecords = fileSize / recordSize;

    struct Record targetRecord;
    strcpy(targetRecord.name, targetName);

    long left = 0;
    long right = numRecords - 1;
    long foundIndex = -1;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        fseek(file, mid * recordSize, SEEK_SET);
        struct Record midRecord;
        fread(&midRecord, sizeof(struct Record), 1, file);

        int comparison = strcmp(targetName, midRecord.name);

        if (comparison == 0) {
            foundIndex = mid;
            break;
        } else if (comparison < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (foundIndex != -1) {
        fseek(file, foundIndex * recordSize, SEEK_SET);
        struct Record foundRecord;
        fread(&foundRecord, sizeof(struct Record), 1, file);

        printf("Record found:\n");
        printf("Name: %s\n", foundRecord.name);
        printf("Age: %d\n", foundRecord.age);
        printf("Phone: %s\n", foundRecord.phone);
    } else {
        printf("Record not found.\n");
    }

    fclose(file);
}

// Function to display all records in the binary file
void displayData(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    long recordSize = sizeof(struct Record);
    long numRecords = fileSize / recordSize;

    fseek(file, 0, SEEK_SET);

    printf("Records in the file:\n");

    for (long i = 0; i < numRecords; i++) {
        struct Record record;
        fread(&record, sizeof(struct Record), 1, file);

        printf("Name: %s, Age: %d, Phone: %s\n", record.name, record.age, record.phone);
    }

    fclose(file);
}

int main() {
    const char* filename = "data.bin";
    int numRecords = MAX_RANODM; // Change this to your desired number of records

    generateRandomData(filename, numRecords);

    // Sort the data in the binary file using Quick Sort
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    long recordSize = sizeof(struct Record);
    long numRecordsInFile = fileSize / recordSize;

    quickSort(file, 0, numRecordsInFile - 1); // Perform Quick Sort on the data

    fclose(file);

    int choice;
    char searchName[50];

    do {
        printf("\nMenu:\n");
        printf("1. Search by name\n");
        printf("2. Display all data\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                binarySearch(filename, searchName);
                break;
            case 2:
                displayData(filename);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}










/*



mkdir /root/c 
cd /root/c 



rm * -fr 

vi t.c
gcc t.c -o t

./t








*/





















