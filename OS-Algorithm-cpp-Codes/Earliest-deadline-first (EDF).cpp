/* Earliest-deadline-first (EDF) : A variant of Priority scheduling where a deadline is
given for each process and this deadline is treated as the priority of that process -
the earlier the deadline, the higher the priority; the later the deadline, the lower the
priority
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int finish_time;
    int deadline;
};

bool compare_deadlines(process p1, process p2) {
    return p1.deadline < p2.deadline;
}

void edf_scheduling(vector<process>& processes) {
    int current_time = 0;
    int total_processes = processes.size();
    int completed_processes = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    
    while (completed_processes < total_processes) {
        // Sort the processes based on their deadlines
        sort(processes.begin(), processes.end(), compare_deadlines);
        
        bool process_completed = false;
        for (int i = 0; i < total_processes; i++) {
            process& current_process = processes[i];
            
            // Check if process has arrived and has remaining burst time
            if (current_process.arrival_time <= current_time && current_process.remaining_time > 0) {
                // Execute the process for its remaining burst time
                current_time += current_process.remaining_time;
                
                // Set finish time for the process
                current_process.finish_time = current_time;
                
                // Set waiting time for the process
                current_process.waiting_time = current_process.finish_time - current_process.arrival_time - current_process.burst_time;
                
                // Set turnaround time for the process
                current_process.turnaround_time = current_process.finish_time - current_process.arrival_time;
                
                // Update total wait time and total turnaround time
                total_wait_time += current_process.waiting_time;
                total_turnaround_time += current_process.turnaround_time;
                
                // Mark the process as completed
                completed_processes++;
                
                process_completed = true;
            }
        }
        
        // If no process has completed, move to the next time unit
        if (!process_completed) {
            current_time++;
        }
    }
    
    // Calculate and print average wait time and average turnaround time
    float avg_wait_time = (float) total_wait_time / total_processes;
    float avg_turnaround_time = (float) total_turnaround_time / total_processes;
    cout << "Average Wait Time: " << avg_wait_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << i+1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter deadline for process " << i+1 << ": ";
        cin >> processes[i].deadline;
        
        // Set remaining time and priority as deadline for EDF scheduling
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].priority = processes[i].deadline;
        processes[i].process_id = i+1;
    }
    
    // Schedule the processes using EDF algorithm
    edf_scheduling(processes);
    
    return 0;
}
