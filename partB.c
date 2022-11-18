#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "student.h"
#include "paths.h"

typedef struct msg
{
  long type;
  float data;
} message;

message createMsg(long x, float y);
float getTotal(Marks m);

int main()
{
  Marks data[100];
  float totalMarks[100];
  pid_t c1, c2, cc1, cc2;

  FILE *file = fopen(filePath, "r");

  if (file == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }

  for (int i = 0; i < 100; i++)
  {
    Marks mark;
    if (fread(&mark, sizeof(Marks), 1, file))
    {
      data[i] = mark;
      totalMarks[i] = getTotal(mark);
    }
  }

  c1 = fork();

  switch (c1)
  {
  // error
  case -1:
    break;

  // C1 and CC1
  case 0:
    cc1 = fork();

    switch (cc1)
    {
    // error
    case -1:
      break;

    // CC1
    case 0:

    // C1
    default:
      break;
    }

    break;

  // P, C2 and CC2
  default:
    c2 = fork();

    switch (c2)
    {
    // error
    case -1:
      break;

    // C2 and CC2
    case 0:
      cc2 = fork();

      switch (cc2)
      {
      // error
      case -1:
        break;

      // CC2
      case 0:
        break;

      // C2
      default:
        break;
      }

      break;

    // P
    default:
      key_t key1 = ftok("file.txt", 30);

      int mqID = msgget(key1, IPC_CREAT | IPC_EXCL | 0666);

      if (mqID == -1)
      {
        printf("Parent message queue create error\n");
        perror("MQ: ");
        printf("Error number is: %d", errno);
        exit(0);
      }
      else
      {
      }

      break;
    }

    break;
  }

  return 0;
}

message createMsg(long x, float y)
{
  message newMsg;

  newMsg.type = x;
  newMsg.data = y;

  return newMsg;
}

float getTotal(Marks m)
{
  float total = m.assgnmt01_marks + m.assgnmt02_marks + m.project_marks + m.finalExam_marks;

  return total;
}