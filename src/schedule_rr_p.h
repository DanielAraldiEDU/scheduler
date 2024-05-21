#define RR_LENGTH 1
#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list
void add(char *name, int priority, int burst);

// list of tasks
void printTasks();

// invoke the scheduler
void schedule();