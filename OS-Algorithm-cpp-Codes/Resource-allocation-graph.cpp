//Resource-Allocation graph:

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100;
const int MAXM = 100;

int n, m;  // n = number of processes, m = number of resources

int available[MAXM];  // available resources
int max_need[MAXN][MAXM];  // max need of each process
int allocated_resources[MAXN][MAXM];  // allocated resources of each process
int need[MAXN][MAXM];  // need of each process

vector<int> graph[MAXN];  // resource allocation graph
int in_degree[MAXN];  // in-degree of each node in the graph

void initialize() {
    memset(in_degree, 0, sizeof(in_degree));
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;
    cout << "Enter the available resources: ";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }
    cout << "Enter the max need of each process: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max_need[i][j];
        }
    }
    cout << "Enter the allocated resources of each process: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocated_resources[i][j];
            need[i][j] = max_need[i][j] - allocated_resources[i][j];
        }
    }
}

void buildGraph() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (need[i][j] <= available[j]) {
                // Process i can request resource j
                graph[i].push_back(j + n);
                in_degree[j + n]++;
            }
        }
    }
}

bool isSafe() {
    queue<int> q;
    vector<int> safe_sequence;
    int work[MAXM];
    memcpy(work, available, sizeof(available));

    // Add all nodes with in-degree 0 to the queue
    for (int i = 0; i < n + m; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // Perform a topological sort of the resource allocation graph
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u < n) {
            // Process u can be allocated resources
            safe_sequence.push_back(u);
            for (int j = 0; j < m; j++) {
                work[j] += allocated_resources[u][j];
            }
        } else {
            // Resource u-n can be allocated to a process
            int v = u - n;
            for (int i = 0; i < graph[v].size(); i++) {
                int w = graph[v][i];
                in_degree[w]--;
                if (in_degree[w] == 0) {
                    q.push(w);
                }
            }
        }
    }

    if (safe_sequence.size() == n) {
        cout << "System is in safe state" << endl;
        cout << "Safe sequence is: ";
        for (int i = 0; i < n; i++){
                cout << "P" << safe_sequence[i] << " ";
        }
        cout << endl;
        return true;
        }
    else {
        cout << "System is not in safe state" << endl;
        return false;
        }
    }

int main() {
    initialize();
    buildGraph();
    isSafe();
    return 0;
}
