#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 300000000
#define MAX_NAME_LENGTH 50
#define DATA_FILE "data.bin"
#define INDEX_FILE "index.bin"





struct Record {
    char name[MAX_NAME_LENGTH];
    int age;
    char phone[MAX_NAME_LENGTH];
};



void log_details(int count) {
    printf("Log details. Loop count: %d\n", count);
}







// Function to generate random data and store it in the data file
void generateRandomData() {
    FILE *dataFile = fopen(DATA_FILE, "wb");
    if (!dataFile) {
        perror("Error opening data file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_RECORDS; i++) {
        struct Record record;
        sprintf(record.name, "Name%d", i);
        record.age = rand() % 100;
        sprintf(record.phone, "Phone%d", rand() % 10000);
        fwrite(&record, sizeof(struct Record), 1, dataFile);
    }

    fclose(dataFile);
}

// Function to create a non-clustered index based on the name field
void createIndex() {
    FILE *dataFile = fopen(DATA_FILE, "rb");
    FILE *indexFile = fopen(INDEX_FILE, "wb");
    if (!dataFile || !indexFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    struct Record record;
    long offset = 0;
    while (fread(&record, sizeof(struct Record), 1, dataFile) == 1) {
        fprintf(indexFile, "%s %ld\n", record.name, offset);
        offset += sizeof(struct Record);
    }

    fclose(dataFile);
    fclose(indexFile);
}

// Function to search for a record by name using the index
void searchByName(const char *name) {




    int enable_log = 1; // Set to 1 to enable, 0 to disable
    int count = 0;






    FILE *indexFile = fopen(INDEX_FILE, "r");
    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!indexFile || !dataFile) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_NAME_LENGTH];
    long offset;
    int found = 0;

    while (fscanf(indexFile, "%s %ld", buffer, &offset) == 2) {
            if (enable_log == 1) {
                 count++;
                 
            }

        if (strcmp(name, buffer) == 0) {
            struct Record record;
            fseek(dataFile, offset, SEEK_SET);
            fread(&record, sizeof(struct Record), 1, dataFile);
            printf("Name: %s, Age: %d, Phone: %s\n", record.name, record.age, record.phone);
            found = 1;


            
            
            break;
        }
    }
                    
    if (enable_log == 1) {                
                     log_details(count); // Log the loop count
     }

    if (!found) {
        printf("Record not found\n");
    }

    fclose(indexFile);
    fclose(dataFile);
}

int main() {
    generateRandomData();
    createIndex();



    char searchName[MAX_NAME_LENGTH];
    int searchAgain = 1;

    while (searchAgain) {
         printf("Enter a name to search for: ");
         scanf("%s", searchName);

         searchByName(searchName);

         printf("Do you want to search again? (1 for yes, 0 for no): ");
         scanf("%d", &searchAgain);
    }










    return 0;
}














/*


create non-clustered index in file and data file like: name, age, phone in programing in C in linux 
Use just C programing 
With big RANDOM data genereation in file 
NOT use array
dont have error in programing when i execute 
ask input seach name 
binary file 
DRAW HOW THIS INDEX WORKS 

ChatGPT
Creating a non-clustered index in a binary file in C on Linux involves several steps: generating random data, creating an index file, and implementing a search mechanism. Here's a simple example, along with a conceptual drawing of how the index works.















Now, let's conceptualize how this index works:

Generate Data: Initially, random data records are generated and stored in the data.bin binary file. Each record consists of name, age, and phone fields.

Create Index: The createIndex() function reads the data from data.bin and creates an index file (index.bin) where each line contains the name field and the corresponding offset in data.bin.

Search by Name: To search for a record by name, the searchByName() function reads the index file line by line. When a match is found with the target name, it retrieves the offset from the index and uses it to directly seek and read the record from data.bin. This way, it avoids reading the entire data file and efficiently finds the desired record.

The index file essentially provides a map from names to offsets in the data file, allowing for efficient random access to specific records based on the name field.












*/










/*

This C program appears to be a simple example of a database-like system with some key features:

Data Generation: The program generates random data records and stores them in a binary data file called "data.bin". Each data record consists of a name, age, and phone number.

Index Creation: It creates a non-clustered index based on the name field from the data file. This index is stored in a separate binary file called "index.bin". The index associates names with their corresponding file offsets, allowing for faster name-based searches.

Search Function: The main part of the program involves searching for a record by name using the previously created index. It reads the index file, looks for a name, and then retrieves the associated data record from the data file based on the file offset. It also provides an option to enable or disable logging and counts the number of search iterations if logging is enabled.

User Interaction: After each search, it asks the user if they want to search again. If the user chooses to search again, the process continues; otherwise, the program exits.

Constants and Data Structures: It defines constants such as MAX_RECORDS (maximum number of records), MAX_NAME_LENGTH (maximum name length), DATA_FILE (data file name), and INDEX_FILE (index file name). It also defines a data structure struct Record to represent each data record.

Error Handling: The program includes error handling for file operations, ensuring that it exits gracefully if there are any issues with file opening.

The program essentially demonstrates how to generate random data, create an index to improve data retrieval efficiency, and perform name-based searches on the generated data using the index. Additionally, it showcases conditional logging of search iterations.

To use this program, you would compile it and run it in a C development environment. Users can enter names to search for, and the program will provide information about the corresponding records or report if a record is not found.






*/





/*

Searching by Name
c
Copy code
void searchByName(const char *name) {
    // ...
}
This function searches for a record by name using the index. It opens the index file and the data file. It then reads the index file line by line, extracting name and offset. When it finds a matching name, it reads the corresponding record from the data file and prints it.
Search Efficiency
The speed of the search operation is influenced by the use of an index. An index is like a table of contents for a book. It allows you to quickly locate the pages (or in this case, records) associated with a specific value (in this case, a name). Without an index, you would have to read through all the records one by one to find a match.

In this program, the index is based on names. When you search for a name, the program first looks it up in the index. Once it finds the name in the index, it uses the associated file offset to directly seek to the record in the data file. This is much faster than scanning through all records.
*/










/*


Why is this Fast?
Indexing: The key reason for the speed of this search operation is the use of an index. An index is like a table of contents in a book. It allows the program to jump directly to the relevant part of the data (in this case, the record with the desired name) rather than reading through every record.

Random Access: With the fseek() function, the program can perform random access to the data file. It moves the file pointer to a specific position (in this case, the position of the record in the data file), allowing the program to efficiently read data from that position.

Binary Files: Both the data and index files are binary. This means data can be read and written in large blocks (as opposed to one character at a time, which would be much slower).

Efficient Data Structure: Using a structure to organize records allows for efficient storage and retrieval.

Conditional Logging: The program optionally keeps track of how many iterations were performed during the search. This isn't directly related to the search speed but provides additional information about the search process.

In summary, this program is designed for speed by utilizing an index, random access, binary files, and efficient data structures. These elements work together to make searching by name a fast operation, even for a large number of records.




*/








