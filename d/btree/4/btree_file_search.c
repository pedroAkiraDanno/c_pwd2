#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "data.txt"

// Structure for a person's information
struct Person {
    char name[50];
    int age;
    char phone[15];
};

// Structure for a node in the binary search tree
struct TreeNode {
    struct Person data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(struct Person data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a person into the binary search tree
struct TreeNode* insert(struct TreeNode* root, struct Person data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data.age < root->data.age) {
        root->left = insert(root->left, data);
    } else if (data.age > root->data.age) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to print the binary search tree in in-order
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Name: %s, Age: %d, Phone: %s\n", root->data.name, root->data.age, root->data.phone);
        inorderTraversal(root->right);
    }
}

// Function to search for a person by age in the binary search tree
struct TreeNode* search(struct TreeNode* root, int key) {
    if (root == NULL || root->data.age == key) {
        return root;
    }

    if (key < root->data.age) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

int main() {
    struct TreeNode* root = NULL;
    FILE* dataFile = fopen(DATA_FILE, "a+");

    if (dataFile == NULL) {
        perror("Error opening data file");
        exit(EXIT_FAILURE);
    }

    char response;
    do {
        struct Person newPerson;
        printf("Enter the name of the person: ");
        scanf("%s", newPerson.name);
        printf("Enter the age of the person: ");
        scanf("%d", &newPerson.age);
        printf("Enter the phone number: ");
        scanf("%s", newPerson.phone);

        fprintf(dataFile, "%s,%d,%s\n", newPerson.name, newPerson.age, newPerson.phone);
        root = insert(root, newPerson);

        printf("Do you want to insert more (y/n)? ");
        scanf(" %c", &response);
    } while (response == 'y' || response == 'Y');

    printf("Data inserted successfully.\n");

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Print all data entries\n");
        printf("2. Search for a person by age\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("All data entries:\n");
                inorderTraversal(root);
                break;

            case 2:
                {
                    int age;
                    printf("Enter an age to search for: ");
                    scanf("%d", &age);
                    struct TreeNode* result = search(root, age);
                    if (result != NULL) {
                        printf("Person found:\n");
                        printf("Name: %s, Age: %d, Phone: %s\n", result->data.name, result->data.age, result->data.phone);
                    } else {
                        printf("Person not found.\n");
                    }
                    break;
                }

            case 3:
                fclose(dataFile);
                // Free allocated memory and exit
                free(root);
                exit(EXIT_SUCCESS);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

































/*

In this program:

Data is stored in a text file ("data.txt") in a CSV format.
A binary search tree (BST) is used to store person data with fields for name, age, and phone number.
You can insert persons with name, age, and phone number, print all data entries, search for persons by age, and exit the program using a menu-driven interface.
Compile and run the program in a Linux environment:

bash
Copy code
gcc btree_file_search.c -o btree_file_search
./btree_file_search
You can follow the menu options to insert persons, print all data entries, search for persons by age, and exit the program.






rm * -fr 

vi btree_file_search.c


gcc btree_file_search.c -o btree_file_search
./btree_file_search



*/










