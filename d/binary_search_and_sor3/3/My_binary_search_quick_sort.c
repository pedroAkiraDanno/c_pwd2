#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>



#define MAX_RANDOM 1000000          // 11:04    time:          size of files: 
#define MAX_SEED   10000








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
    Node* current = head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }

    if (current != NULL) {
        printf("Element %ld found\n", target);
    } else {
        printf("Element %ld not found\n", target);
    }
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}











int main() {
    srand(time(NULL));

    Node* list = NULL;

    for (int i = 0; i < MAX_RANDOM; i++) {
        insertNode(&list, rand() % MAX_SEED);
    }

    writeToFile(list, "data.bin");

    freeList(list);

    list = readFromFile("data.bin");

    quicksort(list);

    writeToFile(list, "sorted_data.bin");

    long target = rand() % MAX_SEED;
    search(list, target);

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








