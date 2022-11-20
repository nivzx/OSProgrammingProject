#include <stdio.h>
#include <stdlib.h>
#include "displayMenu.h"

typedef struct student_marks
{
  char (*student_index)[12]; // EG/XXXX/XXXX
  float assgnmt01_marks;     // 15%
  float assgnmt02_marks;     // 15%
  float project_marks;       // 20%
  float finalExam_marks;     // 50%
} Marks;

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam);

int main()
{
  int selection = mainMenu();

  printf("%d", selection);

  return 0;
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