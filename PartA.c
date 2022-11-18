#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "student.h"

int mainMenu();
void createStudentRecord();
void updateMenu();
void deleteMenu();
void navigate();
void addToFile(Marks mark);
void updateFile(Marks mark);
void deleteMark(char regNo[12]);

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam);

int addedStudents = 0;

char filePath[] = "./data/marks.dat";
char dummyFilePath[] = "./Files/dummyMarks.dat";

int main()
{
  printf("                   ~Welcome~                    \n");

  navigate();

  return 0;
}

void navigate()
{
  int optionSelected = 0;

  while (optionSelected == 0)
  {
    int selection = mainMenu();

    switch (selection)
    {
    case 1:
      createStudentRecord();
      optionSelected = 1;
      break;

    case 2:
      updateMenu();
      optionSelected = 1;
      break;

    case 3:
      deleteMenu();
      optionSelected = 1;
      break;

    default:
      printf("Invalid option. Try Again\n");
      break;
    }
  }
}

int mainMenu()
{
  printf("\n======================Main Menu=================\n");
  printf("1. Add Student Marks Entry\n");
  printf("2. Update Student Marks\n");
  printf("3. Delete Student Marks\n");

  int selected;

  printf("Select Option: ");
  scanf("%d", &selected);

  return selected;
}

void createStudentRecord()
{
  Marks markEntry;

  printf("\n====================Add Mark===================\n");
  printf("Number of students added = %d/100\n", addedStudents);

  printf("Enter index number: ");
  scanf("%s", markEntry.student_index);
  printf("Enter assignment 1 marks: ");
  scanf("%f", &markEntry.assgnmt01_marks);
  printf("Enter assignment 2 marks: ");
  scanf("%f", &markEntry.assgnmt02_marks);
  printf("Enter assignment project marks: ");
  scanf("%f", &markEntry.project_marks);
  printf("Enter final exam marks: ");
  scanf("%f", &markEntry.finalExam_marks);

  addToFile(markEntry);
  navigate();
}

void updateMenu()
{
  Marks updateEntry;

  printf("\n====================Update Mark===================\n");
  printf("Enter index number of student: ");
  scanf("%s", updateEntry.student_index);
  printf("Enter updated assignment 1 marks: ");
  scanf("%f", &updateEntry.assgnmt01_marks);
  printf("Enter updated assignment 2 marks: ");
  scanf("%f", &updateEntry.assgnmt02_marks);
  printf("Enter updated assignment project marks: ");
  scanf("%f", &updateEntry.project_marks);
  printf("Enter updated final exam marks: ");
  scanf("%f", &updateEntry.finalExam_marks);
}

void deleteMenu()
{
  char index[12];

  printf("\n====================Delete Mark===================\n");
  printf("Enter index number of student: ");
  scanf("%s", index);

  deleteMark(index);
}

void addToFile(Marks mark)
{
  FILE *filePointer;

  filePointer = fopen(filePath, "a+");
  if (filePointer == NULL)
  {
    printf("Couldn't open file: %d\n", errno);
    perror("fopen Error: \n");
    exit(1);
  }

  int write_ret = fwrite(&mark, sizeof(Marks), 1, filePointer);

  if (write_ret < 0)
  {
    printf("Error No: %d\n", errno);
    perror("fwrite Error: ");
    exit(1);
  }

  fclose(filePointer);
}

void updateFile(Marks mark)
{
}

void deleteMark(char index[12])
{
}