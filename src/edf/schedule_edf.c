#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "schedule_edf.h"
#include "list.h"
#include "task.h"

// total time burst
int totalTimeBurst = 0;
// task counter
int taskCounter = 0;
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
  newTask->faulted = 0;
  const int index = priority - 1;

  totalTimeBurst += burst;

  if (priorityCounterArray[index] == 0)
    initializeLue(&priorityArray[index]);

  priorityCounterArray[index] += 1;
  insertTask(&priorityArray[index], newTask);

  taskCounter++;
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

  struct executionNode *executingNode = NULL;
  struct task *executingTask = NULL;
  // `isSelected` is boolean value
  int isSelected = 0;
  // `isNewTask` is boolean value
  int isNewTask = 0;
  int time = 0;
  int completedTasksCounter = 0;
  int faultedTasksCounter = 0;

  while (completedTasksCounter + faultedTasksCounter < taskCounter)
  {
    if (executingTask != NULL && executingTask->remainingBurst == 0)
    {
      completedTasksCounter++;
      isSelected = 0;
      executingTask = NULL;
    }

    for (int i = 0; i < MAX_PRIORITY; i++)
    {
      struct node *currentNode = priorityArray[i].start;

      while (currentNode != NULL)
      {
        isNewTask = 0;
        struct task *currentTask = currentNode->task;

        if (currentTask->faulted == 1 || currentTask->remainingBurst == 0)
        {
          currentNode = currentNode->next;
          continue;
        }

        const int currentTaskLoose = currentTask->deadline - currentTask->remainingBurst;
        if (currentTaskLoose < time)
        {
          faultedTasksCounter++;
          currentTask->faulted = 1;
          currentNode = currentNode->next;
          continue;
        }

        if (currentTask != executingTask && currentTaskLoose == time)
        {
          if (executingTask != NULL)
          {
            const int executionTaskLoose = executingTask->deadline - executingTask->remainingBurst;
            if (executingTask->priority <= currentTask->priority)
            {
              if (executionTaskLoose <= time)
              {
                currentNode = currentNode->next;
                continue;
              }
            }
            else
            {
              executingTask->faulted = 1;
            }
            executingNode->slice = time + 1 - executingNode->startTime;
          }

          executingNode = insertExecutionTask(&readyQueue, currentTask, currentTask->burst, time + 1);
          executingTask = currentTask;
          isNewTask = 1;
          isSelected = 1;
          break;
        }

        currentNode = currentNode->next;
      }

      if (isNewTask)
        break;
    }

    for (int i = 0; i < MAX_PRIORITY && executingTask == NULL; i++)
    {
      struct node *currentNode = priorityArray[i].start;
      struct task *earliestDeadlineTask = NULL;

      int priorityCounter = 0;

      while (currentNode != NULL)
      {
        priorityCounter++;
        struct task *currentTask = currentNode->task;

        if (currentTask->faulted == 1 || currentTask->remainingBurst == 0)
        {
          currentNode = currentNode->next;
          continue;
        }

        const int currentTaskLoose = currentTask->deadline - currentTask->remainingBurst;

        if (currentTaskLoose < time)
        {
          faultedTasksCounter++;
          currentTask->faulted = 1;
          currentNode = currentNode->next;
          continue;
        }

        if (earliestDeadlineTask == NULL)
          earliestDeadlineTask = currentTask;
        else if (earliestDeadlineTask->deadline > currentTask->deadline)
          earliestDeadlineTask = currentTask;

        if (priorityCounter == priorityCounterArray[i])
        {
          executingNode = insertExecutionTask(&readyQueue, earliestDeadlineTask, earliestDeadlineTask->burst, time + 1);
          executingTask = earliestDeadlineTask;
          isNewTask = 1;
          isSelected = 1;
          break;
        }
        else
        {
          currentNode = currentNode->next;
        }
      }

      if (isNewTask)
        break;
    }

    if (isSelected)
    {
      if (executingTask->remainingBurst > 0)
      {
        time++;
        executingTask->remainingBurst--;
      }
    }
  }
}