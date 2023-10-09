#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a record
struct Record {
    char name[50];
    int age;
    char phone[15];
};

// Structure to represent an index entry
struct IndexEntry {
    char name[50];
    long offset; // Offset in the data file
};

// Function to add a record to the database
void addRecord(FILE* dataFile, const struct Record* record) {
    fseek(dataFile, 0, SEEK_END);
    fwrite(record, sizeof(struct Record), 1, dataFile);
}

// Function to create a non-clustered index for the 'name' field
void createIndex(FILE* dataFile, FILE* indexFile) {
    fseek(dataFile, 0, SEEK_SET);
    struct IndexEntry entry;
    while (fread(&entry.name, sizeof(entry.name), 1, dataFile) == 1) {
        entry.offset = ftell(dataFile) - sizeof(entry.name);
        fseek(indexFile, 0, SEEK_END);
        fwrite(&entry, sizeof(struct IndexEntry), 1, indexFile);
    }
}

// Function to search for a record by name using the non-clustered index
void searchByName(FILE* indexFile, FILE* dataFile, const char* name) {
    struct IndexEntry entry;
    fseek(indexFile, 0, SEEK_SET);
    while (fread(&entry, sizeof(struct IndexEntry), 1, indexFile) == 1) {
        if (strcmp(entry.name, name) == 0) {
            fseek(dataFile, entry.offset, SEEK_SET);
            struct Record record;
            fread(&record, sizeof(struct Record), 1, dataFile);
            printf("Name: %s, Age: %d, Phone: %s\n", record.name, record.age, record.phone);
            return;
        }
    }
    printf("Record not found for name: %s\n", name);
}

int main() {
    FILE* dataFile = fopen("data.dat", "ab+");
    if (!dataFile) {
        perror("Error opening data file");
        return 1;
    }

    FILE* indexFile = fopen("index.dat", "ab+");
    if (!indexFile) {
        perror("Error opening index file");
        return 1;
    }

    // Generate example data and add to the database
    struct Record exampleData[] = {
        {"Alice", 25, "123-456-7890"},
        {"Bob", 30, "987-654-3210"},
        // Add more records here
    };

    for (size_t i = 0; i < sizeof(exampleData) / sizeof(exampleData[0]); i++) {
        addRecord(dataFile, &exampleData[i]);
    }

    // Create the non-clustered index
    createIndex(dataFile, indexFile);

    // Search for a record by name
    searchByName(indexFile, dataFile, "Alice");

    // Close files
    fclose(dataFile);
    fclose(indexFile);

    return 0;
}
