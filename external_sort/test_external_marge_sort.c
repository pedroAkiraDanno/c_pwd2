#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>



#define BLOCK_SIZE 4 // Adjust this according to your needs

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

void externalMergeSort(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "rb");
    FILE *output = fopen(outputFile, "wb");

    if (input == NULL || output == NULL) {
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
            mergeBuffer[minIdx] = INT_MAX; // Mark as "already merged"
        }

        if ((i + 1) % BLOCK_SIZE == 0 || i == numBlocks * BLOCK_SIZE - 1) {
            writeBlock(output, buffer, BLOCK_SIZE);
        }
    }

    fclose(input);
    fclose(output);
    free(buffer);
    free(mergeBuffer);
    free(blockIndexes);

    printf("Logical Reads: %d\n", logicalReads);
    printf("Physical Reads: %d\n", physicalReads);
}

int main() {
    generateTestData("input.txt", 100); // Generate test data (replace with your own data)

    externalMergeSort("input.txt", "output.txt");

    return 0;
}
















