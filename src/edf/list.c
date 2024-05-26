/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"

// add a new task to the list of tasks
void insertTask(struct taskLue *lue, Task *newTask)
{
  // add the new task to the list
  struct node *newNode = malloc(sizeof(struct node));

  newNode->task = newTask;
  newNode->next = NULL;

  if (lue->start == NULL)
  {
    lue->start = newNode;
    lue->end = newNode;
  }
  else
  {
    lue->end->next = newNode;
    lue->end = newNode;
  }
}

// traverse the task list
void traverseTasks(struct taskLue lue)
{
  struct node *temp = lue.start;
  Task *task;

  while (temp != NULL)
  {
    task = temp->task;
    printf("%s: Priority: [%i] | Burst: [%i]\n", task->name, task->priority, task->burst);
    temp = temp->next;
  }
}

// initialize task lue
void initializeLue(struct taskLue *lue)
{
  lue->start = NULL;
  lue->end = NULL;
}

// reset task list
void resetTasksLue(struct taskLue *lue)
{
  struct node *auxiliary = lue->start;
  struct node *otherAuxiliary;

  while (auxiliary != NULL)
  {
    otherAuxiliary = auxiliary->next;
    free(auxiliary->task);
    free(auxiliary);
    auxiliary = otherAuxiliary;
  }
}

// add a new task to the list of execution tasks
struct executionNode *insertExecutionTask(struct executionLue *lue, Task *newTask, int slice)
{
  // add the new task to the list
  struct executionNode *newExecutionNode = malloc(sizeof(struct executionNode));

  newExecutionNode->task = newTask;
  newExecutionNode->next = NULL;
  newExecutionNode->slice = slice;

  if (lue->start == NULL)
  {
    lue->start = newExecutionNode;
    lue->end = newExecutionNode;
  }
  else
  {
    lue->end->next = newExecutionNode;
    lue->end = newExecutionNode;
  }

  return newExecutionNode;
}

// traverse the execution task list
void traverseExecutionTasks(struct executionLue lue)
{
  struct executionNode *temp = lue.start;
  Task *task;

  while (temp != NULL)
  {
    task = temp->task;
    printf("%s: Priority: [%i] | Burst: [%i] | Slice: [%i] | Deadline: [%i]\n", task->name, task->priority, task->burst, temp->slice, task->deadline);
    temp = temp->next;
  }
}

// initialize execution task lue
void initializeExecutionLue(struct executionLue *lue)
{
  lue->start = NULL;
  lue->end = NULL;
}

// reset execution task lue
void resetExecutionLue(struct executionLue *lue)
{
  struct executionNode *auxiliary = lue->start;
  struct executionNode *otherAuxiliary;

  while (auxiliary != NULL)
  {
    otherAuxiliary = auxiliary->next;
    free(auxiliary);
    auxiliary = otherAuxiliary;
  }
}