#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>





#define MAX_RANDOM 100000000  //





typedef struct Node {
    char name[30];
    int age;
    char phone[15];
    long offset;
    struct Node *left;
    struct Node *right;
} Node;

char* generateRandomName() {
    char *characters = "abcdefghijklmnopqrstuvwxyz";
    char *name = malloc(9 * sizeof(char));

    for (int i = 0; i < 7; i++) {
        name[i] = characters[rand() % 26];
    }
    name[7] = '\0';

    return name;
}

int generateRandomAge() {
    return rand() % 50 + 20; // Generates ages between 20 and 69
}

char* generateRandomPhone() {
    char *phone = malloc(13 * sizeof(char));

    sprintf(phone, "04%d-%d%d%d-%d%d%d", rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    return phone;
}

void insert(Node **root, char *name, int age, char *phone, long offset) {
    if (*root == NULL) {
        *root = (Node *)malloc(sizeof(Node));
        strcpy((*root)->name, name);
        (*root)->age = age;
        strcpy((*root)->phone, phone);
        (*root)->offset = offset;
        (*root)->left = (*root)->right = NULL;
    } else if (strcmp(name, (*root)->name) < 0) {
        insert(&((*root)->left), name, age, phone, offset);
    } else if (strcmp(name, (*root)->name) > 0) {
        insert(&((*root)->right), name, age, phone, offset);
    }
}

Node *search(Node *root, char *name) {
    if (root == NULL || strcmp(name, root->name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    }

    return search(root->right, name);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Name: %s, Age: %d, Phone: %s, Offset: %ld\n", root->name, root->age, root->phone, root->offset);
        inorder(root->right);
    }
}

void saveToFile(Node *root, FILE *file) {
    if (root != NULL) {
        fwrite(root, sizeof(Node), 1, file);
        saveToFile(root->left, file);
        saveToFile(root->right, file);
    }
}

Node *loadFromFile(FILE *file) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (fread(node, sizeof(Node), 1, file) != 1) {
        free(node);
        return NULL;
    }

    node->left = loadFromFile(file);
    node->right = loadFromFile(file);
    return node;
}

void printTimeTaken(clock_t start, clock_t end, char *operation) {
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s took %.4f seconds.\n", operation, timeTaken);
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    Node *root = NULL;

    int choice, age;
    char name[30], phone[15];
    clock_t start, end;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Show All\n");
        printf("4. Generate Random Data\n");
        printf("5. Save to File\n");  // Added option
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter phone: ");
                scanf("%s", phone);

                start = clock();
                long offset = ftell(stdout);
                insert(&root, name, age, phone, offset);
                printTimeTaken(start, clock(), "Insertion");
                break;

            case 2:
                printf("Enter name to search: ");
                scanf("%s", name);

                start = clock();
                Node *result = search(root, name);
                end = clock();

                if (result != NULL) {
                    printf("Data found!\n");
                    printf("Name: %s, Age: %d, Phone: %s, Offset: %ld\n", result->name, result->age, result->phone, result->offset);
                } else {
                    printf("Data not found.\n");
                }
                printTimeTaken(start, end, "Search");
                break;

            case 3:
                printf("All nodes:\n");
                start = clock();
                inorder(root);
                printTimeTaken(start, clock(), "Display");
                break;

            case 4:
                printf("Generating random data...\n");

                start = clock();
                for (int i = 0; i < MAX_RANDOM; i++) {
                    char *randomName = generateRandomName();
                    int randomAge = generateRandomAge();
                    char *randomPhone = generateRandomPhone();


                    offset = ftell(stdout);
                    insert(&root, randomName, randomAge, randomPhone, offset);

                    free(randomName);
                    free(randomPhone);
                }

                printTimeTaken(start, clock(), "Random Data Generation");
                break;

            case 5: // Renumbered option
                printf("Saving tree to file...\n");
                FILE *file = fopen("tree_data.bin", "wb");
                if (file == NULL) {
                    printf("Error opening file for writing.\n");
                    break;
                }
                start = clock();
                saveToFile(root, file);
                fclose(file);
                printTimeTaken(start, clock(), "Save to File");
                break;

            case 6: // Renumbered option
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
