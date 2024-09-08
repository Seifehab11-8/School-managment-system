/*
 * project title: School Management system
 * Date modified: 6 Aug 2024
 * Author: Seif Ehab
 */

/* exceute in terminal gcc -o main main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define STRLENGTH 50

typedef struct{
	int id; // student's ID
	char name[STRLENGTH]; // student's name
	int age; // student's age
	float gpa; // student's GPA
}student;

typedef struct node{
	student data;
	struct node *next; // should be defined using a struct name typedef is only accepted after the decleration is fully finished
}node;

/*Creating head and current pointers for student linked list*/
node *head = NULL, *current = NULL; // Avoiding Wild pointers, assigning to NULL

char *newline_pos = NULL; // used in getting rid of newlines during name scanning in the terminal

void addStudent(const student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main(void)
{
	int operation = 0, id = 0, termination_flag = 0;
	float gpa_average = 0.0;
	student student_temp;

	while(TRUE)
	{
		printf("---------------------------------------------\n");
		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student by ID\n");
		printf("4. Update Student Information\n");
		printf("5. Delete Student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search for Student with Highest GPA\n");
		printf("8. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &operation);

		switch(operation){
		case 1:
			/* scanning a new student */
			printf("---------------------------------------------\n");

			printf("Enter Student ID: ");
			if(!scanf("%d", &(student_temp.id)))
			{
				printf("Something went wrong Exiting....\n");
				return 0;
			}
			getchar();

			printf("Enter name: "); fgets(student_temp.name, STRLENGTH, stdin);
			newline_pos = strchr(student_temp.name, '\n'); // removes potential newlines caused by the fgets
			if (newline_pos) {
				*newline_pos = '\0';
			}

			printf("Enter age: ");
			if(!scanf("%d", &(student_temp.age)))
			{
				printf("Something went wrong Exiting....\n");
				return 0;
			}

			printf("Enter GPA: ");
			if(!scanf("%f", &(student_temp.gpa)))
			{
				printf("Something went wrong Exiting....\n");
				return 0;
			}

			addStudent(&student_temp);
			/***********************************************************/
			/* undefined error during scanning or during function call */
			/***********************************************************/
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			printf("Enter student ID to search: "); scanf("%d", &id);
			searchStudentByID(id);
			break;
		case 4:
			printf("Enter student ID to update: "); scanf("%d", &id);
			updateStudent(id);
			/***********************************************************/
			/* undefined error during function call */
			/***********************************************************/
			break;
		case 5:
			printf("Enter student ID to remove the student's data: "); scanf("%d", &id);
			deleteStudent(id);
			break;
		case 6:
			gpa_average = calculateAverageGPA();
			if(gpa_average == 0.0)
			{
				printf("---------------------------------------------\n");
				printf("No students are found.\n");
			}
			else
			{
				printf("---------------------------------------------\n");
				printf("The average GPA is [%0.2f].\n", gpa_average);
			}
			break;
		case 7:
			searchHighestGPA();
			break;
		case 8:
			termination_flag = TRUE;
			break;

		}
		/* To end the program */
		if(termination_flag)
		{
			break;
		}
	}
}

/*
 * Description:
 * It adds a new student to the linked list. It first checks if the student's ID already exists.
 * If the ID exists, it prints an error message and returns. If the ID does not exist,
 * it attempts to allocate memory for a new node.
 * If memory allocation fails, it prints an error message and returns.
 * If memory allocation is successful, it copies the student data to the new node
 * and adds the node to the end of the linked list.
 */

void addStudent(const student *const ptr)
{
    node* link = NULL, *previous = NULL;

    /* Checking if the id already exists */
    current = head;
    while(current != NULL)
    {
    	if(current ->data.id == ptr->id)
    	{
    		printf("---------------------------------------------\n");
    		printf("Student with ID %d already exist.\n", ptr->id);
    		return;
    	}
    	previous = current; // when current reaches null the previous will reach the last node
    	current = current -> next;
    }

    link = (node*)malloc(sizeof(node)); //creating a new node should be sizeof(node) not sizeof(student) causes segementation fault error
    current = head;

    if(link == NULL)
    {
    	printf("---------------------------------------------\n");
    	printf("Failed to save the data.\n");
    	return;
    }

    /* Copying data to the node */
    link ->data.id = ptr ->id;
    strcpy(link ->data.name, ptr->name);
    link ->data.age = ptr ->age;
    link ->data.gpa = ptr ->gpa;

    /* Attaching the node to the linked list */
    link -> next = NULL;
    if(head == NULL)
    {
        head = link;
        return;
    }

    previous ->next = link;
}

/*
 * Description:
 * Displays all students in the linked list.
 * If the list is empty, it prints a message indicating no students are present. Otherwise,
 * it traverses the list and prints the details of each student.
 */

void displayStudents(void)
{
    current = head;
    printf("---------------------------------------------\n");

    if(head == NULL)
    {
    	printf("No students found.\n");
    	return;
    }

    /* printing node by node */
    while(current != NULL)
    {
        /* Displays the entire data of single student in one line*/
    	printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n",
        		current ->data.id,
        		current ->data.name,
				current ->data.age,
				current ->data.gpa
				);

        current = current ->next;
    }
}

/*
 * Description:
 * It searches for a student by their ID in the linked list.
 * If the student is found, it prints their details.
 * If the student is not found, it prints a message indicating the student was not found.
 */

void searchStudentByID(int id)
{
    current = head;
    while(current != NULL){
        if(current -> data.id == id)
        {
        	printf("---------------------------------------------\n");
        	printf("Student Found:\n");
        	printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n",
					current ->data.id,
					current ->data.name,
					current ->data.age,
					current ->data.gpa
					);
            return;
        }
        current = current ->next;
    }
    printf("---------------------------------------------\n");
    printf("Student with ID %d not found.\n", id);
}

