#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/resource.h>




//#define MAX_RANDOM 1110000000           //about 4GB the limit is the memory you have in your computer 
#define MAX_RANDOM   289999990           //about 4GB the limit is the memory you have in your computer 
#define MAX_SEED     99999999999


//global variable 
int loops = 0; // Added loop counter    to binaryseach()
long loopsLiner = 0; // Added loop counter    to linearsearch() 






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






/*
int linearSearch(int* arr, int size, int target) {
    for (long i = 0; i < size; i++) {
        loopsLiner++;
        if (arr[i] == target) {
            return i; // Return the index where target is found
        }
    }
    return -1; // Return -1 if target is not found
}
*/



//optimization linear search function
int linearSearch(int* arr, int size, int target) {
    for (long i = 0; i < size; i++) {
        loopsLiner++;
        if (arr[i] == target) {
            return i; // Return the index where target is found
        }
        if (arr[i] > target) {
            return -1; // Early termination, target not found
        }
    }
    return -1; // Return -1 if target is not found
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













void timeSearch(int* arr, int size, int target, int (*searchFunction)(int*, int, int)) {
    clock_t start_time, end_time;
    int result;

    // Record the start time
    start_time = clock();

    // Perform the search operation
    result = searchFunction(arr, size, target);

    // Record the end time
    end_time = clock();

    // Calculate the time taken
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the result and time taken
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }

    printf("Time taken: %f seconds\n", time_taken);
}




void printMenu() {
    printf("\nMenu:\n");
    printf("1. Generate and Write Data\n");
    printf("2. Read Data from File\n");
    printf("3. Sort Data\n");
    printf("4. Search (Binary Search)\n");
    printf("5. Search (Linear Search)\n");
    printf("6. Check if Data is Sorted\n");
    printf("7. Convert Binary to Text\n");
    printf("8. Convert Binary to Text (Test)\n");
    printf("9. Measure Memory Usage\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
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
         case 8:
            printf("Testing...\n");
            break;     
        case 9:
            printf("Searching linear...\n");
            break;                                     

        default:
            printf("Invalid parameter!\n");
    }
}






void measureMemory() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld kilobytes\n", usage.ru_maxrss);
}



/*
void getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory usage: %ld kilobytes\n", usage.ru_maxrss);
}
*/



void getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long maxrss_gb = usage.ru_maxrss / (1024 * 1024); // Convert to gigabytes
    printf("Memory usage: %ld gigabytes\n", maxrss_gb);
}





