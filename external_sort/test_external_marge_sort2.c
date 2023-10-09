#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define BLOCK_SIZE 4

void generateTestData(const char *filename, int numElements) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    for (int i = numElements; i > 0; i--) {
        fwrite(&i, sizeof(int), 1, file);
    }
    fclose(file);
}

void readBlock(FILE *file, int *buffer, int blockSize, int *logicalReads, int *physicalReads) {
    *logicalReads += 1;
    *physicalReads += fread(buffer, sizeof(int), blockSize, file);
}

void writeBlock(FILE *file, int *buffer, int blockSize) {
    fwrite(buffer, sizeof(int), blockSize, file);
}

void displayData(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    int value;
    printf("Data: ");
    while (fread(&value, sizeof(int), 1, file)) {
        printf("%d ", value);
    }
    printf("\n");

    fclose(file);
}

void externalMergeSort(const char *inputFile, const char *outputFile, const char *sortedFile) {
    FILE *input = fopen(inputFile, "rb");
    FILE *output = fopen(outputFile, "wb");
    FILE *sorted = fopen(sortedFile, "wb");

    if (input == NULL || output == NULL || sorted == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    int *buffer = malloc(BLOCK_SIZE * sizeof(int));
    if (buffer == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int logicalReads = 0;
    int physicalReads = 0;

    int numBlocks = 0;
    while (!feof(input)) {
        readBlock(input, buffer, BLOCK_SIZE, &logicalReads, &physicalReads);
        numBlocks++;
    }

    rewind(input);

    int *mergeBuffer = malloc(numBlocks * sizeof(int));
    if (mergeBuffer == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int *blockIndexes = malloc(numBlocks * sizeof(int));
    if (blockIndexes == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numBlocks; i++) {
        readBlock(input, buffer, BLOCK_SIZE, &logicalReads, &physicalReads);
        mergeBuffer[i] = buffer[0];
        blockIndexes[i] = 0;
    }

    for (int i = 0; i < numBlocks * BLOCK_SIZE; i++) {
        int min = -1;
        int minIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blockIndexes[j] < BLOCK_SIZE && (min == -1 || mergeBuffer[j] < min)) {
                min = mergeBuffer[j];
                minIdx = j;
            }
        }

        buffer[i % BLOCK_SIZE] = min;

        blockIndexes[minIdx] += 1;
        if (blockIndexes[minIdx] < BLOCK_SIZE) {
            readBlock(input, buffer + BLOCK_SIZE, 1, &logicalReads, &physicalReads);
            mergeBuffer[minIdx] = buffer[BLOCK_SIZE];
        } else {
            mergeBuffer[minIdx] = INT_MAX;
        }

        if ((i + 1) % BLOCK_SIZE == 0 || i == numBlocks * BLOCK_SIZE - 1) {
            writeBlock(output, buffer, BLOCK_SIZE);
            writeBlock(sorted, buffer, BLOCK_SIZE); // Save sorted data
        }
    }

    fclose(input);
    fclose(output);
    fclose(sorted);
    free(buffer);
    free(mergeBuffer);
    free(blockIndexes);

    printf("Logical Reads: %d\n", logicalReads);
    printf("Physical Reads: %d\n", physicalReads);
}

int main() {
    generateTestData("input.txt", 100);
    displayData("input.txt");

    externalMergeSort("input.txt", "output.txt", "sorted.txt");

    printf("Unsorted Data:\n");
    displayData("output.txt");

    printf("Sorted Data:\n");
    displayData("sorted.txt");

    return 0;
}
