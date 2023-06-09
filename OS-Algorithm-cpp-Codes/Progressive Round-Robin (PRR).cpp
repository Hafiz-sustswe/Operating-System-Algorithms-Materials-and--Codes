/*Progressive Round-Robin (PRR) : A variation of the RR scheduler where the timequantum is increased by 10% if a process does not complete within it’s entire timequantum. When the time time-quantum increases by 100% and any process blocks before using its entire time quantum, the time quantum will be reduced to it’s default value again. */


#include <iostream>
#include <vector>

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
};

void prr_scheduling(vector<process>& processes, int time_quantum) {
    int current_time = 0;
    int total_processes = processes.size();
    int completed_processes = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    float time_quantum_multiplier = 1.0;
    
    while (completed_processes < total_processes) {
        bool process_completed = false;
        for (int i = 0; i < total_processes; i++) {
            process& current_process = processes[i];
            
            // Check if process has arrived and has remaining burst time
            if (current_process.arrival_time <= current_time && current_process.remaining_time > 0) {
                int time_quantum_used = 0;
                
                // Check if process can complete within the time quantum
                if (current_process.remaining_time <= time_quantum*time_quantum_multiplier) {
                    time_quantum_used = current_process.remaining_time;
                }
                else {
                    time_quantum_used = time_quantum*time_quantum_multiplier;
                }
                
                // Update remaining time for the current process
                current_process.remaining_time -= time_quantum_used;
                current_time += time_quantum_used;
                
                // Update time quantum multiplier if process did not complete within the time quantum
                if (time_quantum_used < time_quantum*time_quantum_multiplier) {
                    time_quantum_multiplier += 0.1;
                }
                
                // Check if process has completed execution
                if (current_process.remaining_time == 0) {
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
                    
                    // Reset time quantum multiplier to 1.0 if process blocked before using its entire time quantum
                    if (time_quantum_used < time_quantum) {
                        time_quantum_multiplier = 1.0;
                    }
                    
                    process_completed = true;
                }
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
    int time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> time_quantum;
    // Input process details
    vector<process> processes(n);
    for (int i = 0; i < n; i++) {
    	processes[i].process_id = i + 1;
    	cout << "Enter arrival time for process " << i+1 << ": ";
    	cin >> processes[i].arrival_time;
    	cout << "Enter burst time for process " << i+1 << ": ";
    	cin >> processes[i].burst_time;
    	processes[i].remaining_time = processes[i].burst_time;
}

// Call PRR scheduling function
prr_scheduling(processes, time_quantum);

return 0;
}