int main() {
    const char* filename = "data.dat";
    int size = MAX_RANDOM; // Change this to the desired size of your data

    clock_t start, end;
    double cpu_time_used;




    srand(time(NULL));

    start = clock();            
    printDefault(1);  
    // Generate and write random data to the file
    generateAndWriteData(filename, size);



    #ifdef __unix__
        measureMemory();
    #else
        printf("This code is designed for Unix/Linux environments.\n");
    #endif



    printDefault(7);  
    const char* textFilenameUn = "unsorted_data.txt";
    convertBinaryToText(filename, textFilenameUn, size);


    printDefault(8); 
    writeBinToTxt(filename, "test_unsorted_data.txt");



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


    #ifdef __unix__
        measureMemory();
    #else
        printf("This code is designed for Unix/Linux environments.\n");
    #endif




    printDefault(4);  
    // Perform quicksort on the data
    quicksort(data, 0, size - 1);


    #ifdef __unix__
        measureMemory();
    #else
        printf("This code is designed for Unix/Linux environments.\n");
    #endif

    
    

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





    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Generete random and sort all data took %f seconds.\n", cpu_time_used);    




    printDefault(5);  
    // Implement binary search on the sorted data
    int target = rand() % MAX_SEED; // Change this to the value you want to search for
    int result = binarySearch(data, size, target);

    if (result != -1) {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d found at index %d\n", target, ++result);
    } else {
        printf("Total loops in this search: %d\n", loops); // Print loop count        
        printf("Element %d not found\n", target);
    }








    printDefault(9);
    //int target = rand() % MAX_SEED; // Change this to the value you want to search for
    int result_Li = linearSearch(data, size, target);
    printf("Linear search... ");
    if (result_Li != -1) {
        printf("Element %d found at index %d\n", target, result_Li);
    } else {
        printf("Element %d not found\n", target);
    }






    // Use binarySearch function with time measurement
    timeSearch(data, size, target, binarySearch);

    // Use linearSearch function with time measurement
    timeSearch(data, size, target, linearSearch);





    #ifdef __unix__
        measureMemory();
    #else
        printf("This code is designed for Unix/Linux environments.\n");
    #endif

    














   int choice;
    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Generate and Write Data
                generateAndWriteData(filename, size);
                break;
            case 2:
                // Read Data from File
                data = readDataFromFile(filename, size);
                break;
            case 3:
                // Sort Data
                quicksort(data, 0, size - 1);
                break;
            case 4:
                        long number = 0;

                        printf("Enter a number to search for: ");
                        scanf("%ld", &number);
                        start = clock();               

                        long result = binarySearch(data, size, number);

                        end = clock();
                        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                        printf("Searching all data took %f seconds.\n", cpu_time_used);                   

                        if(result != -1) {
                            printf("Total loops in this search: %d\n", loops); // Print loop count            
                            printf("Element %ld found at index %ld\n", number, ++result);

                        } else {
                            printf("Total loops in this search: %d\n", loops); // Print loop count            
                            printf("Element %ld not found\n", number);
                        }

                break;
            case 5:
                        // Implement binary search on the sorted data with while 
                        number = 0;
                        printf("Enter a number to search for: ");
                        scanf("%ld", &number);

                        start = clock();               

                        long resultLi = linearSearch(data, size, number);

                        end = clock();
                        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                        printf("Searching all data took %f seconds.\n", cpu_time_used);              

                        if(resultLi != -1) {
                            printf("Total loops in this search: %ld\n", loopsLiner); // Print loop count            
                            printf("Element %ld found at index %ld\n", number, ++resultLi);

                        } else {
                            printf("Total loops in this search: %ld\n", loopsLiner); // Print loop count            
                            printf("Element %ld not found\n", number);
                        }

                break;
            case 6:
                // Check if Data is Sorted
                if (isFileSorted(filenameUn)) {
                    printf("%s is sorted.\n", filenameUn);
                } else {
                    printf("%s is not sorted.\n", filenameUn);
                }
                break;
            case 7:
                // Convert Binary to Text
                const char* textFilename = "sorted_data.txt";
                convertBinaryToText(filename, textFilename, size);
                break;
            case 8:
                // Convert Binary to Text (Test)
                writeBinToTxt(filename, "test_unsorted_data.txt");
                break;
            case 9:
                // Measure Memory Usage
                getMemoryUsage();
                break;
            case 0:
                // Exit
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

























    // Call the function to get memory usage
    getMemoryUsage();





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












/*

why data.dat is less size then sorted_data.txt???

ChatGPT
The reason data.dat is smaller in size compared to sorted_data.txt is likely due to the way integers are stored in binary and text formats.

In data.dat, integers are stored in binary format using the fwrite function, which means each integer takes up a fixed number of bytes (in this case, sizeof(int) bytes). This results in a compact representation of the data.

In sorted_data.txt, integers are stored as text, with each integer represented as a sequence of characters (digits) followed by a newline character. This means each integer takes up more space in the text file compared to the binary file.

Here's an example to illustrate this:

Suppose you have the following integers: 10, 20, 30. In binary format, they might be stored as:



00000000 00000000 00000000 00001010 (10 in binary)
00000000 00000000 00000000 00010100 (20 in binary)
00000000 00000000 00000000 00011110 (30 in binary)




In text format, they would be stored as:



10
20
30




As you can see, the binary format is more space-efficient for storing raw numerical data, while the text format is human-readable but takes up more space due to the additional characters (digits, spaces, and newline characters).















Binary Format (data.dat):

In this format, the numbers are stored using the binary system, which is the base-2 numbering system (0s and 1s).
Each number takes up a fixed amount of space, regardless of its value. In your program, you're using fwrite to write integers directly to the file.
This format is very efficient in terms of file size because it doesn't use any extra characters for formatting. It's like writing numbers in a secret code that only the computer understands.
Example:

If you have the number 10 in binary, it might look something like: 00000000 00000000 00000000 00001010.
Text Format (sorted_data.txt):

In this format, numbers are stored as characters that represent the digits (0-9). Additionally, each number is followed by a newline character to separate them.
This format is less space-efficient because it uses more characters to represent the same numbers. It's similar to writing numbers in a way that humans can easily read.
Example:

If you have the number 10, it will be stored as the characters '1' and '0', followed by a newline character. This takes up more space than the binary representation.
In summary, binary format is a compact way to store numbers directly as computer data, while text format is a more human-readable way that uses more characters for representation. That's why the binary file (data.dat) is smaller in size compared to the text file (sorted_data.txt).
















*/




















