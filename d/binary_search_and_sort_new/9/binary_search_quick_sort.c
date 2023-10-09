#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    char phone[15];
};

void generateRandomPerson(struct Person* p) {
    sprintf(p->name, "Person%d", rand() % 1000);
    p->age = rand() % 100;
    sprintf(p->phone, "123-456-%04d", rand() % 10000);
}

void writePersonToFile(struct Person p, FILE* file) {
    fprintf(file, "%s %d %s\n", p.name, p.age, p.phone);
}

struct Person readPersonFromFile(FILE* file) {
    struct Person p;
    fscanf(file, "%s %d %s\n", p.name, &p.age, p.phone);
    return p;
}

int compare(const void* a, const void* b) {
    return strcmp(((struct Person*)a)->name, ((struct Person*)b)->name);
}

int binarySearch(FILE* file, char* target) {
    fseek(file, 0, SEEK_SET);
    int left = 0, right = ftell(file) / sizeof(struct Person) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        struct Person p = readPersonFromFile(file);
        int cmp = strcmp(p.name, target);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void displayAllData(FILE* file) {
    fseek(file, 0, SEEK_SET);
    while (!feof(file)) {
        struct Person p = readPersonFromFile(file);
        printf("Name: %s, Age: %d, Phone: %s\n", p.name, p.age, p.phone);
    }
}

int main() {
    FILE* unsortedFile = fopen("unsorted_data.txt", "w+");
    if (unsortedFile == NULL) {
        printf("Error opening unsorted file.\n");
        return 1;
    }

    // Generate random data and write it to unsorted file
    for (int i = 0; i < 10000; i++) {
        struct Person p;
        generateRandomPerson(&p);
        writePersonToFile(p, unsortedFile);
    }

    fclose(unsortedFile);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Sort and Display Data\n");
        printf("2. Search for a Person\n");
        printf("3. Quit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE* unsortedFile = fopen("unsorted_data.txt", "r");
                if (unsortedFile == NULL) {
                    printf("Error opening unsorted file.\n");
                    return 1;
                }

                FILE* sortedFile = fopen("sorted_data.txt", "w+");
                if (sortedFile == NULL) {
                    printf("Error opening sorted file.\n");
                    return 1;
                }

                while (!feof(unsortedFile)) {
                    struct Person p = readPersonFromFile(unsortedFile);
                    writePersonToFile(p, sortedFile);
                }

                fclose(unsortedFile);
                fclose(sortedFile);

                FILE* sortedFileRead = fopen("sorted_data.txt", "r");
                int numRecords = ftell(sortedFileRead) / sizeof(struct Person);
                fseek(sortedFileRead, 0, SEEK_SET);
                struct Person* data = malloc(numRecords * sizeof(struct Person));
                for (int i = 0; i < numRecords; i++) {
                    data[i] = readPersonFromFile(sortedFileRead);
                }
                qsort(data, numRecords, sizeof(struct Person), compare);

                FILE* sortedFileWrite = fopen("sorted_data.txt", "w+");
                fseek(sortedFileWrite, 0, SEEK_SET);
                for (int i = 0; i < numRecords; i++) {
                    writePersonToFile(data[i], sortedFileWrite);
                }

                free(data);
                fclose(sortedFileWrite);
                printf("Data sorted and written to file.\n");
                break;
            }
            case 2: {
                char target[50];
                printf("Enter the name to search: ");
                scanf("%s", target);

                FILE* sortedFile = fopen("sorted_data.txt", "r");
                int index = binarySearch(sortedFile, target);

                if (index >= 0) {
                    fseek(sortedFile, index * sizeof(struct Person), SEEK_SET);
                    struct Person result = readPersonFromFile(sortedFile);
                    printf("Found at index %d:\n", index);
                    printf("Name: %s\nAge: %d\nPhone: %s\n", result.name, result.age, result.phone);
                } else {
                    printf("Not found.\n");
                }

                fclose(sortedFile);
                break;
            }
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
