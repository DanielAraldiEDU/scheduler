#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// round robin lue
extern struct executionLue readyQueue;

// add a task to the list
void add(char *name, int priority, int burst);

// reset priority array
void resetPriorityArray();

// invoke the scheduler
void schedule(int quantum);