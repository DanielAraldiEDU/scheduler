/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node
{
  Task *task;
  struct node *next;
};

// representation of a execution task
struct executionNode
{
  Task *task;
  int slice;
  struct executionNode *next;
};

// insert and delete operations.
void insertExecutionTask(struct executionNode **head, Task *newTask, int slice);
void traverseExecutionTasks(struct executionNode *head);
void insertTask(struct node **head, Task *newTask);
void delete(struct node **head, Task *task);
void traverseTasks(struct node *head);