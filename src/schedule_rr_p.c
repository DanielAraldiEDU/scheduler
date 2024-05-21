#include <stddef.h>
#include <stdlib.h>
#include "schedule_rr_p.h"
#include "list.h"
#include "task.h"

struct node *priorityArray[MAX_PRIORITY];

// add a task to the list
void add(char *name, int priority, int burst)
{
  struct task *newTask = malloc(sizeof(struct task));

  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;

  insert(&priorityArray[priority - 1], newTask);
}

// invoke the scheduler
void schedule()
{
  int x = 0;
}