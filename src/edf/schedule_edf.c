#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "schedule_edf.h"
#include "list.h"
#include "task.h"

// total time burst
int totalTimeBurst = 0;
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

  totalTimeBurst += burst;

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

  struct node *currentNode = NULL;
  struct executionNode *currentExecutionNode = NULL;
  struct task *executingTask = NULL;
  struct task *currentTask = NULL;
  // time execution
  int timeExecuting = 0;

  // time
  for (int time = 0; time <= totalTimeBurst; time++)
  {
    // `isSelected` is boolean value
    int isSelected = 0;

    for (int i = 0; i < MAX_PRIORITY; i++)
    {
      currentNode = priorityArray[i].start;
      while (currentNode != NULL)
      {
        currentTask = currentNode->task;

        if (currentTask->remainingBurst > 0)
        {
          if ((currentTask->deadline - currentTask->remainingBurst) == time)
          {
            currentExecutionNode = insertExecutionTask(&readyQueue, currentTask, currentTask->burst);

            if (executingTask != NULL)
            {
              currentExecutionNode->slice = timeExecuting;
              executingTask->remainingBurst = executingTask->burst - timeExecuting;
            }

            executingTask = currentTask;
            isSelected = 1;
            timeExecuting = 0;
            break;
          }
        }

        currentNode = currentNode->next;
      }

      if (isSelected)
        break;
    }

    if (isSelected)
      continue;

    if (executingTask != NULL && timeExecuting < executingTask->remainingBurst)
    {
      timeExecuting++;
      continue;
    }
    else
    {
      if (executingTask != NULL)
        executingTask->remainingBurst = 0;

      timeExecuting = 0;
      executingTask = NULL;
    }

    for (int i = 0; i < MAX_PRIORITY; i++)
    {
      currentNode = priorityArray[i].start;

      while (currentNode != NULL)
      {
        currentTask = currentNode->task;

        if (currentTask->remainingBurst > 0)
        {
          insertExecutionTask(&readyQueue, currentTask, currentTask->burst);
          currentTask->remainingBurst = 0;
          executingTask = currentTask;
          isSelected = 1;
          break;
        }

        currentNode = currentNode->next;
      }

      if (isSelected)
        break;
    }
  }

  // for (int i = 0; i < MAX_PRIORITY; i++)
  // {
  //   traverseTasks(priorityArray[i]);
  // }
  traverseExecutionTasks(readyQueue);
}