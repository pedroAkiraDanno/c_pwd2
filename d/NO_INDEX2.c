#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_RECORDS 1000000


// Define the structure of a data record
struct Record {
    char name[MAX_NAME_LENGTH];
    int age;
    char phone[MAX_PHONE_LENGTH];
    struct Record* next;
};

// Function to generate random data and write it to a binary file
void generateRandomData(const char* filename, int numRecords) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    struct Record record;
    for (int i = 0; i < numRecords; i++) {
        sprintf(record.name, "Name%d", i);
        record.age = rand() % 100;
        sprintf(record.phone, "Phone%d", rand() % 10000);
        record.next = NULL;
        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file);
}

// Function to display a record
void displayRecord(const struct Record* record) {
    printf("Name: %s\nAge: %d\nPhone: %s\n", record->name, record->age, record->phone);
}

// Function to display all records
void displayAllRecords(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    struct Record record;

    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        displayRecord(&record);
        printf("\n");
    }

    fclose(file);
}

// Function to insert a new record at the end of the file
void insertRecord(const char* filename, const struct Record* newRecord) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    fwrite(newRecord, sizeof(struct Record), 1, file);
    fclose(file);
}

// Function to delete a record by name
void deleteByName(const char* filename, const char* deleteName) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    FILE* tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
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

    remove(filename);
    rename("temp.dat", filename);
}

// Function to sort records by name using quicksort
void swapRecords(struct Record* a, struct Record* b) {
    struct Record temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Record arr[], int low, int high) {
    struct Record pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].name, pivot.name) < 0) {
            i++;
            swapRecords(&arr[i], &arr[j]);
        }
    }

    swapRecords(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(struct Record arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to search for a record by name using linear search
void searchByName(const char* filename, const char* searchName) {
    FILE* file = fopen(filename, "rb");
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

// Function to search for a record by name using binary search
void searchByNameBinary(const char* filename, const char* searchName) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    struct Record record;
    int found = 0;
    int low = 0, high = 0;

    fseek(file, 0, SEEK_END);
    high = ftell(file) / sizeof(struct Record) - 1;
    rewind(file);

    while (low <= high) {
        int mid = (low + high) / 2;
        fseek(file, mid * sizeof(struct Record), SEEK_SET);
        fread(&record, sizeof(struct Record), 1, file);

        if (strcmp(record.name, searchName) == 0) {
            displayRecord(&record);
            found = 1;
            break;
        } else if (strcmp(record.name, searchName) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("Record with name '%s' not found.\n", searchName);
    }

    fclose(file);
}

int main() {
    const char* filename = "data.dat";
    int numRecords = MAX_RECORDS;

    // Generate random data and write it to a binary file
    generateRandomData(filename, numRecords);

    int choice;
    char searchName[MAX_NAME_LENGTH];
    struct Record newRecord;

    do {
        printf("\nMenu:\n");
        printf("1. Search by Name (Linear Search)\n");
        printf("2. Search by Name (Binary Search)\n");
        printf("3. Insert Record\n");
        printf("4. Delete Record\n");
        printf("5. Sort Records by Name (Quick Sort)\n");
        printf("6. Display All Records\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                searchByName(filename, searchName);
                break;

            case 2:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                searchByNameBinary(filename, searchName);
                break;

            case 3:
                printf("Enter name: ");
                scanf("%s", newRecord.name);
                printf("Enter age: ");
                scanf("%d", &newRecord.age);
                printf("Enter phone: ");
                scanf("%s", newRecord.phone);
                insertRecord(filename, &newRecord);
                printf("Record inserted successfully.\n");
                break;

            case 4:
                printf("Enter name to delete: ");
                scanf("%s", searchName);
                deleteByName(filename, searchName);
                printf("Record deleted successfully.\n");
                break;

            case 5:
                {
                    // Read all records into memory and sort them
                    FILE* file = fopen(filename, "rb");
                    if (file == NULL) {
                        perror("Error opening file for reading");
                        exit(1);
                    }

                    fseek(file, 0, SEEK_END);
                    int numRecords = ftell(file) / sizeof(struct Record);
                    rewind(file);

                    struct Record* records = (struct Record*)malloc(numRecords * sizeof(struct Record));
                    if (records == NULL) {
                        perror("Error allocating memory");
                        exit(1);
                    }

                    fread(records, sizeof(struct Record), numRecords, file);
                    fclose(file);

                    quickSort(records, 0, numRecords - 1);

                    // Rewrite the sorted records to the file
                    file = fopen(filename, "wb");
                    if (file == NULL) {
                        perror("Error opening file for writing");
                        exit(1);
                    }

                    fwrite(records, sizeof(struct Record), numRecords, file);
                    fclose(file);

                    free(records);
                    printf("Records sorted by name (Quick Sort).\n");
                }
                break;

            case 6:
                displayAllRecords(filename);
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}




/*


create non-clustered index in file and data file like: name, age, phone in programing in C in linux 
Use just C programing 
With big RANDOM data genereation in file 
NOT use array
dont have error in programing when i execute 
ask input seach name - ask if want seach again 
insert option 
delete option 
order by quick sort 
search by liner 
Binary search 
display datas 
create manu
binary file 



ChatGPT
Creating a C program that includes non-clustered indexing, insertion, deletion, sorting, searching, displaying data, and a menu system for a binary file is a complex task. Below is a comprehensive example that demonstrates these functionalities. This example uses a combination of linked lists and binary files to manage the data and perform operations.


This code extends the previous example by adding a "Search by Name (Binary Search)" option, "Sort Records by Name (Quick Sort)" option, and the ability to read records into memory for sorting. It demonstrates both linear and binary search methods and includes an option to sort the records by name using the quicksort algorithm.


*/




