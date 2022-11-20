#pragma once

#include "marks.c"

typedef struct student_marks
{
  char (*student_index)[12]; // EG/XXXX/XXXX
  float assgnmt01_marks;     // 15%
  float assgnmt02_marks;     // 15%
  float project_marks;       // 20%
  float finalExam_marks;     // 50%
} Marks;

Marks *createMarks(char (*index)[12], float a1, float a2, float project, float exam);