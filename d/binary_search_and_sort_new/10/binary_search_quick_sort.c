#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int age;
    char phone[20];
} Person;

void generateRandomData(Person* people, int n) {
    char* names[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace"};
    char* phones[] = {"555-1234", "555-5678", "555-9876", "555-4321", "555-8765", "555-3456", "555-7890"};

    for (int i = 0; i < n; i++) {
        strcpy(people[i].name, names[rand() % 7]);
        people[i].age = rand() % 50 + 20; // Age between 20 and 70
        strcpy(people[i].phone, phones[rand() % 7]);
    }
}

void writeToFile(Person* people, int n, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(people, sizeof(Person), n, file);

    fclose(file);
}

void readFromFile(Person* people, int n, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fread(people, sizeof(Person), n, file);

    fclose(file);
}

int comparePeople(const void* a, const void* b) {
    return strcmp(((Person*)a)->name, ((Person*)b)->name);
}

void sortByNames(Person* people, int n) {
    qsort(people, n, sizeof(Person), comparePeople);
}

void printAllData(Person* people, int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Age: %d, Phone: %s\n", people[i].name, people[i].age, people[i].phone);
    }
}

int binarySearch(Person* people, int n, const char* target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(people[mid].name, target);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    int n = 5; // Change this to the desired number of random data

    Person people[n];
    generateRandomData(people, n);

    writeToFile(people, n, "data.txt");

    readFromFile(people, n, "data.txt");

    sortByNames(people, n);

    writeToFile(people, n, "sorted_data.txt");

    int choice;
    char target[50];
    do {
        printf("\nMenu:\n");
        printf("1. Search by name\n");
        printf("2. Sort data again\n");
        printf("3. Show all data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf("%s", target);
                int index = binarySearch(people, n, target);
                if (index != -1) {
                    printf("Found at index %d\n", index);
                } else {
                    printf("Not found\n");
                }
                break;
            case 2:
                sortByNames(people, n);
                writeToFile(people, n, "sorted_data.txt");
                printf("Data sorted and written to file.\n");
                break;
            case 3:
                printAllData(people, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
