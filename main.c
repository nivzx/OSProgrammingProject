#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct student_marks
{
  char (*student_index)[12]; // EG/XXXX/XXXX
  float assgnmt01_marks;     // 15%
  float assgnmt02_marks;     // 15%
  float project_marks;       // 20%
  float finalExam_marks;     // 50%
} Marks;

int mainMenu();
void addMenu();
void updateMenu();
void deleteMenu();
void navigate();
void addToFile(Marks *mark);

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam);

int addedStudents = 0;

char filePath[] = "./Files/marks.txt";

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
      addMenu();
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
  printf("\n====================Main Menu=================\n");
  printf("1. Add Student Marks\n");
  printf("2. Update Student Marks\n");
  printf("3. Delete Student Marks\n");

  int selected;

  printf("Select Option: ");
  scanf("%d", &selected);

  return selected;
}

void addMenu()
{
  char index[12];
  float a1, a2, proj, exam;

  printf("\n====================Add Mark===================\n");
  printf("Number of students added = %d/100\n", addedStudents);

  printf("Enter index number: ");
  scanf("%s", index);
  printf("Enter assignment 1 marks: ");
  scanf("%f", &a1);
  printf("Enter assignment 2 marks: ");
  scanf("%f", &a2);
  printf("Enter assignment project marks: ");
  scanf("%f", &proj);
  printf("Enter final exam marks: ");
  scanf("%f", &exam);

  Marks *newMark = createMarks(index, a1, a2, proj, exam);

  addToFile(newMark);

  navigate();
}

void updateMenu()
{
  char index[12];
  float a1, a2, proj, exam;

  printf("\n====================Update Mark===================\n");
  printf("Enter index number of student: ");
  scanf("%s", index);
  printf("Enter updated assignment 1 marks: ");
  scanf("%f", &a1);
  printf("Enter updated assignment 2 marks: ");
  scanf("%f", &a2);
  printf("Enter updated assignment project marks: ");
  scanf("%f", &proj);
  printf("Enter updated final exam marks: ");
  scanf("%f", &exam);
}

void deleteMenu()
{
  char index[12];

  printf("\n====================Delete Mark===================\n");
  printf("Enter index number of student: ");
  scanf("%s", index);
}

void addToFile(Marks *mark)
{
  FILE *fp = fopen(filePath, "w+");

  if (fp == NULL)
  {
    perror(filePath);
    printf("Couldn't open file.\n");
    exit(0);
  }

  int byte_ret = fprintf(fp, "%s %f %f %f %f\n",
                         (char *)(mark->student_index),
                         mark->assgnmt01_marks,
                         mark->assgnmt02_marks,
                         mark->project_marks,
                         mark->finalExam_marks);

  if (byte_ret == -1)
  {
    perror(filePath);
    printf("Couldn't write .\n");
    exit(0);
  }
  printf("Success\n");
  addedStudents++;
}

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam)
{
  Marks *m = malloc(sizeof(Marks));

  m->student_index = index;
  m->assgnmt01_marks = a1;
  m->assgnmt02_marks = a2;
  m->project_marks = project;
  m->finalExam_marks = exam;

  return m;
};