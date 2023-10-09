#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>



//#define MAX_RANDOM 1110000000           //about 4GB the limit is the memory you have in your computer 
#define MAX_RANDOM   289999990           //about 4GB the limit is the memory you have in your computer 
#define MAX_SEED     9999999999


//global variable 
int loops = 0; // Added loop counter    to binaryseach()






// Function to generate random data and write it to a file
void generateAndWriteData(const char* filename, int size) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        //int random = rand() % 10000; // Generate a random number between 0 and 9999
        int random = rand() % MAX_SEED; // Generate a random number between 0 and 10.000.000       
        
        fwrite(&random, sizeof(int), 1, file);
    }

    fclose(file);
}




// Function to read data from the file
int* readDataFromFile(const char* filename, int size) {
    int* data = (int*)malloc(size * sizeof(int));
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fread(data, sizeof(int), size, file);

    fclose(file);
    return data;
}




// Function to perform quicksort
void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int pivotIndex = i + 1;

        quicksort(arr, left, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, right);
    }
}








// more performance bacause the pivot
// Function to perform quicksort
/*
void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[left + (right - left) / 2];

        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int pivotIndex = i + 1;

        quicksort(arr, left, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, right);
    }
}
*/













// Function to implement binary search
/*
int binarySearch(int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // Element not found
}
*/




// Function to implement binary search
int binarySearch(int* arr, int size, int target) {




    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        loops++; // Increment loop counter        

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;



    }

    return -1; // Element not found
}














void convertBinaryToText(const char* binaryFilename, const char* textFilename, int size) {
    FILE* binaryFile = fopen(binaryFilename, "rb");
    if (binaryFile == NULL) {
        perror("Error opening binary file");
        exit(EXIT_FAILURE);
    }

    FILE* textFile = fopen(textFilename, "w");
    if (textFile == NULL) {
        perror("Error opening text file");
        fclose(binaryFile);
        exit(EXIT_FAILURE);
    }

    int value;
    while (fread(&value, sizeof(int), 1, binaryFile) == 1) {
        fprintf(textFile, "%d\n", value);
    }

    fclose(binaryFile);
    fclose(textFile);
}










bool isFileSorted(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    int prev, current;
    int first = 1;

    while (fscanf(file, "%d", &current) == 1) {
        if (!first && current < prev) {
            fclose(file);
            return false;
        }
        first = 0;
        prev = current;
    }

    fclose(file);
    return true;
}






void printDefault(int parameter) {
    switch (parameter) {
        case 1:
            printf("Generating data...\n");
            break;
        case 2:
            printf("Writing...\n");
            break;                
        case 3:
            printf("Read to file...\n");
            break;            
         case 4:
            printf("Sorting...\n");
            break;
        case 5:
            printf("Searching...\n");
            break;
         case 6:
            printf("Checking if is sorting...\n");
            break;         
         case 7:
            printf("Bin to Txt Wrting...\n");
            break;                        

        default:
            printf("Invalid parameter!\n");
    }
}









int main() {
    const char* filename = "data.dat";
    int size = MAX_RANDOM; // Change this to the desired size of your data

    srand(time(NULL));

    printDefault(1);  
    // Generate and write random data to the file
    generateAndWriteData(filename, size);



    printDefault(7);  
    const char* textFilenameUn = "unsorted_data.txt";
    convertBinaryToText(filename, textFilenameUn, size);



    printDefault(3);  
    // Read the data from the file
    int* data = readDataFromFile(filename, size);


    printDefault(6);  
    const char* filenameUn = "unsorted_data.txt";
    if (isFileSorted(filenameUn)) {
        printf("%s is sorted.\n", filenameUn);
    } else {
        printf("%s is not sorted.\n", filenameUn);
    }





    printDefault(4);  
    // Perform quicksort on the data
    quicksort(data, 0, size - 1);

    printDefault(2);  
    // Write the sorted data back to the file
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(data, sizeof(int), size, file);

    fclose(file);




    printDefault(7);  
    const char* textFilename = "sorted_data.txt";

    convertBinaryToText(filename, textFilename, size);



    printDefault(6);  
    const char* filename2 = "sorted_data.txt";
    if (isFileSorted(filename2)) {
        printf("%s is sorted.\n", filename2);
    } else {
        printf("%s is not sorted.\n", filename2);
    }









    printDefault(5);  
    // Implement binary search on the sorted data
    int target = 42; // Change this to the value you want to search for
    int result = binarySearch(data, size, target);

    if (result != -1) {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d found at index %d\n", target, ++result);
    } else {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d not found\n", target);
    }
















    // Implement binary search on the sorted data with while 
    long number = 0;
    long searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);

         long result = binarySearch(data, size, number);

        if(result != -1) {
            printf("Total loops in this search: %d\n", loops); // Print loop count            
            printf("Element %ld found at index %ld\n", number, ++result);

        } else {
            printf("Total loops in this search: %d\n", loops); // Print loop count            
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%ld", &searchAgain);
    }





    // Free allocated memory
    free(data);

    return 0;
}









/*




programing in c in linux in file 
Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.
use malloc 

ChatGPT
Sure! I can help you with that. Below is a C program that does what you described:










This program generates random data, writes it to a file, reads it back, performs quicksort, writes the sorted data back to the file, and then implements a binary search on the sorted data. It uses malloc to dynamically allocate memory for the array.

Please make sure to compile this program with a C compiler, and you may need to link the math library using -lm depending on your compiler and platform. For example, you can compile it using gcc:







*/





