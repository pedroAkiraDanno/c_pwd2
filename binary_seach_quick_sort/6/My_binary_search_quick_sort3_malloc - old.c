#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_DATA  20000000              // limit by memory of computer 
#define MAX_ARRAY MAX_DATA







typedef struct {
    char name[50];
    int age;
    char phone[20];
} Person;





void log_details(int count) {
    printf("Log details. Loop count: %d\n", count);
}







void generateRandomPerson(Person* person) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int nameLength = rand() % 10 + 5; // Random name length between 5 and 14 characters
    for (int i = 0; i < nameLength; i++) {
        person->name[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    person->name[nameLength] = '\0';

    person->age = rand() % 50 + 20; // Age between 20 and 70

    char* phones[] = {"555-1234", "555-5678", "555-9876", "555-4321", "555-8765", "555-3456", "555-7890"};
    strcpy(person->phone, phones[rand() % 7]);
}

void generateRandomData(Person* people, int n) {
    for (int i = 0; i < n; i++) {
        generateRandomPerson(&people[i]);
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
        printf("%d. Name: %s, Age: %d, Phone: %s\n", i, people[i].name, people[i].age, people[i].phone);
    }
}

int binarySearch(Person* people, int n, const char* target) {

    int enable_log = 1; // Set to 1 to enable, 0 to disable
    int count = 0;


    int left = 0, right = n - 1;
    while (left <= right) {
        if (enable_log == 1) {
            count++;
        }

        int mid = left + (right - left) / 2;
        int cmp = strcmp(people[mid].name, target);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    if (enable_log == 1) {                
        log_details(count); // Log the loop count
     }


    return -1;
}

void insertRandomData(Person* people, int* n) {
    if (*n < MAX_ARRAY) {  // Ensure we don't exceed array size
        generateRandomPerson(&people[*n]);
        (*n)++;
        sortByNames(people, *n);
    } else {
        printf("Cannot insert more data. Maximum limit reached.\n");
    }
}

int main() {



    srand(time(NULL));
    int n = MAX_DATA; // Change this to the desired initial number of random data
    
    clock_t start, end;
    double cpu_time_used;    

    Person* people = malloc(MAX_DATA * sizeof(Person)); // Dynamically allocate memory
    if (people == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }



    
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
        printf("2. Show index, name, age, and phone\n");
        printf("3. Sort data again\n");
        printf("4. Show all data\n");
        printf("5. random data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:


                printf("Enter name to search: ");
                scanf("%s", target);
                int index = binarySearch(people, n, target);
                if (index != -1) {
                    printf("Found at index %d\n", index);
                    printf("%d. Name: %s, Age: %d, Phone: %s\n", index, people[index].name, people[index].age, people[index].phone);                    
                } else {
                    pr
                    intf("Not found\n");
                }


                                
                break;
            case 2:
                start = clock();

                printAllData(people, n);

                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Node inserted in %f seconds.\n", cpu_time_used);                
                break;
            case 3:
                sortByNames(people, n);
                writeToFile(people, n, "sorted_data.txt");
                printf("Data sorted and written to file.\n");
                break;
            case 4:
                printAllData(people, n);
                break;
            case 5:
                generateRandomData(people, n);
                writeToFile(people, n, "data.txt");
                readFromFile(people, n, "data.txt");
                sortByNames(people, n);
                writeToFile(people, n, "sorted_data.txt");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}







