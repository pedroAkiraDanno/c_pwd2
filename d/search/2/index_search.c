#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILENAME "random_data.txt"
#define INDEX_FILENAME "index.txt"
#define MAX_RECORD_LENGTH 100

// Structure for the index entry
struct IndexEntry {
    int key;
    long position;
};

// Function to create an index file for a data file
void createIndexFile(FILE *dataFile, FILE *indexFile) {
    int key;
    long position = 0;
    struct IndexEntry indexEntry;

    // Open the data file
    dataFile = fopen(DATA_FILENAME, "r");
    if (!dataFile) {
        perror("Data file open error");
        exit(1);
    }

    // Open the index file
    indexFile = fopen(INDEX_FILENAME, "wb");
    if (!indexFile) {
        perror("Index file open error");
        exit(1);
    }

    // Initialize the index file
    while (fscanf(dataFile, "%d", &key) != EOF) {
        indexEntry.key = key;
        indexEntry.position = position;
        fwrite(&indexEntry, sizeof(struct IndexEntry), 1, indexFile);

        // Skip the rest of the record
        while (fgetc(dataFile) != '\n' && !feof(dataFile)) {
            position++;
        }

        // Increment position to account for the newline character
        position++;
    }

    fclose(dataFile);
    fclose(indexFile);
}

// Function to perform an index search and retrieve a record
void indexSearch(FILE *dataFile, FILE *indexFile, int searchKey) {
    struct IndexEntry indexEntry;
    int found = 0;

    // Open the index file
    indexFile = fopen(INDEX_FILENAME, "rb");
    if (!indexFile) {
        perror("Index file open error");
        exit(1);
    }

    // Search for the key in the index
    while (fread(&indexEntry, sizeof(struct IndexEntry), 1, indexFile) == 1) {
        if (indexEntry.key == searchKey) {
            found = 1;
            break;
        }
    }

    if (found) {
        // Open the data file
        dataFile = fopen(DATA_FILENAME, "r");
        if (!dataFile) {
            perror("Data file open error");
            exit(1);
        }

        // Seek to the record's position and print the record
        fseek(dataFile, indexEntry.position, SEEK_SET);
        char record[MAX_RECORD_LENGTH];
        if (fgets(record, sizeof(record), dataFile)) {
            printf("Record found at position %ld: %s", indexEntry.position, record);
        } else {
            printf("Record not found.\n");
        }

        fclose(dataFile);
    } else {
        printf("Record with key %d not found.\n", searchKey);
    }

    fclose(indexFile);
}

int main() {
    FILE *dataFile = NULL, *indexFile = NULL;
    int searchKey;

    printf("Enter the key to search: ");
    scanf("%d", &searchKey);

    // Create an index for the data file
    createIndexFile(dataFile, indexFile);

    // Perform an index search and retrieve the record
    indexSearch(dataFile, indexFile, searchKey);

    return 0;
}











/*

In this program:

createIndexFile function generates an index for the data file. It reads the data file, extracts keys, and stores key-position pairs in the index file.

indexSearch function takes a search key, looks up its position in the index, and retrieves the corresponding record from the data file.

To execute the program:

Save the C code to a file (e.g., index_search.c).

Create a random_data.txt file with records as shown earlier.

Compile the program using gcc:

bash
Copy code
gcc index_search.c -o index_search
Run the program:

bash
Copy code
./index_search
Enter a key when prompted, and the program will perform an index search and display the corresponding record if found.






*/




