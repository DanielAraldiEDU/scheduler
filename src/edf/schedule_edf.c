#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "schedule_edf.h"
#include "list.h"
#include "task.h"

// add a task to the list
// counter of priority array
int priorityCounterArray[MAX_PRIORITY] = {0};
// priority lue array
struct taskLue priorityArray[MAX_PRIORITY];
// round robin lue
struct executionLue readyQueue;

// add a task to the list
void add(char *name, int priority, int burst, int deadline)
{
  struct task *newTask = malloc(sizeof(struct task));

  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;
  newTask->remainingBurst = burst;
  newTask->deadline = deadline;
  const int index = priority - 1;

  if (priorityCounterArray[index] == 0)
    initializeLue(&priorityArray[index]);

  priorityCounterArray[index] += 1;
  insertTask(&priorityArray[index], newTask);
}

// reset priority array
void resetPriorityArray()
{
  for (int index = 0; index < MAX_PRIORITY; index++)
    resetTasksLue(&priorityArray[index]);
}

// invoke the scheduler
void schedule()
{
  initializeExecutionLue(&readyQueue);

  for (int i = 0; i < MAX_PRIORITY; i++)
  {
    if (priorityArray[i].start == NULL)
      continue;

    if (priorityArray[i].start->next == NULL)
    {
      int slice = priorityArray[i].start->task->burst;
      insertExecutionTask(&readyQueue, priorityArray[i].start->task, slice);
    }
    else
    {
      int doneCounter = 0;
      struct node *firstTask = priorityArray[i].start;
      struct node *currentTask = firstTask;

      while (doneCounter < priorityCounterArray[i])
      {
        if (currentTask->task->remainingBurst == 0)
        {
          if (currentTask->next != NULL)
            currentTask = currentTask->next;
          else
            currentTask = firstTask;

          continue;
        }

        if (currentTask->task->remainingBurst < quantum)
        {
          insertExecutionTask(&readyQueue, currentTask->task, currentTask->task->remainingBurst);
          currentTask->task->remainingBurst = 0;
        }
        else
        {
          insertExecutionTask(&readyQueue, currentTask->task, quantum);
          currentTask->task->remainingBurst -= quantum;
        }

        if (currentTask->task->remainingBurst == 0)
          doneCounter++;

        if (currentTask->next == NULL)
          currentTask = firstTask;
        else
          currentTask = currentTask->next;
      }
    }
  }
}