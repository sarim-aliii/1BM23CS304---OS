// Write a C program to simulate the following CPU scheduling
// algorithm to find turnaround time and waiting time. a) FCFS
// b) SJF
// c) Priority
// d) Round Robin (Experiment with different quantum sizes
// for RR algorithm)
#include <stdio.h>

#define MAX 10

struct Process {
    int pid; // Process ID
    int bt;  // Burst time
    int wt;  // Waiting time
    int tat; // Turnaround time
    int priority; // Priority (only used in Priority Scheduling)
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].wt = 0; // First process has zero waiting time

    // Calculate waiting time for the remaining processes
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i-1].bt + proc[i-1].wt;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void findAverageTime(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
}

void FCFS(struct Process proc[], int n) {
    printf("\nFCFS Scheduling:\n");
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d: Waiting Time = %d, Turnaround Time = %d", proc[i].pid, proc[i].wt, proc[i].tat);
    }

    findAverageTime(proc, n);
}

void SJF(struct Process proc[], int n) {
    struct Process temp;
    
    // Sorting processes by burst time (Shortest Job First)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].bt > proc[j].bt) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    printf("\nSJF Scheduling:\n");
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d: Waiting Time = %d, Turnaround Time = %d", proc[i].pid, proc[i].wt, proc[i].tat);
    }

    findAverageTime(proc, n);
}

// Function to implement Priority Scheduling (non-preemptive)
void PriorityScheduling(struct Process proc[], int n) {
    struct Process temp;

    // Sorting by priority (higher number means higher priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].priority < proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    printf("\nPriority Scheduling:\n");
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d: Waiting Time = %d, Turnaround Time = %d", proc[i].pid, proc[i].wt, proc[i].tat);
    }

    findAverageTime(proc, n);
}

// Function to implement Round Robin (RR)
void RoundRobin(struct Process proc[], int n, int quantum) {
    int remaining_bt[MAX], time = 0;
    int flag = 0, i;

    // Initializing the remaining burst time for each process
    for (i = 0; i < n; i++) {
        remaining_bt[i] = proc[i].bt;
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);

    while (1) {
        flag = 1;

        for (i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                flag = 0;
                if (remaining_bt[i] > quantum) {
                    remaining_bt[i] -= quantum;
                    time += quantum;
                } else {
                    time += remaining_bt[i];
                    proc[i].wt = time - proc[i].bt;
                    remaining_bt[i] = 0;
                }
            }
        }

        if (flag == 1)
            break;
    }

    // Calculating turnaround time
    for (i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
        printf("\nProcess %d: Waiting Time = %d, Turnaround Time = %d", proc[i].pid, proc[i].wt, proc[i].tat);
    }

    findAverageTime(proc, n);
}

int main() {
    int n, choice, quantum;
    struct Process proc[MAX];

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nEnter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        proc[i].priority = 0; // default priority 0 for non-priority scheduling
    }

    // Menu for choosing scheduling algorithm
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            FCFS(proc, n);
            break;
        case 2:
            SJF(proc, n);
            break;
        case 3:
            // Input priorities for processes
            for (int i = 0; i < n; i++) {
                printf("Enter Priority for Process %d: ", i + 1);
                scanf("%d", &proc[i].priority);
            }
            PriorityScheduling(proc, n);
            break;
        case 4:
            // Input the quantum size
            printf("Enter quantum size for Round Robin: ");
            scanf("%d", &quantum);
            RoundRobin(proc, n, quantum);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}




// multi-level queue scheduling
#include <stdio.h>

#define MAX 10

// Structure to represent each process
struct Process {
    int pid;  // Process ID
    int bt;   // Burst time
    int wt;   // Waiting time
    int tat;  // Turnaround time
    int type; // Type of process: 0 for system, 1 for user
};

// Function to calculate waiting time and turnaround time for FCFS
void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].wt = 0; // First process has zero waiting time

    // Calculate waiting time for the remaining processes
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i-1].bt + proc[i-1].wt;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void findAverageTime(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
}

// Function to execute FCFS scheduling
void FCFS(struct Process proc[], int n) {
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d: Waiting Time = %d, Turnaround Time = %d", proc[i].pid, proc[i].wt, proc[i].tat);
    }

    findAverageTime(proc, n);
}

// Function to simulate multi-level queue scheduling
void multiLevelQueueScheduling(struct Process proc[], int n) {
    struct Process systemQueue[MAX], userQueue[MAX];
    int sysCount = 0, userCount = 0;

    // Divide the processes into system and user queues
    for (int i = 0; i < n; i++) {
        if (proc[i].type == 0) {
            systemQueue[sysCount++] = proc[i];
        } else {
            userQueue[userCount++] = proc[i];
        }
    }

    printf("\nSystem Processes Scheduling (FCFS):\n");
    FCFS(systemQueue, sysCount);

    printf("\nUser Processes Scheduling (FCFS):\n");
    FCFS(userQueue, userCount);
}

int main() {
    int n, choice;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[MAX];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nEnter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter Process Type (0 for System, 1 for User): ");
        scanf("%d", &proc[i].type);
    }

    // Call Multi-level Queue Scheduling function
    multiLevelQueueScheduling(proc, n);

    return 0;
}




