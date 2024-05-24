/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedule_rr_p.h"
#include "cpu.h"
// #include "schedule_edf.h"

#define SIZE 100

int main(int argc, char *argv[])
{
  FILE *in = NULL;
  char *temp = NULL;
  char task[SIZE];

  char *name;
  int priority;
  int burst;
  int deadline;

  in = fopen(argv[1], "r");

  while (fgets(task, SIZE, in) != NULL)
  {
    temp = strdup(task);
    name = strsep(&temp, ",");
    priority = atoi(strsep(&temp, ","));
    burst = atoi(strsep(&temp, ","));
    // Only to EDF algorithm
    // deadline = atoi(strsep(&temp, ","));

    // add the task to the scheduler's list of tasks
    // printf("%s, %i, %i\n", name, priority, burst);
    add(name, priority, burst);

    // to EDF only
    // add(name, priority, burst, deadline);
    // printf("%s, %i, %i, %i\n", name, priority, burst, deadline);

    free(temp);
  }

  fclose(in);

  // invoke the scheduler
  int quantum = QUANTUM;
  schedule(quantum);

  // execute the tasks in the ready queue
  struct executionNode *currentTask = readyQueue.start;
  int time = 0;

  while (currentTask != NULL)
  {
    run(currentTask->task, currentTask->slice, &time);
    currentTask = currentTask->next;
  }

  // free the memory
  resetExecutionLue(&readyQueue);
  resetPriorityArray();
  return 0;
}