// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_PROCESSES 10
// #define MAX_NAME_LENGTH 20

// typedef struct {
//     int pid;  
//     char name[MAX_NAME_LENGTH]; 
//     int burst_time;  
// } Process;


// void FCFS(Process queue[], int n) {
//     int total_wait_time = 0, total_turnaround_time = 0;
//     printf("\nScheduling processes with FCFS...\n");
//     printf("PID\tName\tBurst Time\tWaiting Time\tTurnaround Time\n");                     

//     int waiting_time = 0;  
//     for (int i = 0; i < n; i++) {
//         int turnaround_time = queue[i].burst_time + waiting_time;
//         printf("%d\t%s\t%d\t\t%d\t\t%d\n", queue[i].pid, queue[i].name, queue[i].burst_time, waiting_time, turnaround_time);
       
//         total_wait_time += waiting_time;
//         total_turnaround_time += turnaround_time;
       
//         waiting_time += queue[i].burst_time;  
//     }
   
//     printf("\nAverage Waiting Time: %.2f\n", (float)total_wait_time / n);
//     printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
// }

// void input_processes(Process queue[], int *n) {
//     printf("Enter the number of processes: ");
//     scanf("%d", n);

//     for (int i = 0; i < *n; i++) {
//         queue[i].pid = i + 1;
//         printf("Enter the name of process %d: ", i + 1);
//         scanf("%s", queue[i].name);
//         printf("Enter the burst time of process %d: ", i + 1);
//         scanf("%d", &queue[i].burst_time);
//     }
// }

// int main() {
//     Process system_queue[MAX_PROCESSES], user_queue[MAX_PROCESSES];
//     int system_count, user_count;

//     printf("Enter details for system processes:\n");
//     input_processes(system_queue, &system_count);

//     printf("\nEnter details for user processes:\n");
//     input_processes(user_queue, &user_count);

//     printf("\nScheduling system processes:\n");
//     FCFS(system_queue, system_count);

//     printf("\nScheduling user processes:\n");
//     FCFS(user_queue, user_count);

//     return 0;
// }





// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_TASKS 10

// typedef struct {
//     int id;
//     int period;
//     int execution_time;
//     int remaining_time;
// } Task;

// void sort_by_priority(Task tasks[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (tasks[j].period > tasks[j + 1].period) {
//                 Task temp = tasks[j];
//                 tasks[j] = tasks[j + 1];
//                 tasks[j + 1] = temp;
//             }
//         }
//     }
// }

// void rms_scheduling(Task tasks[], int n, int total_time) {
//     sort_by_priority(tasks, n);

//     for (int t = 0; t < total_time; t++) {
//         int executed = 0;
//         for (int i = 0; i < n; i++) {
//             if (tasks[i].remaining_time > 0) {
//                 printf("Time %d: Executing Task %d\n", t, tasks[i].id);
//                 tasks[i].remaining_time--;

//                 if (tasks[i].remaining_time == 0)
//                     tasks[i].remaining_time = tasks[i].execution_time; // Reset for next period
                
//                 executed = 1;
//                 break;
//             }
//         }
//         if (!executed) {
//             printf("Time %d: Idle\n", t);
//         }
//     }
// }

// int main() {
//     Task tasks[MAX_TASKS] = {
//         {1, 3, 1, 1},
//         {2, 5, 2, 2},
//         {3, 7, 2, 2}
//     };
//     int num_tasks = 3;
//     int total_time = 15; // Simulation time

//     rms_scheduling(tasks, num_tasks, total_time);
//     return 0;
// }






// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_TASKS 10

// typedef struct {
//     int id;
//     int deadline;
//     int execution_time;
//     int remaining_time;
// } Task;

// void sort_by_deadline(Task tasks[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (tasks[j].deadline > tasks[j + 1].deadline) {
//                 Task temp = tasks[j];
//                 tasks[j] = tasks[j + 1];
//                 tasks[j + 1] = temp;
//             }
//         }
//     }
// }

// void edf_scheduling(Task tasks[], int n, int total_time) {
//     for (int t = 0; t < total_time; t++) {
//         sort_by_deadline(tasks, n);
        
//         int executed = 0;
//         for (int i = 0; i < n; i++) {
//             if (tasks[i].remaining_time > 0) {
//                 printf("Time %d: Executing Task %d\n", t, tasks[i].id);
//                 tasks[i].remaining_time--;

//                 if (tasks[i].remaining_time == 0)
//                     tasks[i].remaining_time = tasks[i].execution_time; // Reset for next cycle

//                 executed = 1;
//                 break;
//             }
//         }
//         if (!executed) {
//             printf("Time %d: Idle\n", t);
//         }
//     }
// }

// int main() {
//     Task tasks[MAX_TASKS] = {
//         {1, 3, 1, 1},
//         {2, 5, 2, 2},
//         {3, 7, 2, 2}
//     };
//     int num_tasks = 3;
//     int total_time = 15; // Simulation time

//     edf_scheduling(tasks, num_tasks, total_time);
//     return 0;
// }