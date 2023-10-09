#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Function to compare two lines (numbers) as strings
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to perform merge operation
void mergeFiles(FILE *input1, FILE *input2, FILE *output) {
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];

    // Read the first line from each input file
    if (fgets(line1, MAX_LINE_LENGTH, input1) == NULL) {
        while (fgets(line2, MAX_LINE_LENGTH, input2) != NULL) {
            fputs(line2, output);
        }
    }

    if (fgets(line2, MAX_LINE_LENGTH, input2) == NULL) {
        while (fgets(line1, MAX_LINE_LENGTH, input1) != NULL) {
            fputs(line1, output);
        }
    }

    // Merge lines from both files in sorted order
    while (fgets(line1, MAX_LINE_LENGTH, input1) != NULL && fgets(line2, MAX_LINE_LENGTH, input2) != NULL) {
        if (strcmp(line1, line2) < 0) {
            fputs(line1, output);
        } else {
            fputs(line2, output);
        }
    }

    // Copy any remaining lines from input1
    while (fgets(line1, MAX_LINE_LENGTH, input1) != NULL) {
        fputs(line1, output);
    }

    // Copy any remaining lines from input2
    while (fgets(line2, MAX_LINE_LENGTH, input2) != NULL) {
        fputs(line2, output);
    }
}

// Function to perform external merge sort
void externalMergeSort(FILE *input, FILE *output) {
    char *buffer[MAX_LINE_LENGTH];
    int bufferSize = 0;
    int numFiles = 0;

    while (1) {
        // Read lines into the buffer until it's full
        while (bufferSize < MAX_LINE_LENGTH && fgets(buffer[bufferSize], MAX_LINE_LENGTH, input)) {
            bufferSize++;
        }

        // If the buffer is empty, we're done
        if (bufferSize == 0) {
            break;
        }

        // Sort the lines in the buffer
        qsort(buffer, bufferSize, sizeof(char *), compare);

        // Create a temporary file for writing the sorted lines
        char tempFileName[20];
        sprintf(tempFileName, "temp%d.txt", numFiles);
        numFiles++;

        FILE *tempFile = fopen(tempFileName, "w");
        if (tempFile == NULL) {
            perror("Error creating temporary file");
            exit(EXIT_FAILURE);
        }

        // Write the sorted lines to the temporary file
        for (int i = 0; i < bufferSize; i++) {
            fputs(buffer[i], tempFile);
        }

        fclose(tempFile);

        // Merge the temporary file with the output file
        FILE *tempInput = fopen(tempFileName, "r");
        if (tempInput == NULL) {
            perror("Error opening temporary file for reading");
            exit(EXIT_FAILURE);
        }

        mergeFiles(output, tempInput, input);

        fclose(tempInput);

        // Clean up the temporary file
        remove(tempFileName);

        // Reset the buffer
        bufferSize = 0;
    }
}

int main() {
    FILE *input = fopen("data.txt", "r");
    FILE *output = fopen("sorted_data.txt", "w");

    if (input == NULL || output == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    externalMergeSort(input, output);

    fclose(input);
    fclose(output);

    printf("External merge sort completed.\n");

    return 0;
}













/*






rm * -fr


vi test.c 


gcc test.c -o test

./test



*/


































