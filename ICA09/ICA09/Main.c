#include <stdlib.h>
#include <stdio.h>

char studentName[10][20] = { "George","Sher","Steve","Gan","Fro","McGee","Citrus","Dalf","Do","Lock" };
int id[10] = { 49, 25, 69, 40, 20, 19, 81, 43, 71, 17 };
int grades[10] = { 80, 75, 62, 69, 54, 45, 70, 39, 88, 90 };

typedef struct Student
{
	char* name;
	int id;
	int grade;
	struct Student* next;
}Student;

typedef struct Student* ptr;

ptr CreateNode(char* name, int id, int grade)
{
	ptr node = (ptr)malloc(sizeof(struct Student));

	node->name = name;
	node->id = id;
	node->grade = grade;
	node->next = NULL;
	return node;
}

void DisplayList(ptr head)
{
	ptr current;
	current = head;

	while (current != NULL)
	{
		printf("Name: %s | Id: %d | Grade: %d\n", current->name, current->id, current->grade);
		current = current->next;
	}

	printf("\n");
}

void Menu(ptr idHead, ptr gradeHead)
{
	int userChoice = 0;
	int valueSelect = 0;
	ptr temp = NULL;
	ptr current = NULL;

		printf("1. Display list in order of ID's\n");
		printf("2. Display list in descending order of Grades\n");
		printf("3. Display person based on ID (ID input required)\n");
		printf("4. Display students above a threshold (threshold input required)\n");
		printf("5. Exit\n");
	do
	{
		printf("Enter a selection: ");
		scanf_s("%d", &userChoice);
		
		switch (userChoice)
		{
			case 1:
				DisplayList(idHead);
				break;

			case 2:
				DisplayList(gradeHead);
				break;
				
			case 3:
			{
				printf("Enter student ID: ");
				scanf_s("%d", &valueSelect);

				current = idHead;
				while (current != NULL)
				{
					if (current->id == valueSelect)
					{
						temp = current;
						break;
					}

					current = current->next;
				}

				if (temp == NULL)
				{
					printf("ID not found\n");

				}
				else
				{
					printf("Name: %s | Id: %d | Grade: %d\n", current->name, current->id, current->grade);
				}
				break;
			}



			case 4:
			{
				printf("Enter threshold grade: ");
				scanf_s("%d", &valueSelect);

				current = idHead;
				while (current != NULL)
				{
					if (current->id >= valueSelect)
					{
						printf("Name: %s | Grade: %d\n", current->name, current->grade);
					}

					current = current->next;
				}

				break;
			}

			case 5:
				exit(EXIT_SUCCESS);
				break;

			default:
				printf("\nInvalid! Enter a valid selection (1 - 5)\n\n");
				break;
		}
	} while (userChoice != 5);
}

int main(int argc, char** argv)
{
	ptr node;
	ptr temp;
	ptr current;
	ptr idHead = NULL;
	ptr gradeHead = NULL;

	//id linked list (increasing order)
	for (int i = 0; i < 10; i++)
	{
		node = CreateNode(studentName[i], id[i], grades[i]);

		if (i == 0)
		{
			idHead = node;
		}
		else if (i > 0)
		{
			
			if (idHead->id > node->id) //before head
			{
				temp = idHead;
				idHead = node;
				idHead->next = temp;
			}
			else //after head
			{
				current = idHead;
				while (current->next != NULL)
				{
					if (current->next->id >= node->id)
						break;

					current = current->next;
				}
				temp = current->next;
				current->next = node;
				node->next = temp;
			}
		}	
	}

	//grades linked list (descending order)
	for (int i = 0; i < 10; i++)
	{
		node = CreateNode(studentName[i], id[i], grades[i]);

		if (i == 0)
		{
			gradeHead = node;
		}
		else if (i > 0)
		{
			if (node->grade > gradeHead->grade)
			{
				temp = gradeHead;
				gradeHead = node;
				node->next = temp;
			}
			else
			{
				current = gradeHead;
				while (current->next != NULL)
				{
					if (current->next->grade <= node->grade)
						break;

					current = current->next;
				}
				temp = current->next;
				current->next = node;
				node->next = temp;
			}
		}
	}

	Menu(idHead, gradeHead);
}