#include <marks.h>

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