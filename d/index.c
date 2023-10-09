#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 10000

// Structure to hold a record
struct Record {
    char name[100];
    int age;
    char phone[15];
};

// Structure to hold the non-clustered index
struct IndexEntry {
    char name[100];
    int offset; // Offset of the corresponding record in the data file
};

// Function to generate example data and write it to a file
void generateExampleData() {
    FILE *dataFile = fopen("data.txt", "w");
    if (dataFile == NULL) {
        perror("Error opening data file for writing");
        exit(1);
    }

    // Generate example data and write it to the data file
    struct Record records[MAX_RECORDS];
    for (int i = 0; i < MAX_RECORDS; i++) {
        sprintf(records[i].name, "Name%d", i + 1);
        records[i].age = 20 + i;
        sprintf(records[i].phone, "Phone%d", i + 1);
        fprintf(dataFile, "%s,%d,%s\n", records[i].name, records[i].age, records[i].phone);
    }

    fclose(dataFile);
}

int main() {
    // Generate example data and write it to the data file
    generateExampleData();

    FILE *dataFile, *indexFile;
    struct Record records[MAX_RECORDS];
    struct IndexEntry index[MAX_RECORDS];
    int recordCount = 0;

    // Open the data file for reading
    dataFile = fopen("data.txt", "r");

    if (dataFile == NULL) {
        perror("Error opening data file");
        return 1;
    }

    // Read data file and build the index
    while (fscanf(dataFile, "%[^,],%d,%[^\n]\n", records[recordCount].name, &records[recordCount].age, records[recordCount].phone) != EOF) {
        // Store the name and its offset in the index
        strcpy(index[recordCount].name, records[recordCount].name);
        index[recordCount].offset = recordCount;
        recordCount++;
    }

    // Open the index file for writing
    indexFile = fopen("index.txt", "w");

    if (indexFile == NULL) {
        perror("Error opening index file");
        fclose(dataFile);
        return 1;
    }

    // Write the index to the index file
    for (int i = 0; i < recordCount; i++) {
        fprintf(indexFile, "%s,%d\n", index[i].name, index[i].offset);
    }

    // Close both files
    fclose(dataFile);
    fclose(indexFile);

    // Perform lookups using the index
    char searchName[100];
    int foundOffset = -1;

    printf("Enter name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < recordCount; i++) {
        if (strcmp(searchName, index[i].name) == 0) {
            foundOffset = index[i].offset;
            break;
        }
    }

    if (foundOffset != -1) {
        printf("Record found:\n");
        printf("Name: %s\nAge: %d\nPhone: %s\n", records[foundOffset].name, records[foundOffset].age, records[foundOffset].phone);
    } else {
        printf("Record not found.\n");
    }

    return 0;
}

















/*


create non-clustered index in file and data file like: name, age, phone in programing in C in linux 
Use just C programing 
With example data genereation in file 
ChatGPT
Creating a non-clustered index for a file with data fields like "name," "age," and "phone" in C on Linux, including example data generation, can be done as follows:





In this program:

The generateExampleData function generates example data and writes it to the "data.txt" file.

The main part of the program reads data from "data.txt," creates an index in "index.txt," and allows you to perform lookups based on the "name" field.

Example data is generated and stored in "data.txt" for demonstration purposes. You can adjust the number of records and data as needed.

Please note that this is a simplified example, and in a real-world scenario, you would need error handling, memory management, and more robust indexing techniques for efficiency and scalability.










*/






















