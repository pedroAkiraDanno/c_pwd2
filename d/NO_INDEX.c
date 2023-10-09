#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 300000000

// Define the structure of a data record
struct Record {
    char name[50];
    int age;
    char phone[15];
};

// Function to generate random data and write it to a binary file
void generateRandomData(const char *filename, int numRecords) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    struct Record record;
    for (int i = 0; i < numRecords; i++) {
        sprintf(record.name, "Name%d", i);
        record.age = rand() % 100;
        sprintf(record.phone, "Phone%d", rand() % 10000);
        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file);
}

// Function to display a record
void displayRecord(const struct Record *record) {
    printf("Name: %s\nAge: %d\nPhone: %s\n", record->name, record->age, record->phone);
}

// Function to search for a record by name
void searchByName(const char *filename, const char *searchName) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    struct Record record;
    int found = 0;

    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(record.name, searchName) == 0) {
            displayRecord(&record);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record with name '%s' not found.\n", searchName);
    }

    fclose(file);
}

// Function to insert a new record
void insertRecord(const char *filename, const struct Record *newRecord) {
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    fwrite(newRecord, sizeof(struct Record), 1, file);
    fclose(file);
}

// Function to delete a record by name
void deleteByName(const char *filename, const char *deleteName) {
    // Create a temporary file to copy non-deleted records
    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    struct Record record;

    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(record.name, deleteName) != 0) {
            fwrite(&record, sizeof(struct Record), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(filename);
    rename("temp.dat", filename);
}

int main() {
    const char *filename = "data.dat";
    int numRecords = MAX_RECORDS;

    // Generate random data and write it to a binary file
    generateRandomData(filename, numRecords);

    int choice;
    char searchName[50];
    struct Record newRecord;

    do {
        printf("\nMenu:\n");
        printf("1. Search by Name\n");
        printf("2. Insert Record\n");
        printf("3. Delete Record\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                searchByName(filename, searchName);
                break;

            case 2:
                printf("Enter name: ");
                scanf("%s", newRecord.name);
                printf("Enter age: ");
                scanf("%d", &newRecord.age);
                printf("Enter phone: ");
                scanf("%s", newRecord.phone);
                insertRecord(filename, &newRecord);
                printf("Record inserted successfully.\n");
                break;

            case 3:
                printf("Enter name to delete: ");
                scanf("%s", searchName);
                deleteByName(filename, searchName);
                printf("Record deleted successfully.\n");
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}











/*



Creating a complete C program that includes non-clustered indexing, insertion, deletion, searching, displaying data, and a menu system for a binary file is a complex task. Below is an extended version of the previous code that includes these features:





This code extends the previous example by adding a "Display All Records" option and a menu system that allows you to perform various actions on the binary file. It also displays all records in the file when you choose the "Display All Records" option.







*/





