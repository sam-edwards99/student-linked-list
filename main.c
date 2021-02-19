#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//stores nodes of student object
struct Student{
        char name[100];
        int id;
        char department[100];
        float sub1;
        float sub2;
        float sub3;
        float scores;
        struct Student_t * next;
};

//global head of list
struct Student * HEAD = NULL;

//read in records from text file
int readFromFile(){
    FILE * input;
    input = fopen("data.txt", "r");
    if (input == NULL)
    {
        perror( "fopen failed" );
        exit(1);
    }

    int count = 0;
    HEAD = malloc(sizeof(struct Student));
    struct Student * temp = malloc(sizeof(struct Student));
    HEAD->next = temp;
    char parsedLine[100];
    while (fgets(parsedLine, 100, input) != NULL && count < 3) {
        char *getName = strtok(parsedLine, ",");
        strcpy(temp->name, getName);
        int getId = atoi(strtok(NULL, ","));
        temp->id = getId;
        char *getDep = strtok(NULL, ",");
        strcpy(temp->department, getDep);
        float getSub1 = atof(strtok(NULL, ","));
        temp->sub1 = getSub1;
        float getSub2 = atof(strtok(NULL, ","));
        temp->sub2 = getSub2;
        float getSub3 = atof(strtok(NULL, ",\n"));
        temp->sub3 = getSub3;
        printf("%s, %d, %s, %f, %f, %f\n", temp->name, temp->id, temp->department, temp->sub1, temp->sub2, temp->sub3);\
        temp->next = malloc(sizeof(struct Student));
        temp = temp->next;
        count++;
    }
    temp->next = NULL;
    return count;
}

//test function
void printRecords(){
    struct Student * temp = HEAD;
    while(temp->next != NULL){
        temp = temp->next;
        printf("Student is: %s, %d, %s, %f, %f, %f\n", temp->name, temp->id, temp->department, temp->sub1,
               temp->sub2, temp->sub3);
    }
}

