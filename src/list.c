/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"

// add a new task to the list of execution tasks
void insertExecutionTask(struct executionNode **head, Task *newTask, int slice)
{
  // add the new task to the list
  struct executionNode *newExecutionNode = malloc(sizeof(struct executionNode));

  newExecutionNode->task = newTask;
  newExecutionNode->slice = slice;
  newExecutionNode->next = *head;
  *head = newExecutionNode;
}

// add a new task to the list of tasks
void insertTask(struct node **head, Task *newTask)
{
  // add the new task to the list
  struct node *newNode = malloc(sizeof(struct node));

  newNode->task = newTask;
  newNode->next = *head;
  *head = newNode;
}

// delete the selected task from the list
void delete(struct node **head, Task *task)
{
  struct node *temp;
  struct node *prev;

  temp = *head;
  // special case - beginning of list
  if (strcmp(task->name, temp->task->name) == 0)
  {
    *head = (*head)->next;
  }
  else
  {
    // interior or last element in the list
    prev = *head;
    temp = temp->next;
    while (strcmp(task->name, temp->task->name) != 0)
    {
      prev = temp;
      temp = temp->next;
    }

    prev->next = temp->next;
  }
}

// traverse the list
void traverseTasks(struct node *head)
{
  struct node *temp;
  temp = head;

  while (temp != NULL)
  {
    printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority, temp->task->burst);
    temp = temp->next;
  }
}

void traverseExecutionTasks(struct executionNode *head)
{
  struct executionNode *temp;
  temp = head;
  Task *task = temp->task;

  while (temp != NULL)
  {
    printf("[%s] [%d] [%d] [%d] [%d]\n", task->name, task->priority, task->burst, task->remainingBurst, temp->slice);
    temp = temp->next;
  }
}