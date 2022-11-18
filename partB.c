#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
  int belowTwntyFive = 0;

  // Reading data from file to analyze
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

      if (totalMarks[i] < 25)
      {
        belowTwntyFive++;
      }
    }
  }

  // Initial fork
  c1 = fork();

  switch (c1)
  {
  // error
  case -1:
    perror("Parent fork error: ");
    printf("Error No: %d\n", errno);
    exit(0);
    break;

  // C1 and CC1
  case 0:
    // Creating child of first child
    cc1 = fork();

    switch (cc1)
    {
    // error
    case -1:
      perror("C1 fork error: ");
      printf("Error No: %d\n", errno);
      exit(0);
      break;

    // CC1
    case 0:;
      sleep(0.001);
      float t4;
      t4 = 0;

      for (int i = 60; i < 80; i++)
      {
        t4 += totalMarks[i];
      }

      key_t key4 = ftok("file.txt", 30);

      int mqID = msgget(key4, 0);
      if (mqID == -1)
      {
        printf("CC1 mq error\n");
        perror("MQ: ");
        printf("Error number is: %d", errno);
        exit(0);
      }

      message m4 = createMsg(1, t4);
      msgsnd(mqID, &m4, sizeof(t4), IPC_NOWAIT);

      break;

    // C1
    default:;
      sleep(0.001);
      float t2;
      t2 = 0;

      for (int i = 20; i < 40; i++)
      {
        t2 += totalMarks[i];
      }

      key_t key2 = ftok("file.txt", 30);

      int mqID2 = msgget(key2, 0);
      if (mqID2 == -1)
      {
        printf("C2 message queue create error\n");
        perror("MQ: ");
        printf("Error number is: %d", errno);
        exit(0);
      }

      if (mqID2 == -1)
      {
        printf("C1 message send error\n");
        perror("MQ: ");
        printf("Error number is: %d", errno);
        exit(0);
      }

      message m1 = createMsg(1, t2);
      msgsnd(mqID2, &m1, sizeof(t2), IPC_NOWAIT);

      waitpid(cc1, NULL, 0);

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
      perror("C2 fork error: ");
      printf("Error No: %d\n", errno);
      exit(0);
      break;

    // C2 and CC2
    case 0:
      sleep(0.001);
      cc2 = fork();

      switch (cc2)
      {
      // error
      case -1:
        break;

      // CC2
      case 0:;
        sleep(0.001);
        float t5 = 0;

        for (int i = 80; i < 100; i++)
        {
          t5 += totalMarks[i];
        }

        key_t key5 = ftok("file.txt", 30);

        int mqID5 = msgget(key5, 0);
        if (mqID5 == -1)
        {
          printf("C5 message queue create error\n");
          perror("MQ: ");
          printf("Error number is: %d", errno);
          exit(0);
        }

        if (mqID5 == -1)
        {
          printf("CC2 message send error\n");
          perror("MQ: ");
          printf("Error number is: %d", errno);
          exit(0);
        }

        message m5 = createMsg(1, t5);
        msgsnd(mqID5, &m5, sizeof(t5), IPC_NOWAIT);

        break;

      // C2
      default:;
        sleep(0.001);
        float t3 = 0;

        for (int i = 40; i < 60; i++)
        {
          t3 += totalMarks[i];
        }

        key_t key3 = ftok("file.txt", 30);

        int mqID3 = msgget(key3, 0);
        if (mqID3 == -1)
        {
          printf("C2 message queue create error\n");
          perror("MQ: ");
          printf("Error number is: %d", errno);
          exit(0);
        }

        if (mqID3 == -1)
        {
          printf("C2 message send error\n");
          perror("MQ: ");
          printf("Error number is: %d", errno);
          exit(0);
        }

        message m3 = createMsg(1, t3);
        msgsnd(mqID3, &m3, sizeof(t3), IPC_NOWAIT);
        waitpid(cc2, NULL, 0);
        break;
      }

      break;

    // P
    default:;
      key_t key1 = ftok("file.txt", 30);

      // creating the message queue
      int mqID = msgget(key1, 0666);

      if (mqID == -1)
      {
        printf("Parent message queue create error\n");
        perror("MQ: ");
        printf("Error number is: %d", errno);
        exit(0);
      }
      else
      {
        float t1 = 0;
        float subtotal = 0;

        for (int i = 0; i < 20; i++)
        {
          t1 += totalMarks[i];
        }

        waitpid(c2, NULL, 0);

        message receivedMessages[5];

        for (int i = 0; i < 5; i++)
        {
          int x = msgrcv(mqID, receivedMessages + i, sizeof(float), 0, IPC_NOWAIT);
          if (x == -1)
          {
            printf("Parent message queue read error\n");
            perror("MQ: ");
            printf("Error number is: %d", errno);
            exit(0);
          }
          subtotal = subtotal + receivedMessages[i].data;
        }

        subtotal += t1;

        printf("The average is %f\n", subtotal / 100);
        printf("Number of students below 25: %d\n", belowTwntyFive);
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