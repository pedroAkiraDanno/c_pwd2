#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>



#define MAX_RANDOM 100000          //   time: 2 minutes         size of files: 782K
//#define MAX_RANDOM 1000
#define MAX_SEED   10000





void printDefault(int parameter) {
    switch (parameter) {
        case 1:
            printf("Generating data...\n");
            break;
        case 2:
            printf("Writing to file...\n");
            break;
        case 3:
            printf("Read to file...\n");
            break;            
        case 4:
            printf("Searching...\n");
            break;

        default:
            printf("Invalid parameter!\n");
    }
}





typedef struct Node {
    long data;
    struct Node* next;
} Node;

Node* createNode(long data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, long data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void writeToFile(Node* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while (head != NULL) {
        fwrite(&head->data, sizeof(long), 1, file);
        head = head->next;
    }
    fclose(file);
}

Node* readFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Node* head = NULL;
    long data;
    while (fread(&data, sizeof(long), 1, file) == 1) {
        insertNode(&head, data);
    }
    fclose(file);
    return head;
}

void quicksort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    long pivot = head->data;
    Node* less = NULL;
    Node* equal = NULL;
    Node* greater = NULL;

    Node* current = head;
    while (current != NULL) {
        if (current->data < pivot) {
            insertNode(&less, current->data);
        } else if (current->data == pivot) {
            insertNode(&equal, current->data);
        } else {
            insertNode(&greater, current->data);
        }
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    quicksort(less);
    quicksort(greater);

    head = NULL;
    if (less != NULL) {
        head = less;
        current = less;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = equal;
    } else {
        head = equal;
    }

    current = equal;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = greater;
}

void search(Node* head, long target) {
    long count = 0;


    Node* current = head;
    while (current != NULL && current->data != target) {
        current = current->next;
        count++;
    }


    if (current != NULL) {
        printf("Element %ld found\n", target);
    } else {
        printf("Element %ld not found\n", target);
    }


    printf("Count Loops to find target:  %ld \n", count);    


}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}




void writeBinToTxt(const char* binFilename, const char* txtFilename) {
    FILE* binFile = fopen(binFilename, "rb");
    FILE* txtFile = fopen(txtFilename, "w");

    if (binFile == NULL || txtFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    long data;
    while (fread(&data, sizeof(long), 1, binFile) == 1) {
        fprintf(txtFile, "%ld\n", data);
    }

    fclose(binFile);
    fclose(txtFile);
}







int main() {
    srand(time(NULL));

    Node* list = NULL;

    printDefault(1);
    for (int i = 0; i < MAX_RANDOM; i++) {
        insertNode(&list, rand() % MAX_SEED);
    }


    printDefault(2);
    writeToFile(list, "data.bin");

    freeList(list);

    printDefault(3);
    list = readFromFile("data.bin");

    //quicksort(list);

    //writeToFile(list, "sorted_data.bin");

    printDefault(4);
    long target = rand() % MAX_SEED;
    search(list, target);



    // Write binary to text
    writeBinToTxt("data.bin", "data.txt");




    freeList(list);

    return 0;
}







/*


programing in c in file in linux:
Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
NO USE ARRAY 




ChatGPT
If you want to perform sorting and searching operations without using an array, you can use a linked list. Here's an example C program that accomplishes this:





In this program, a linked list is used instead of an array to store and manipulate data. The functions insertNode, writeToFile, readFromFile, quicksort, and search operate on this linked list. This program generates random data, writes it to a file, performs quicksort, writes the sorted data back to the file, and implements a search operation.









*/








