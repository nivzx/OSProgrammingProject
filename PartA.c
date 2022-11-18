#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "student.h"
#include "paths.h"

int mainMenu();
void createStudentRecord();
void updateMenu();
void deleteMenu();
void readMarks();
void navigate();
void addToFile(Marks mark);
void updateFile(Marks mark);
void deleteMark(char regNo[12]);

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam);

int addedStudents = 0;

int main()
{
  printf("                   ~Welcome~                    \n");

  navigate();

  return 0;
}

// To handle the menu navigation
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

    case 4:
      readMarks();
      optionSelected = 1;
      break;

    default:
      printf("Invalid option. Try Again\n");
      break;
    }
  }
}

// Displaying main menu
int mainMenu()
{
  printf("\n======================Main Menu=================\n");
  printf("1. Add Student Marks Entry\n");
  printf("2. Update Student Marks\n");
  printf("3. Delete Student Marks\n");
  printf("4. View data records\n");

  int selected;

  printf("Select Option: ");
  scanf("%d", &selected);

  return selected;
}

// Create entry menu
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

// Update entry menu
void updateMenu()
{
  Marks updateEntry;

  printf("\n====================Update Mark===================\n");
  printf("Enter student index number: ");
  scanf("%s", updateEntry.student_index);
  printf("Enter updated assignment 1 marks: ");
  scanf("%f", &updateEntry.assgnmt01_marks);
  printf("Enter updated assignment 2 marks: ");
  scanf("%f", &updateEntry.assgnmt02_marks);
  printf("Enter updated assignment project marks: ");
  scanf("%f", &updateEntry.project_marks);
  printf("Enter updated final exam marks: ");
  scanf("%f", &updateEntry.finalExam_marks);

  updateFile(updateEntry);

  navigate();
}

// Delete mark menu
void deleteMenu()
{
  char index[12];

  printf("\n====================Delete Mark===================\n");
  printf("Enter index number of student: ");
  scanf("%s", index);

  deleteMark(index);

  navigate();
}

// Writing to file
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

// Update a file
void updateFile(Marks updatedMark)
{
  // File pointers to data file and a copy of that file
  FILE *file, *copy;
  Marks mark;

  // Opening file to read
  file = fopen(filePath, "r+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Opening copy file to write
  copy = fopen(tempFilePath, "a+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Copying to temp file with updated data
  while (fread(&mark, sizeof(Marks), 1, file))
  {
    if (strcmp(mark.student_index, updatedMark.student_index) == 0)
    {
      int write_ret = fwrite(&updatedMark, sizeof(Marks), 1, copy);
      if (write_ret < 0)
      {
        printf("Error No: %d\n", errno);
        perror("fwrite Error: ");
        exit(1);
      }
    }
    else
    {
      int write_ret = fwrite(&mark, sizeof(Marks), 1, copy);
      if (write_ret < 0)
      {
        printf("Error No: %d\n", errno);
        perror("fwrite Error: ");
        exit(1);
      }
    }
  }

  fclose(file);

  file = fopen(filePath, "w+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Writing back to main file
  while (fread(&mark, sizeof(Marks), 1, copy))
  {
    int write_ret = fwrite(&mark, sizeof(Marks), 1, file);
    if (write_ret < 0)
    {
      printf("Error No: %d\n", errno);
      perror("fwrite Error: ");
      exit(1);
    }
  }

  fclose(file);
  fclose(copy);
}

void deleteMark(char index[12])
{
  // File pointers to data file and a copy of that file
  FILE *file, *copy;
  Marks mark;

  // Opening file to read
  file = fopen(filePath, "r+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Opening copy file to write
  copy = fopen(tempFilePath, "a+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Copying to temp file without deleting entry
  while (fread(&mark, sizeof(Marks), 1, file))
  {
    if (strcmp(mark.student_index, index) != 0)
    {
      int write_ret = fwrite(&mark, sizeof(Marks), 1, copy);
      if (write_ret < 0)
      {
        printf("Error No: %d\n", errno);
        perror("fwrite Error: ");
        exit(1);
      }
    }
  }

  fclose(file);

  file = fopen(filePath, "w+");
  if (file == NULL)
  {
    printf("Error No: %d\n", errno);
    perror("fopen Error: ");
    exit(1);
  }

  // Copying back to main file
  while (fread(&mark, sizeof(Marks), 1, copy))
  {
    int write_ret = fwrite(&mark, sizeof(Marks), 1, file);
    if (write_ret < 0)
    {
      printf("Error No: %d\n", errno);
      perror("fwrite Error: ");
      exit(1);
    }
  }

  fclose(file);
  fclose(copy);
}

void readMarks()
{
  FILE *infile;
  Marks input;

  // Open person.dat for reading
  infile = fopen(filePath, "r");
  if (infile == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }

  // read file contents till end of file
  while (fread(&input, sizeof(Marks), 1, infile))
  {
    printf("%s | %f | %f | %f | %f\n",
           input.student_index,
           input.assgnmt01_marks,
           input.assgnmt02_marks,
           input.project_marks,
           input.finalExam_marks);
  }

  // close file
  fclose(infile);

  navigate();
}