// Write a C program to simulate Real-Time CPU Scheduling
// algorithms:
// a) Rate- Monotonic
// b) Earliest-deadline First
// c) Proportional scheduling
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure to represent each process
struct Process {
    int pid;          // Process ID
    int bt;           // Burst time
    int period;       // Period (for Rate-Monotonic)
    int deadline;     // Deadline (for EDF)
    int priority;     // Priority (for Proportional Scheduling)
    int remaining_bt; // Remaining burst time (for execution tracking)
};

// Function to sort processes based on burst time for Proportional Scheduling
void sortByBurstTime(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].bt > proc[j].bt) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to sort processes based on period for Rate-Monotonic Scheduling
void sortByPeriod(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].period > proc[j].period) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to sort processes based on deadline for Earliest-Deadline First Scheduling
void sortByDeadline(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].deadline > proc[j].deadline) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time for each scheduling algorithm
void calculateWaitingTime(struct Process proc[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        proc[i].remaining_bt = proc[i].bt; // Reset remaining burst time
    }
    
    for (int i = 0; i < n; i++) {
        time += proc[i].bt;
        proc[i].priority = time; // This is just an example of tracking time, not an actual priority calculation
    }
}

// Function to simulate Rate-Monotonic Scheduling
void RateMonotonic(struct Process proc[], int n) {
    // Sort the processes by their period (shortest period = highest priority)
    sortByPeriod(proc, n);

    int time = 0;
    printf("\nRate-Monotonic Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Burst Time = %d, Period = %d, Deadline = %d\n", 
            proc[i].pid, proc[i].bt, proc[i].period, proc[i].deadline);
        time += proc[i].bt;
    }
}

// Function to simulate Earliest-Deadline First Scheduling
void EarliestDeadlineFirst(struct Process proc[], int n) {
    // Sort the processes by their deadline (earliest deadline = highest priority)
    sortByDeadline(proc, n);

    int time = 0;
    printf("\nEarliest-Deadline First Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Burst Time = %d, Deadline = %d\n", proc[i].pid, proc[i].bt, proc[i].deadline);
        time += proc[i].bt;
    }
}

// Function to simulate Proportional Scheduling
void ProportionalScheduling(struct Process proc[], int n) {
    // Sort the processes by burst time (shortest burst time = highest priority)
    sortByBurstTime(proc, n);

    int time = 0;
    printf("\nProportional Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Burst Time = %d\n", proc[i].pid, proc[i].bt);
        time += proc[i].bt;
    }
}

int main() {
    int n, choice;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[MAX];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nEnter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);

        // Input for Rate-Monotonic and Earliest-Deadline First
        printf("Enter Period for Process %d (for Rate-Monotonic): ", i + 1);
        scanf("%d", &proc[i].period);

        printf("Enter Deadline for Process %d (for EDF): ", i + 1);
        scanf("%d", &proc[i].deadline);
    }

    // Menu for selecting the scheduling algorithm
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Rate-Monotonic Scheduling\n");
    printf("2. Earliest-Deadline First\n");
    printf("3. Proportional Scheduling\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            RateMonotonic(proc, n);
            break;
        case 2:
            EarliestDeadlineFirst(proc, n);
            break;
        case 3:
            ProportionalScheduling(proc, n);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}





// Write a C program to simulate: 
// a) Producer-Consumer problem using semaphores.
// b) Dining-Philosopher’s problem
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&empty);     // Decrease empty slot count
        sem_wait(&mutex);     // Acquire mutex lock to access the buffer

        // Produce item (add to buffer)
        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);     // Release mutex lock
        sem_post(&full);      // Increase full slot count
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);      // Decrease full slot count
        sem_wait(&mutex);     // Acquire mutex lock to access the buffer

        // Consume item (remove from buffer)
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);     // Release mutex lock
        sem_post(&empty);     // Increase empty slot count
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, all slots are empty
    sem_init(&full, 0, 0);              // Initially, no slots are filled
    sem_init(&mutex, 0, 1);             // Mutex is initially unlocked

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}





// Write a C program to simulate: 
// a) Bankers’ algorithm for the purpose of deadlock
// avoidance.
// b) Deadlock Detection
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if the system is in a safe state
bool isSafe(int processes, int resources, int allocation[processes][resources], int max[processes][resources], int available[resources]) {
    int need[processes][resources];
    int work[resources];
    bool finish[processes];
    
    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Initialize work and finish arrays
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }
    
    // Try to find a safe sequence
    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < resources; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Pretend to allocate resources
                    for (int r = 0; r < resources; r++) {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = true;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return false; // No process can proceed, hence deadlock
        }
    }
    return true; // All processes can finish
}

int main() {
    int processes = 5;
    int resources = 3;
    
    // Example matrices for the system
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    // Check if the system is in a safe state
    if (isSafe(processes, resources, allocation, max, available)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}




// Deadlock
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to detect deadlock by checking if all processes can eventually finish
bool detectDeadlock(int processes, int resources, int allocation[processes][resources], int max[processes][resources], int available[resources]) {
    int need[processes][resources];
    int work[resources];
    bool finish[processes];
    
    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work and finish arrays
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    // Try to find a process that can finish
    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < resources; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Pretend to allocate resources
                    for (int r = 0; r < resources; r++) {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = true;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return true; // Deadlock detected, no process can finish
        }
    }

    return false; // No deadlock, all processes can finish
}

