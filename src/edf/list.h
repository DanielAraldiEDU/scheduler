/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node
{
  Task *task;
  struct node *next;
};

struct taskLue
{
  struct node *start, *end;
};

// representation of a execution task
struct executionNode
{
  Task *task;
  int slice;
  struct executionNode *next;
};

struct executionLue
{
  struct executionNode *start, *end;
};

// insert and delete operations.
void insertTask(struct taskLue *lue, Task *newTask);
void traverseTasks(struct taskLue lue);
void initializeLue(struct taskLue *lue);
void resetTasksLue(struct taskLue *lue);

struct executionLue *insertExecutionTask(struct executionLue *lue, Task *newTask, int slice);
void traverseExecutionTasks(struct executionLue lue);
void initializeExecutionLue(struct executionLue *lue);
void resetExecutionLue(struct executionLue *lue);