#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 10000
#define MAX_NAME_LENGTH 50
#define DATA_FILE "data.dat"
#define INDEX_FILE "index.dat"

struct Record {
    char name[MAX_NAME_LENGTH];
    int age;
    char phone[MAX_NAME_LENGTH];
};

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
        fwrite(&offset, sizeof(long), 1, indexFile);
        offset += sizeof(struct Record);
    }

    fclose(dataFile);
    fclose(indexFile);
}


void searchByName(const char *name) {
    FILE *indexFile = fopen(INDEX_FILE, "rb");
    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!indexFile || !dataFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    long offset;
    struct Record record;
    int found = 0;

    for (int i = 0; i < MAX_RECORDS; i++) {
        fread(&offset, sizeof(long), 1, indexFile);
        fseek(dataFile, offset, SEEK_SET);
        fread(&record, sizeof(struct Record), 1, dataFile);

        if (strcmp(name, record.name) == 0) {
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
    printf("Enter a name to search for: ");
    scanf("%s", searchName);

    searchByName(searchName);

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

ChatGPT
To create a non-clustered index for data stored in a binary file and perform searches based on the "name" field in C on Linux without using arrays, you can follow the example below. This example generates random data, creates an index file, and allows users to search for records by name:








This program generates random data, creates a non-clustered index, and allows you to search for records by name. It uses binary files for both the data and index storage.








*/