void clearstdin(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

//function to add a new record
void add_student(char * name,int id, char * department,float sub1,float sub2,float sub3){
    struct Student * temp = HEAD;
    while(temp->next != NULL){
        temp = temp->next;
        //printf("Student is: %s, %d, %s, %f, %f, %f\n", temp->name, temp->id, temp->department, temp->sub1, temp->sub2, temp->sub3);
    }
    temp->next = malloc(sizeof(struct Student));
    temp = temp->next;
    strcpy(temp->name, name);
    temp->id = id;
    strcpy(temp->department, department);
    temp->sub1 = sub1;
    temp->sub2 = sub2;
    temp->sub3 = sub3;
    temp->next = NULL;
    return;
}

//function to update a students info
struct Student * update_student(int id, char * column_name, char * new_value){
    struct Student * temp = HEAD;
    while(temp->next != NULL){
        if(temp->id == id){
            if(strcmp(column_name, "name")){
                strcpy(temp->name, new_value);
            }
            if(strcmp(column_name, "id")){
                temp->id = atoi(id);
            }
            if(strcmp(column_name, "department")){
                strcpy(temp->department, new_value);
            }
            if(strcmp(column_name, "subject1")){
                temp->sub1 = atof(new_value);
            }
            if(strcmp(column_name, "subject2")){
                temp->sub2 = atof(new_value);
            }
            if(strcmp(column_name, "subject3")){
                temp->sub3 = atof(new_value);
            }
            else{
                printf("Invalid Column name\n");
            }
        }
        temp = temp->next;
    }
    return NULL;

}

// function to read a students columns
struct Student * read_student(int id, char * column_name){
    struct Student * temp = HEAD;
    while(temp->next != NULL){
        if(temp->id == id){
            if(strcmp(column_name, "name")){
                printf("Name: %s",temp->name);
            }
            if(strcmp(column_name, "id")){
                printf("id: %d", temp->id);
            }
            if(strcmp(column_name, "department")){
                printf(temp->department);
            }
            if(strcmp(column_name, "subject1")){
                printf("Subject1: %f", temp->sub1);
            }
            if(strcmp(column_name, "subject2")){
                printf("Subject2: %f", temp->sub2);
            }
            if(strcmp(column_name, "subject3")){
                printf("Subject3: %f", temp->sub3);
            }
            else{
                printf("Invalid Column name\n");
            }
        }
        temp = temp->next;
    }
    return NULL;

}

//function to find a student and show all of its attributes
struct Student * search_student(int id){
    int found = 0;
    struct Student * temp = HEAD;
    while(temp->next != NULL) {
        if (temp->id == id) {
            //printf("Student is: %s, %d, %s, %f, %f, %f\n", temp->name, temp->id, temp->department, temp->sub1, temp->sub2, temp->sub3);
            found = 1;
        }
        temp = temp->next;
    }
    if(found == 0){
        printf("Student not found");
    }
    return NULL;

}

//function to remove a student from the list
struct Student * delete_student(int id) {
    int found = 0;
    struct Student * trailer = HEAD;
    struct Student * temp = HEAD;
    while(temp->next != NULL) {
        trailer = temp;
        temp = temp->next;
        if (temp->id == id) {
            trailer->next = temp->next;
            printf("Student is: %s, %d, %s, %f, %f, %f\n", temp->name, temp->id, temp->department, temp->sub1, temp->sub2, temp->sub3);
            found = 1;
        }

    }
    if(found == 0){
        printf("Student not found");
    }
    return NULL;
}

int main() {
    //load records from file
    printf("data from file...\n");
    readFromFile();
    int choice = -1;
    //menu
    while(choice != 6) {
        printf("Welcome to Student Records Manager!\n");
        printf("What would you like to do?\n");
        printf( "1 to Add a new Student Record\n");
        printf( "2 to Update a Student Record\n");
        printf( "3 to Read a Student Record\n");
        printf( "4 Search for a Student Record\n");
        printf( "5 to Delete a Student Record\n");
        printf( "6 to Exit\n");
        printf( "Enter:");

        scanf("%d", &choice);
        clearstdin();


        printf("\n");

        if (choice > 6 || choice < 0) {
            printf("Input must be an integer 1 - 6\n");
            continue;
        }

        char name[100];
        int id = -1;
        char char_id[10];
        char department[100];
        float sub1;
        char c_sub1[6];
        float sub2;
        char c_sub2[6];
        float sub3;
        char c_sub3[6];

        char column[100];
        char value[100];

        switch (choice) {
            // if the user wishes to add a record
            case 1:
                printf("Add A New Student\n");
                while (1) {
                    printf("\nStudent name:");

                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = 0;

                    printf("Student id:");
                    fgets(char_id, sizeof(char_id), stdin);
                    char_id[strcspn(char_id, "\n")] = 0;

                    printf("Student department:");

                    fgets(department, sizeof(department), stdin);
                    department[strcspn(department, "\n")] = 0;

                    printf("Student Subject 1 grade:");

                    fgets(c_sub1, sizeof(c_sub1), stdin);
                    c_sub1[strcspn(c_sub1, "\n")] = 0;

                    printf("Student Subject 2 grade:");

                    fgets(c_sub2, sizeof(c_sub2), stdin);
                    c_sub2[strcspn(c_sub2, "\n")] = 0;

                    printf("Student Subject 3 grade:");

                    fgets(c_sub3, sizeof(c_sub3), stdin);
                    c_sub3[strcspn(c_sub3, "\n")] = 0;

                    if ((id = atoi(char_id)) < 0 || (sub1 = atoi(c_sub1)) < 0 || (sub2 = atoi(c_sub2)) < 0 ||
                        (sub3 = atoi(c_sub3)) < 0) {
                        printf("Invalid Input: Please Try Again\n");
                        break;
                    } else {
                        printf("Adding Student: %s, %s, %s, %s, %s, %s\n", name, char_id, department, c_sub1, c_sub2,
                               c_sub3);
                        add_student(name, id, department, sub1, sub2, sub3);
                        break;
                    }
                }
                //add_student(name, id, department, sub1, sub2, sub3);
                //printf( "Student Added" << endl;
                break;

                //if the user wishes to update a record
            case 2:
                printf("Update a Student Record\n");
                while (1) {
                    printf("Student id:");
                    fgets(char_id, sizeof(char_id), stdin);
                    char_id[strcspn(char_id, "\n")] = 0;

                    printf("Column to Update (Options are 'name', 'id', 'department', 'subject1', 'subject2', 'subject3'):");
                    fgets(column, sizeof(column), stdin);
                    column[strcspn(column, "\n")] = 0;

                    printf("New Value:");
                    fgets(value, sizeof(value), stdin);
                    value[strcspn(value, "\n")] = 0;

                    if ((id = atoi(char_id)) < 0) {
                        printf("Invalid Input: Please Try Again\n");
                        continue;
                    } else {
                        update_student(id, column, value);
                        break;
                    }
                }
                update_student(id, column, value);
                break;

                //if the user wishes to read a students value
            case 3:
                printf("Read a Student Record\n");
                while (1) {
                    printf("Student id:");
                    fgets(char_id, sizeof(char_id), stdin);
                    char_id[strcspn(char_id, "\n")] = 0;

                    printf("Column to View (Options are 'name', 'id', 'department', 'subject1', 'subject2', 'subject3'):");
                    fgets(column, sizeof(column), stdin);
                    column[strcspn(column, "\n")] = 0;

                    if ((id = atoi(char_id)) < 0) {
                        printf("Invalid Input: Please Try Again\n");
                        read_student(id, column);
                    } else {
                        break;
                    }
                }
                break;

            // if the user wishes to find all of a records attributes
            case 4:
                printf( "Search for a Student Record\n" );
                while(1) {
                    printf( "Student id:");
                    fgets(char_id, sizeof(char_id), stdin);
                    char_id[strcspn(char_id, "\n")] = 0;

                    if ((id = atoi(char_id)) < 0) {
                        printf( "Invalid Input: Please Try Again\n");
                        continue;
                    }
                    else {
                        search_student(id);
                        break;
                    }
                }

                break;

                //if a user wishes to delete a students record
            case 5:
                printf( "Delete a Student Record\n");
                while(1) {
                    printf( "Student id:");
                    fgets(char_id, sizeof(char_id), stdin);
                    char_id[strcspn(char_id, "\n")] = 0;

                    if ((id = atoi(char_id)) < 0) {
                        printf( "Invalid Input: Please Try Again\n" );
                        continue;
                    }
                    else {
                        break;
                    }
                }
                delete_student(id);
                break;

                //if a student wants to exit
            case 6:
                //printRecords();
                exit(0);
        }
    }
    //printRecords();
    return 0;
}