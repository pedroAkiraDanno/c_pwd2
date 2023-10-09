#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


//#define MAX_RANDOM 400000000            // 3GB, the limit is the memory in your computer 
#define MAX_RANDOM 200000000   
//#define MAX_SEED   900000
#define MAX_SEED   900000000                   





void generateRandomData(long* arr, long size) {
    for(long i = 0; i < size; i++) {
        arr[i] = rand() % MAX_SEED;
                          
    }
}

void writeToFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(arr, sizeof(long), size, file);
    fclose(file);
}

void readFromFile(long* arr, long size, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fread(arr, sizeof(long), size, file);
    fclose(file);
}

void quicksort(long* arr, long left, long right) {
    if(left < right) {
        long pivot = arr[right];
        long i = left - 1;
        for(long j = left; j <= right - 1; j++) {
            if(arr[j] <= pivot) {
                i++;
                long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        long temp = arr[i+1];
        arr[i+1] = arr[right];
        arr[right] = temp;

        long partition = i + 1;

        quicksort(arr, left, partition - 1);
        quicksort(arr, partition + 1, right);
    }
}

long binarySearch(long* arr, long size, long target) {
    long left = 0;
    long right = size - 1;
    while(left <= right) {
        long mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            return mid;
        }
        if(arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
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










int is_sorted(long* arr, long size) {
    for(long i = 1; i < size; i++) {
        if(arr[i] < arr[i-1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}





void countOccurrences(long* arr, long size) {
    int* counts = (int*)calloc(MAX_SEED, sizeof(int));

    if (counts == NULL) {
        perror("Error allocating memory for counts");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < size; i++) {
        counts[arr[i]]++;
    }

    for (long i = 0; i < MAX_SEED; i++) {
        if (counts[i] > 0) {
            printf("Number %ld appeared %d times\n", i, counts[i]);
        }
    }

    free(counts);
}





long* deleteDuplicates(long* arr, long size, long* newSize) {
    int* counts = (int*)calloc(MAX_SEED, sizeof(int));

    if (counts == NULL) {
        perror("Error allocating memory for counts");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < size; i++) {
        counts[arr[i]]++;
    }

    // Count unique elements
    *newSize = 0;
    for (long i = 0; i < MAX_SEED; i++) {
        if (counts[i] > 0) {
            (*newSize)++;
        }
    }

    // Create a new array with unique elements
    long* uniqueArr = (long*)malloc(*newSize * sizeof(long));
    if (uniqueArr == NULL) {
        perror("Error allocating memory for uniqueArr");
        exit(EXIT_FAILURE);
    }

    long currentIndex = 0;
    for (long i = 0; i < MAX_SEED; i++) {
        if (counts[i] > 0) {
            uniqueArr[currentIndex++] = i;
        }
    }

    free(counts);

    return uniqueArr;
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
            printf("Bin file to txt Writing...\n");
            break;                       

        default:
            printf("Invalid parameter!\n");
    }
}
















int main() {
    long size = MAX_RANDOM;
    long* data = (long*)malloc(size * sizeof(long));
    if (data == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }


    printDefault(1);
    generateRandomData(data, size);
    printDefault(2);    
    writeToFile(data, size, "data.bin");


    printDefault(6);
     // After sorting the data
    if(is_sorted(data, size)) {
        printf("The data is sorted.\n");
    } else {
        printf("The data is not sorted.\n");
    }


    long newSize;
    long* uniqueData = deleteDuplicates(data, size, &newSize);
    

    
    //countOccurrences(uniqueData, newSize);
    //countOccurrences(data, newSize);



    printDefault(3);
    readFromFile(data, size, "data.bin");

    printDefault(4);
    quicksort(data, 0, size - 1);
    printDefault(2);    
    writeToFile(data, size, "sorted_data.bin");



    printDefault(7);
    // Write binary to text
    writeBinToTxt("sorted_data.bin", "sorted_data.txt");



    printDefault(6);
    // After sorting the data
    if(is_sorted(data, size)) {
        printf("The data is sorted.\n");
    } else {
        printf("The data is not sorted.\n");
    }







    printDefault(4);
    long target = 420000;
    long result = binarySearch(data, size, target);

    if(result != -1) {
        printf("Element %ld found at index %ld\n", target, result);
    } else {
        printf("Element %ld not found\n", target);
    }













    // Implement binary search on the sorted data with while 
    long number = 0;
    long searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);

         long result = binarySearch(data, size, number);

        if(result != -1) {
            printf("Element %ld found at index %ld\n", number, result);
        } else {
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%ld", &searchAgain);
    }

















    free(data);

    return 0;
}







/*








I understand your concern. To avoid potential segmentation faults when working with a large amount of data, it's important to be mindful of memory allocation and deallocation. Additionally, using dynamic memory allocation functions like malloc and ensuring proper error handling is crucial.

Here is a revised version of the C program, with added error handling for memory allocation and file operations:






In this revised version, I've added error handling for memory allocation and file operations. This should help in avoiding segmentation faults, especially when working with large amounts of data.





















mkdir /root/c

cd /root/c 










rm * -rf 

vi test.c

gcc test.c -o test

./test














*/

























