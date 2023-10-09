#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure of a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to search for a node in the BST
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

// Function to find the minimum value node in a subtree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the BST (inorder traversal)
void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

// Function to generate random data and write it to a file
void generateRandomDataToFile(int numData, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        srand(time(NULL));
        for (int i = 0; i < numData; i++) {
            fprintf(file, "%d\n", rand() % 100); // Generates random numbers between 0 and 99
        }
        fclose(file);
    } else {
        printf("Error: Unable to open file %s\n", filename);
    }
}

int main() {
    struct Node* root = NULL;

    // Generate random data and write it to a file
    generateRandomDataToFile(10, "random_data.txt");

    // Read data from file and insert into BST
    FILE* file = fopen("random_data.txt", "r");
    if (file != NULL) {
        int data;
        while (fscanf(file, "%d", &data) == 1) {
            root = insert(root, data);
        }
        fclose(file);
    } else {
        printf("Error: Unable to open file random_data.txt\n");
        return 1;
    }

    int choice, data;
    do {
        printf("\nMENU:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &data);
                struct Node* result = search(root, data);
                if (result != NULL) {
                    printf("Data found in the tree\n");
                } else {
                    printf("Data not found in the tree\n");
                }
                break;
            case 4:
                printf("BST (inorder traversal): ");
                display(root);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
