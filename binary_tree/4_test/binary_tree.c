#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int age;
    char phone[15];
} NodeData;

typedef struct TreeNode {
    NodeData data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* insertNode(TreeNode* root, NodeData data) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    int cmp = strcmp(data.name, root->data.name);

    if (cmp < 0) {
        root->left = insertNode(root->left, data);
    } else if (cmp > 0) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

NodeData generateRandomData() {
    NodeData newData;
    char charset[] = "abcdefghijklmnopqrstuvwxyz";
    size_t name_len = 10 + rand() % 40;
    for (size_t i = 0; i < name_len; i++) {
        newData.name[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    newData.name[name_len] = '\0';
    newData.age = rand() % 80 + 18; 
    sprintf(newData.phone, "%d-%04d", rand() % 1000, rand() % 10000);
    return newData;
}

TreeNode* searchByName(TreeNode* root, const char* name) {
    if (root == NULL || strcmp(root->data.name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->data.name) < 0) {
        return searchByName(root->left, name);
    }

    return searchByName(root->right, name);
}

void displayMenu() {
    printf("\nMenu\n");
    printf("1. Insert\n");
    printf("2. Generate Random Data\n");
    printf("3. Search by Name\n");
    printf("4. Show All Data\n");
    printf("5. Insert with User Input\n");
    printf("6. Quit\n");
}

void saveTreeToFile(TreeNode* root, FILE* file) {
    if (root != NULL) {
        fwrite(&root->data, sizeof(NodeData), 1, file);
        saveTreeToFile(root->left, file);
        saveTreeToFile(root->right, file);
    }
}

TreeNode* loadTreeFromFile(FILE* file) {
    NodeData data;
    if (fread(&data, sizeof(NodeData), 1, file) == 1) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = loadTreeFromFile(file);
        newNode->right = loadTreeFromFile(file);
        return newNode;
    }
    return NULL;
}

void cleanup(TreeNode* root) {
    if (root != NULL) {
        cleanup(root->left);
        cleanup(root->right);
        free(root);
    }
}

void displayAllData(TreeNode* root) {
    if (root != NULL) {
        printf("Name: %s, Age: %d, Phone: %s\n", root->data.name, root->data.age, root->data.phone);
        displayAllData(root->left);
        displayAllData(root->right);
    }
}

int main() {
    TreeNode* root = NULL;
    clock_t start, end;
    double cpu_time_used;

    int choice;
    char searchName[50];

    srand(time(NULL));

    FILE* file = fopen("data.dat", "ab+"); 

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    root = loadTreeFromFile(file);

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                NodeData newData = generateRandomData();
                start = clock();
                root = insertNode(root, newData);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Node inserted in %f seconds.\n", cpu_time_used);
                break;
            }
            case 2: {
                int quantity;
                printf("Enter the quantity of random data to generate: ");
                scanf("%d", &quantity);
                start = clock();
                for (int i = 0; i < quantity; i++) {
                    NodeData newData = generateRandomData();
                    root = insertNode(root, newData);
                }
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("%d nodes inserted in %f seconds.\n", quantity, cpu_time_used);
                break;
            }
            case 3:
                printf("Enter the name to search: ");
                scanf(" %[^\n]s", searchName);
                start = clock();
                TreeNode* result = searchByName(root, searchName);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                if (result != NULL) {
                    printf("Found: %s, Age: %d, Phone: %s\n", result->data.name, result->data.age, result->data.phone);
                } else {
                    printf("Not found.\n");
                }
                printf("Search completed in %f seconds.\n", cpu_time_used);
                break;
            case 4:
                start = clock();
                displayAllData(root);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Displaying all data took %f seconds.\n", cpu_time_used);
                break;
            case 5: {
                NodeData newData;
                printf("Enter name: ");
                scanf(" %[^\n]s", newData.name);
                printf("Enter age: ");
                scanf("%d", &newData.age);
                printf("Enter phone (format: xxxx-yyyy): ");
                scanf(" %s", newData.phone);
                start = clock();
                root = insertNode(root, newData);
                end = clock();
                cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Node inserted in %f seconds.\n", cpu_time_used);
                break;
            }
            case 6:
                // Save the tree to the file before quitting
                fclose(file);
                file = fopen("data.dat", "wb"); 
                saveTreeToFile(root, file);
                fclose(file);

                cleanup(root);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
