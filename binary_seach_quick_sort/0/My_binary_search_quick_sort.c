#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>


#define SIZE_MAX 1000000
#define SEED_MAX 1000000









// Function to swap two long integers
void swap(long* a, long* b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array for quicksort
long partition(long arr[], long low, long high) {
    long pivot = arr[high];
    long i = (low - 1);

    for (long j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to implement quicksort
void quicksort(long arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}












// Function to perform binary search
/*
long binarySearch(long arr[], long left, long right, long target) {

    while (left <= right) {
        long mid = left + (right - left) / 2;
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



// Function to perform binary search
long binarySearch(long arr[], long left, long right, long target) {

    int enable_log = 1; // Set to 1 to enable, 0 to disable
    int count = 0;


    while (left <= right) {
        if (enable_log == 1) {
            count++;
            //printf("test...");
        }

        long mid = left + (right - left) / 2;
        if (arr[mid] == target){
            if (enable_log == 1) {
                log_details(count); // Log the loop count
            }

            return mid;
        }

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }


    if (enable_log == 1) {                
        log_details(count); // Log the loop count
    }

    return -1; // Element not found
}













bool isFileSorted(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    long prev, current;
    int first = 1;

    while (fscanf(file, "%ld", &current) == 1) {
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





void displaySortedDataFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    long value;

    while (fscanf(file, "%ld", &value) == 1) {
        printf("%ld\n", value);
    }

    fclose(file);
}



// Log to Loop/Reads count in Binary Search 
void log_details(int count) {
    printf("Log details. Loop/Reads count: %d\n", count);
}







int main() {

    clock_t start, end;
    double cpu_time_used;

    srand(time(NULL));
    long n = SIZE_MAX; // Change this value for the desired number of elements
    long data[n];


    // Generate random data and write it to a file
    FILE* file = fopen("random_data.txt", "w");
    for (long i = 0; i < n; i++) {
        data[i] = rand();
        fprintf(file, "%ld\n", data[i]);
    }
    fclose(file);




    // Read data from the file
    file = fopen("random_data.txt", "r");
    for (long i = 0; i < n; i++) {
        fscanf(file, "%ld", &data[i]);
    }
    fclose(file);





    start = clock();
    // Perform quicksort
    quicksort(data, 0, n - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Quicksort took %f seconds.\n", cpu_time_used);
        





    // Write the sorted data back to the file
    file = fopen("sorted_data.txt", "w");
    for (long i = 0; i < n; i++) {
        fprintf(file, "%ld\n", data[i]);
    }
    fclose(file);




    // Check is sorted 
    if (isFileSorted("sorted_data.txt")) {
        printf("File is sorted.\n");
    } else {
        printf("File is not sorted.\n");
    }




    // Perform binary search
    long target = data[rand() % n]; // Choose a random target value
    long result = binarySearch(data, 0, n - 1, target);


    if (result != -1) {
        printf("Target %ld found at index %ld.\n", target, ++result);         // +1 bacause array start with 0
    } else {
        printf("Target %ld not found.\n", target);
    }






    // Perform binary search with while 
    long number = 0;
    long searchAgain = 1;

    while (searchAgain) {
         printf("Enter a number to search for: ");
         scanf("%ld", &number);                                     

         long result = binarySearch(data, 0, n - 1, number);
               

        if(result != -1) {
            printf("Element %ld found at index %ld\n", number, ++result);           // +1 bacause array start with 0
        } else {
            printf("Element %ld not found\n", number);
        }

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%ld", &searchAgain);
    }









    const char* filename = "sorted_data.txt";
    // Display all sorted data from the file
    //displaySortedDataFromFile(filename);










    return 0;
}










/*

To perform quicksort on a file containing random data using C, and then conduct a binary search within the sorted file, you can follow these steps:

Generate random data and write it to a file.
Read the data from the file.
Perform quicksort on the data.
Write the sorted data back to the file.
Implement binary search on the sorted data.







mkdir /root/c 

cd /root/c 

rm * -fr 

vi test.c 

gcc test.c -o test

./test













This program generates random long integers, sorts them using quicksort, writes the sorted data to a file, and then performs a binary search for a randomly chosen target value within the sorted data. You can adjust the n variable to control the number of elements in your data.





















*/












