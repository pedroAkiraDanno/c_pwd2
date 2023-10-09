#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    char name[30];
    int age;
    char phone[15];
};

FILE *unsortedFile;
FILE *sortedFile;

void generateRandomData(int numRecords) {
    for (int i = 0; i < numRecords; i++) {
        struct Record record;
        sprintf(record.name, "Name%d", rand() % 1000);
        record.age = rand() % 100;
        sprintf(record.phone, "555-555-%04d", rand() % 10000);
        fwrite(&record, sizeof(struct Record), 1, unsortedFile);
    }
}

void printRecord(struct Record *record) {
    printf("Name: %s, Age: %d, Phone: %s\n", record->name, record->age, record->phone);
}

void quicksort(long left, long right) {
    if (left >= right) return;

    struct Record pivot, temp, current;
    fseek(unsortedFile, (left + right) / 2 * sizeof(struct Record), SEEK_SET);
    fread(&pivot, sizeof(struct Record), 1, unsortedFile);

    long i = left;
    long j = right;

    while (i <= j) {
        fseek(unsortedFile, i * sizeof(struct Record), SEEK_SET);
        fread(&current, sizeof(struct Record), 1, unsortedFile);
        while (strcmp(current.name, pivot.name) < 0) {
            i++;
            fseek(unsortedFile, i * sizeof(struct Record), SEEK_SET);
            fread(&current, sizeof(struct Record), 1, unsortedFile);
        }

        fseek(unsortedFile, j * sizeof(struct Record), SEEK_SET);
        fread(&current, sizeof(struct Record), 1, unsortedFile);
        while (strcmp(current.name, pivot.name) > 0) {
            j--;
            fseek(unsortedFile, j * sizeof(struct Record), SEEK_SET);
            fread(&current, sizeof(struct Record), 1, unsortedFile);
        }

        if (i <= j) {
            fseek(unsortedFile, i * sizeof(struct Record), SEEK_SET);
            fread(&temp, sizeof(struct Record), 1, unsortedFile);

            fseek(unsortedFile, j * sizeof(struct Record), SEEK_SET);
            fwrite(&temp, sizeof(struct Record), 1, unsortedFile);

            fseek(unsortedFile, j * sizeof(struct Record), SEEK_SET);
            fwrite(&current, sizeof(struct Record), 1, unsortedFile);

            i++;
            j--;
        }
    }

    if (left < j) quicksort(left, j);
    if (i < right) quicksort(i, right);
}

void binarySearch(char *targetName) {
    long left = 0;
    fseek(sortedFile, 0, SEEK_END);
    long right = (ftell(sortedFile) / sizeof(struct Record)) - 1;
    long mid;

    while (left <= right) {
        mid = left + (right - left) / 2;
        fseek(sortedFile, mid * sizeof(struct Record), SEEK_SET);
        struct Record current;
        fread(&current, sizeof(struct Record), 1, sortedFile);

        int cmp = strcmp(current.name, targetName);

        if (cmp == 0) {
            printf("Record found at index %ld:\n", mid);
            printRecord(&current);
            return;
        }

        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("Record with name %s not found.\n", targetName);
}

void showAllData(FILE *file) {
    fseek(file, 0, SEEK_SET);
    struct Record current;
    while (fread(&current, sizeof(struct Record), 1, file)) {
        printRecord(&current);
    }
}

int main() {
    unsortedFile = fopen("unsorted_data.txt", "wb+");
    if (!unsortedFile) {
        printf("Error opening unsorted file.\n");
        return 1;
    }

    sortedFile = fopen("sorted_data.txt", "wb+");
    if (!sortedFile) {
        printf("Error opening sorted file.\n");
        fclose(unsortedFile);
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Generate Random Data\n");
        printf("2. Read and Sort Data\n");
        printf("3. Search Record by Name\n");
        printf("4. Show All Data\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateRandomData(10);
                printf("Random data generated and written to unsorted file.\n");
                break;
            case 2:
                fseek(unsortedFile, 0, SEEK_SET);
                fseek(sortedFile, 0, SEEK_SET);
                struct Record current;
                while (fread(&current, sizeof(struct Record), 1, unsortedFile)) {
                    fwrite(&current, sizeof(struct Record), 1, sortedFile);
                }
                quicksort(0, 9);
                printf("Data sorted and written to sorted file.\n");
                break;
            case 3:
                char targetName[30];
                printf("Enter name to search: ");
                scanf("%s", targetName);
                binarySearch(targetName);
                break;
            case 4:
                showAllData(sortedFile);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(unsortedFile);
    fclose(sortedFile);
    return 0;
}
