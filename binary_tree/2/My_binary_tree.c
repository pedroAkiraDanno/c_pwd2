#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATA 10000




// Define the structure for a node in the binary search tree
typedef struct TreeNode {
    char name[20];
    int age;
    char phone[15];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode *createNode(char name[], int age, char phone[]) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    newNode->age = age;
    strcpy(newNode->phone, phone);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
TreeNode *insert(TreeNode *root, char name[], int age, char phone[]) {
    if (root == NULL) {
        return createNode(name, age, phone);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, age, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, age, phone);
    }
    return root;
}

// Function to search for a node in the BST
TreeNode *search(TreeNode *root, char name[]) {
    if (root == NULL || strcmp(name, root->name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    }
    return search(root->right, name);
}

// Function to display all nodes in the BST (in-order traversal)
void display(TreeNode *root) {
    if (root != NULL) {
        display(root->left);
        printf("Name: %s, Age: %d, Phone: %s\n", root->name, root->age, root->phone);
        display(root->right);
    }
}

// Function to generate random names
char *generateRandomName() {
    char *name = (char *)malloc(11 * sizeof(char)); // Maximum 10 characters for the name
    for (int i = 0; i < 10; i++) {
        name[i] = 'a' + rand() % 26; // Generates random lowercase letters
    }
    name[10] = '\0';
    return name;
}

// Function to generate random data and write it to a file
void generateRandomDataToFile(char *filename, long numRecords) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    srand(time(NULL)); // Seed the random number generator

    for (long i = 0; i < numRecords; i++) {
        char *name = generateRandomName();
        int age = rand() % 50 + 20; // Generates random age between 20 and 69
        char phone[15];
        sprintf(phone, "555-%04d", rand() % 10000); // Generates random 4-digit phone number starting with "555-"
        fprintf(file, "%s,%d,%s\n", name, age, phone);
        free(name);
    }

    fclose(file);
}

int main() {
    TreeNode *root = NULL;
    char filename[] = "records.txt";

    // Generate random data and write it to a file
    generateRandomDataToFile(filename, MAX_DATA);

    // Read data from the file and insert into the BST
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char name[20], phone[15];
    int age;
    while (fscanf(file, "%19[^,],%d,%14[^\n]\n", name, &age, phone) == 3) {
        root = insert(root, name, age, phone);
    }

    fclose(file);

    // Menu for user interaction
    int choice;
    char searchName[20];
    do {
        printf("\nMENU:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name, age, and phone (e.g., JohnDoe 30 555-1234): ");
                scanf("%19s %d %14s", name, &age, phone);
                root = insert(root, name, age, phone);
                break;
            case 2:
                printf("Enter name to delete: ");
                scanf("%19s", name);
                // Implement delete operation
                // You can add the delete function similar to the insert and search functions.
                break;
            case 3:
                printf("Enter name to search: ");
                scanf("%19s", searchName);
                TreeNode *result = search(root, searchName);
                if (result != NULL) {
                    printf("Name: %s, Age: %d, Phone: %s\n", result->name, result->age, result->phone);
                } else {
                    printf("Record not found.\n");
                }
                break;
            case 4:
                display(root);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free allocated memory
    // You should implement a function to free the BST nodes.
    return 0;
}
