#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n, m;

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    // Input number of resources
    cout << "Enter number of resources: ";
    cin >> m;

    // Dynamic matrices using vector
    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> req(n, vector<int>(m));

    // Resource vectors
    vector<int> avail(m);
    vector<int> work(m);
    vector<int> finish(n, 0);

    // Input Allocation Matrix
    cout << "Enter Allocation Matrix:\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {

            cin >> alloc[i][j];
        }
    }

    // Input Request Matrix
    cout << "Enter Request Matrix:\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {

            cin >> req[i][j];
        }
    }

    // Input Available Resources
    cout << "Enter Available Resources:\n";

    for (int i = 0; i < m; i++) {

        cin >> avail[i];

        // Copy available resources into work vector
        work[i] = avail[i];
    }

    int count = 0;

    // Deadlock Detection Algorithm
    while (count < n) {

        bool found = false;

        // Check every process
        for (int i = 0; i < n; i++) {

            // Process not finished
            if (finish[i] == 0) {

                bool canalloc = true;

                // Check if request <= available resources
                for (int j = 0; j < m; j++) {

                    if (req[i][j] > work[j]) {

                        canalloc = false;
                        break;
                    }
                }

                // Process can execute
                if (canalloc) {

                    // Release allocated resources
                    for (int j = 0; j < m; j++) {

                        work[j] += alloc[i][j];
                    }

                    // Mark process finished
                    finish[i] = 1;

                    found = true;

                    count++;
                }
            }
        }

        // No process can execute
        if (!found)
            break;
    }

    // Final Deadlock Check
    bool deadlock = false;

    for (int i = 0; i < n; i++) {

        if (finish[i] == 0) {

            deadlock = true;
            break;
        }
    }

    // Output Result
    if (deadlock)

        cout << "Deadlock Detected\n";

    else

        cout << "No Deadlock Detected\n";

    return 0;
}