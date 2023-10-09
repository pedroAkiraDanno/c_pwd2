#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DATA 10000

struct Person {
    char name[50];
    int age;
    char phone[15];
};

void generateRandomData(const char* filename, int numEntries) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numEntries; i++) {
        struct Person p;
        sprintf(p.name, "Person%d", rand() % 1000);
        p.age = rand() % 50 + 20;
        sprintf(p.phone, "555-%04d", rand() % 10000);

        fwrite(&p, sizeof(struct Person), 1, file);
    }

    fclose(file);
}

void readData(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Person p;
    while (fread(&p, sizeof(struct Person), 1, file) == 1) {
        printf("Name: %s, Age: %d, Phone: %s\n", p.name, p.age, p.phone);
    }

    fclose(file);
}

void swap(struct Person* a, struct Person* b) {
    struct Person temp = *a;
    *a = *b;
    *b = temp;
}

int partition(const char* filename, int low, int high) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Person pivot, temp;
    fseek(file, low * sizeof(struct Person), SEEK_SET);
    fread(&pivot, sizeof(struct Person), 1, file);

    int left = low;
    int right = high;

    while (left < right) {
        while (left <= high) {
            fseek(file, left * sizeof(struct Person), SEEK_SET);
            fread(&temp, sizeof(struct Person), 1, file);
            if (strcmp(temp.name, pivot.name) > 0) break;
            left++;
        }

        while (right >= low) {
            fseek(file, right * sizeof(struct Person), SEEK_SET);
            fread(&temp, sizeof(struct Person), 1, file);
            if (strcmp(temp.name, pivot.name) < 0) break;
            right--;
        }

        if (left < right) {
            swap(&temp, &pivot);

            fseek(file, left * sizeof(struct Person), SEEK_SET);
            fwrite(&temp, sizeof(struct Person), 1, file);

            fseek(file, right * sizeof(struct Person), SEEK_SET);
            fwrite(&pivot, sizeof(struct Person), 1, file);
        }
    }

    fclose(file);
    return right;
}

void quickSort(const char* filename, int low, int high) {
    if (low < high) {
        int pivot = partition(filename, low, high);

        quickSort(filename, low, pivot - 1);
        quickSort(filename, pivot + 1, high);
    }
}

void quickSortWrapper(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    int numEntries = ftell(file) / sizeof(struct Person);
    fclose(file);

    quickSort(filename, 0, numEntries - 1);
}

void binarySearch(const char* filename, const char* searchTerm) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Person p;
    int left = 0, right, mid;
    fseek(file, 0, SEEK_END);
    right = ftell(file) / sizeof(struct Person) - 1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        fseek(file, mid * sizeof(struct Person), SEEK_SET);
        fread(&p, sizeof(struct Person), 1, file);

        int cmp = strcmp(p.name, searchTerm);

        if (cmp == 0) {
            printf("Found at index %d:\n", mid);
            printf("Name: %s, Age: %d, Phone: %s\n", p.name, p.age, p.phone);
            fclose(file);
            return;
        }

        if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    printf("Not found.\n");
    fclose(file);
}

int main() {
    const char* filename = "data.dat";
    long size = MAX_DATA; // Define your desired size
    generateRandomData(filename, size);





    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Display all data\n");
        printf("2. Search by name\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAll data:\n");
                readData(filename);
                break;

            case 2: {
                char searchTerm[50];
                printf("\nEnter search term (name): ");
                scanf("%s", searchTerm);

                binarySearch(filename, searchTerm);
                break;
            }

            case 3:
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}



