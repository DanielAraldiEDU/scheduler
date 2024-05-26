/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice, int *time)
{
  *time += slice;
  printf("Running task = [%s] [%d] [%d] for %d units.\t(%i time units)\n", task->name, task->priority, task->burst, slice, *time);
}