/*
 * Description:
 * Updates the details of a student with a given ID in the linked list.
 * If the student is found, then update the student's information (student name, age, gpa).
 * If the student is not found, it prints a message indicating the student was not found.
 */

void updateStudent(int id)
{
    current = head;
    char name[STRLENGTH];
    while(current != NULL){
    	/* Taking the new inputs from the user */
        if(current ->data.id == id)
        {
        	printf("---------------------------------------------\n");
        	printf("Enter new details of Student with ID %d:\n", id);

        	getchar();

            printf("Enter new name: ");
            fgets(name, STRLENGTH, stdin); // checks for the length of string and stops the input once length -1 is reached

            newline_pos = strchr(name, '\n'); // removes potential newlines caused by the fgets
			if (newline_pos) {
				*newline_pos = '\0';
			}
			strcpy(current ->data.name, name);

            printf("Enter new age: ");
            if(!scanf("%d", &(current ->data.age)))
            {
				printf("Something went wrong Exiting....\n");
				return;
			}

            printf("Enter new GPA: ");
            if(!scanf("%f", &(current ->data.gpa)))
            {
				printf("Something went wrong Exiting....\n");
				return ;
			}

            printf("Student details updated successfully.\n");
            return;
        }
        current = current ->next;
    }

    printf("---------------------------------------------\n");
    printf("Student with ID %d not found.\n", id);
}

/*
 * Description:
 * Calculates and returns the average GPA of all students in the linked list.
 * It traverses the list to sum the GPAs of all students and counts the number of students.
 * If the list is empty, it returns 0.0.
 * Otherwise, it computes and returns the average GPA by dividing the total sum of GPAs by the number of students.
 */

float calculateAverageGPA(void)
{
	float averageGPA = 0;
    int count = 0;

    if(head == NULL)
    {
    	return 0.0;// handling corner case which can cause the program to try and return 0/0 which will cause a runtime error
    }

	current = head;
    while(current != NULL)
    {
        averageGPA += (current ->data.gpa);
        count++;// count is incremented since the linked list size is unknown
        current = current ->next;
    }
	averageGPA = averageGPA/count;

	return averageGPA;
}

/*
 * Description:
 * Searches for the student with the highest GPA in the linked list.
 * It traverses the list, keeping track of the student with the highest GPA encountered.
 * If the list is empty, it prints a message indicating that there are no students.
 * After finding the student with the highest GPA, it prints the details of that student.
 */

void searchHighestGPA(void)
{
    float maxGPA = 0;
    node* maxPtr = head; // To stop at the student with the highest GPA

    current = head;
    if(head == NULL)
    {
    	printf("---------------------------------------------\n");
        printf("No students found.\n");
        return;
    }

    while(current != NULL)
    {
        if(current -> data.gpa > maxGPA)
        {
            maxGPA = current -> data.gpa;
            maxPtr = current; // Updated when a new highest GPA is found
        }
        current = current->next;
    }

    printf("---------------------------------------------\n");
    printf("Student with the highest GPA is: \n");
    printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n",
    		maxPtr ->data.id,
			maxPtr ->data.name,
			maxPtr ->data.age,
			maxPtr ->data.gpa
			);
}

/*
 * Description:
 * Iterates through the linked list of students starting with the Head of it to find the student with the given ID.
 * If the student is found, it adjusts the pointers to remove the node from the list,
 * frees the memory allocated for the node, and prints a success message.
 * If the student is not found, it prints a message indicating the student was not found.
 */

void deleteStudent(int id)
{
    node* previous = head;
    current = head;

    if(head == NULL)
    {
    	printf("---------------------------------------------\n");
    	printf("Students not found.\n");
    	return;
    }

    /* if the data equal the head node data the head should be shifted */
    if(head ->data.id == id)
    {
        head = head->next;
        free(current); // freeing the heap memory after delinking the data
        return;
    }

    /* searching for the data to be deleted*/
    current = current -> next;
    while(current != NULL)
    {
        if(current ->data.id == id)
        {
            previous ->next = current ->next;
            free(current);// freeing the heap memory after delinking the data

            printf("---------------------------------------------\n");
            printf("Student with ID %d is removed successfully.\n", id);

            return;
        }
        previous = current;
        current = current ->next;
    }

    printf("---------------------------------------------\n");
    printf("Student with ID %d not found.\n", id);
}


