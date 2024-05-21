#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "schedule_rr_p.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

// priority array
struct node *priorityArray[MAX_PRIORITY];
// counter of priority array
int counterPriorityArray[MAX_PRIORITY] = {0};
// round robin array
struct executionNode *roundRobin[RR_LENGTH];

// add a task to the list
void add(char *name, int priority, int burst)
{
  struct task *newTask = malloc(sizeof(struct task));

  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;
  newTask->remainingBurst = burst;
  const int index = priority - 1;

  counterPriorityArray[index] += 1;
  insertTask(&priorityArray[index], newTask);
}

void printTasks()
{
  for (int i = 0; i < MAX_PRIORITY; i++)
  {
    printf("\nPriority %i:\n", i + 1);
    traverseTasks(priorityArray[i]);
  }
}

// invoke the scheduler
void schedule()
{
  struct executionNode *roundRobin[RR_LENGTH];

  for (int i = 0; i < MAX_PRIORITY; i++)
  {
    if (priorityArray[i] == NULL)
      continue;

    if (priorityArray[i]->next == NULL)
    {
      int slice = priorityArray[i]->task->burst;
      insertExecutionTask(&roundRobin[0], priorityArray[i]->task, slice);
    }
    else
    {
      int counterDone = 0;
      struct node *firstTask = priorityArray[i];
      struct node *currentTask = firstTask;

      while (counterDone < counterPriorityArray[i])
      {
        if (currentTask->task->remainingBurst < QUANTUM)
        {
          insertExecutionTask(&roundRobin[0], currentTask->task, currentTask->task->remainingBurst);
          currentTask->task->remainingBurst = 0;
        }
        else
        {
          insertExecutionTask(&roundRobin[0], currentTask->task, QUANTUM);
          currentTask->task->remainingBurst -= QUANTUM;
        }

        if (currentTask->task->remainingBurst == 0)
          counterDone++;

        if (currentTask->next == NULL)
          currentTask = firstTask;
        else
          currentTask = currentTask->next;
      }
    }
  }

  traverseExecutionTasks(roundRobin[0]);
}