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
    for (int i = 0; i < 10; i++) {
        struct Person p;
        generateRandomPerson(&p);
        writePersonToFile(p, unsortedFile);
    }

    // Close and reopen for reading
    fclose(unsortedFile);
    unsortedFile = fopen("unsorted_data.txt", "r");

    // Create a sorted file
    FILE* sortedFile = fopen("sorted_data.txt", "w+");
    if (sortedFile == NULL) {
        printf("Error opening sorted file.\n");
        return 1;
    }

    // Read data from unsorted file, quicksort, and write to sorted file
    while (!feof(unsortedFile)) {
        struct Person p = readPersonFromFile(unsortedFile);
        writePersonToFile(p, sortedFile);
    }

    // Sort the data in sorted file
    fseek(sortedFile, 0, SEEK_SET);
    int numRecords = ftell(sortedFile) / sizeof(struct Person);
    fseek(sortedFile, 0, SEEK_SET);
    struct Person* data = malloc(numRecords * sizeof(struct Person));
    for (int i = 0; i < numRecords; i++) {
        data[i] = readPersonFromFile(sortedFile);
    }
    qsort(data, numRecords, sizeof(struct Person), compare);
    fseek(sortedFile, 0, SEEK_SET);
    for (int i = 0; i < numRecords; i++) {
        writePersonToFile(data[i], sortedFile);
    }
    free(data);

    // Perform binary search on the sorted data
    char target[50];
    printf("Enter the name to search: ");
    scanf("%s", target);
    int index = binarySearch(sortedFile, target);

    // Display the result
    if (index >= 0) {
        fseek(sortedFile, index * sizeof(struct Person), SEEK_SET);
        struct Person result = readPersonFromFile(sortedFile);
        printf("Found at index %d:\n", index);
        printf("Name: %s\nAge: %d\nPhone: %s\n", result.name, result.age, result.phone);
    } else {
        printf("Not found.\n");
    }

    // Display all data
    printf("All Data:\n");
    displayAllData(sortedFile);

    fclose(unsortedFile);
    fclose(sortedFile);
    return 0;
}




