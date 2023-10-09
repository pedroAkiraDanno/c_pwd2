#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 300000000
#define MAX_NAME_LENGTH 50
#define DATA_FILE "data.bin"
#define INDEX_FILE "index.bin"

struct Record {
    char name[MAX_NAME_LENGTH];
    int age;
    char phone[MAX_NAME_LENGTH];
};

// Function to generate random data and store it in the data file
void generateRandomData() {
    FILE *dataFile = fopen(DATA_FILE, "wb");
    if (!dataFile) {
        perror("Error opening data file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_RECORDS; i++) {
        struct Record record;
        sprintf(record.name, "Name%d", i);
        record.age = rand() % 100;
        sprintf(record.phone, "Phone%d", rand() % 10000);
        fwrite(&record, sizeof(struct Record), 1, dataFile);
    }

    fclose(dataFile);
}

// Function to create a non-clustered index based on the name field
void createIndex() {
    FILE *dataFile = fopen(DATA_FILE, "rb");
    FILE *indexFile = fopen(INDEX_FILE, "wb");
    if (!dataFile || !indexFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    struct Record record;
    long offset = 0;
    while (fread(&record, sizeof(struct Record), 1, dataFile) == 1) {
        fprintf(indexFile, "%s %ld\n", record.name, offset);
        offset += sizeof(struct Record);
    }

    fclose(dataFile);
    fclose(indexFile);
}

// Function to search for a record by name using the index
void searchByName(const char *name) {
    FILE *indexFile = fopen(INDEX_FILE, "r");
    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!indexFile || !dataFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_NAME_LENGTH];
    long offset;
    int found = 0;

    while (fscanf(indexFile, "%s %ld", buffer, &offset) == 2) {
        if (strcmp(name, buffer) == 0) {
            struct Record record;
            fseek(dataFile, offset, SEEK_SET);
            fread(&record, sizeof(struct Record), 1, dataFile);
            printf("Name: %s, Age: %d, Phone: %s\n", record.name, record.age, record.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }

    fclose(indexFile);
    fclose(dataFile);
}

int main() {
    generateRandomData();
    createIndex();



    char searchName[MAX_NAME_LENGTH];
    int searchAgain = 1;

    while (searchAgain) {
         printf("Enter a name to search for: ");
         scanf("%s", searchName);

         searchByName(searchName);

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%d", &searchAgain);
    }










    return 0;
}














/*


create non-clustered index in file and data file like: name, age, phone in programing in C in linux 
Use just C programing 
With big RANDOM data genereation in file 
NOT use array
dont have error in programing when i execute 
ask input seach name 
binary file 
DRAW HOW THIS INDEX WORKS 

ChatGPT
Creating a non-clustered index in a binary file in C on Linux involves several steps: generating random data, creating an index file, and implementing a search mechanism. Here's a simple example, along with a conceptual drawing of how the index works.















Now, let's conceptualize how this index works:

Generate Data: Initially, random data records are generated and stored in the data.bin binary file. Each record consists of name, age, and phone fields.

Create Index: The createIndex() function reads the data from data.bin and creates an index file (index.bin) where each line contains the name field and the corresponding offset in data.bin.

Search by Name: To search for a record by name, the searchByName() function reads the index file line by line. When a match is found with the target name, it retrieves the offset from the index and uses it to directly seek and read the record from data.bin. This way, it avoids reading the entire data file and efficiently finds the desired record.

The index file essentially provides a map from names to offsets in the data file, allowing for efficient random access to specific records based on the name field.












*/





