int main() {
    int processes = 5;
    int resources = 3;
    
    // Example matrices for the system
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    // Check for deadlock
    if (detectDeadlock(processes, resources, allocation, max, available)) {
        printf("Deadlock detected in the system.\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}




// Write a C program to simulate the following contiguous
// memory allocation techniques. (Any one)
// a) Worst-fit
// b) Best-fit
// c) First-fit 
#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

int main() {
    int m, n;
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];

   
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);


    printf("\nEnter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }


    printf("\nEnter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    printf("\nMemory Allocation using First Fit:\n");
    firstFit(blockSize, m, processSize, n);

    printf("\nMemory Allocation using Best Fit:\n");
    bestFit(blockSize, m, processSize, n);

    printf("\nMemory Allocation using Worst Fit:\n");
    worstFit(blockSize, m, processSize, n);

    return 0;
}


void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; 
    }

   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }


    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d could not be allocated\n", i + 1);
        }
    }
}


void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d could not be allocated\n", i + 1);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; 
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d could not be allocated\n", i + 1);
        }
    }
}



// Write a C program to simulate page replacement algorithms.
// a) FIFO
// b) LRU
// c) Optimal 
#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

// Function to implement FIFO page replacement algorithm
void fifo(int pages[], int n, int frames[], int m) {
    int page_faults = 0, k = 0;
    int page_in_frame = 0;
    int frame_filled = 0;

    for (int i = 0; i < n; i++) {
        page_in_frame = 0;
        
        // Check if page is already in the frame
        for (int j = 0; j < m; j++) {
            if (pages[i] == frames[j]) {
                page_in_frame = 1;
                break;
            }
        }

        // If page is not in frame, page fault occurs
        if (!page_in_frame) {
            frames[k] = pages[i];
            k = (k + 1) % m;
            page_faults++;
        }

        // Print the current page frame state
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < m; j++) {
            if (frames[j] == -1)
                printf("_ ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("FIFO Page Faults: %d\n", page_faults);
}

// Function to implement LRU page replacement algorithm
void lru(int pages[], int n, int frames[], int m) {
    int page_faults = 0;
    int last_used[MAX_FRAMES] = {0};

    for (int i = 0; i < n; i++) {
        int page_in_frame = 0, least_recently_used = 0;

        // Check if page is already in the frame
        for (int j = 0; j < m; j++) {
            if (pages[i] == frames[j]) {
                page_in_frame = 1;
                last_used[j] = i; // Update last used time
                break;
            }
        }

        // If page is not in frame, page fault occurs
        if (!page_in_frame) {
            int min_time = n + 1;
            for (int j = 0; j < m; j++) {
                if (frames[j] == -1 || last_used[j] < min_time) {
                    least_recently_used = j;
                    min_time = last_used[j];
                }
            }
            frames[least_recently_used] = pages[i];
            last_used[least_recently_used] = i;
            page_faults++;
        }

        // Print the current page frame state
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < m; j++) {
            if (frames[j] == -1)
                printf("_ ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("LRU Page Faults: %d\n", page_faults);
}

// Function to implement Optimal page replacement algorithm
int findOptimal(int frames[], int m, int pages[], int n, int current_index) {
    int farthest = current_index;
    int index_to_replace = -1;

    for (int i = 0; i < m; i++) {
        int j;
        for (j = current_index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index_to_replace = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return index_to_replace;
}

void optimal(int pages[], int n, int frames[], int m) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page_in_frame = 0;

        // Check if page is already in the frame
        for (int j = 0; j < m; j++) {
            if (pages[i] == frames[j]) {
                page_in_frame = 1;
                break;
            }
        }

        // If page is not in frame, page fault occurs
        if (!page_in_frame) {
            int replace_index = findOptimal(frames, m, pages, n, i + 1);
            frames[replace_index] = pages[i];
            page_faults++;
        }

        // Print the current page frame state
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < m; j++) {
            if (frames[j] == -1)
                printf("_ ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Optimal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, m;

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &m);

    // Initialize frames with -1 (empty)
    for (int i = 0; i < m; i++) {
        frames[i] = -1;
    }

    // Simulate FIFO page replacement
    printf("\nFIFO Page Replacement:\n");
    fifo(pages, n, frames, m);

    // Reset frames for LRU and Optimal simulations
    for (int i = 0; i < m; i++) {
        frames[i] = -1;
    }

    // Simulate LRU page replacement
    printf("\nLRU Page Replacement:\n");
    lru(pages, n, frames, m);

    // Reset frames for Optimal simulation
    for (int i = 0; i < m; i++) {
        frames[i] = -1;
    }

    // Simulate Optimal page replacement
    printf("\nOptimal Page Replacement:\n");
    optimal(pages, n, frames, m);

    return 0;
}
