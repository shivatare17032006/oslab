#include <iostream>
using namespace std;

void calculateNeed(int n, int m, int alloc[][10], int maxm[][10], int need[][10]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];
}

void displayMatrices(int n, int m, int alloc[][10], int maxm[][10], int need[][10], int avail[]) {
    cout << "\n--- Current System State ---\n";

    cout << "\nAllocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cout << alloc[i][j] << " ";
        cout << endl;
    }

    cout << "\nMax Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cout << maxm[i][j] << " ";
        cout << endl;
    }

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    cout << "\nAvailable Resources:\n";
    for (int i = 0; i < m; i++)
        cout << avail[i] << " ";
    cout << endl;
}

bool checkSafety(int n, int m, int alloc[][10], int need[][10], int avail[], int safeSeq[]) {
    int work[10], finish[10];

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                bool canAllocate = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in safe state!\n";
            return false;
        }
    }

    cout << "\nSystem is in SAFE state!\nSafe sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return true;
}

bool requestResources(int n, int m, int alloc[][10], int need[][10], int avail[], int process, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            cout << "Error: Request exceeds maximum claim!\n";
            return false;
        }
        if (request[i] > avail[i]) {
            cout << "Resources not available. Process must wait!\n";
            return false;
        }
    }

    int tempAvail[10];
    int tempAlloc[10][10], tempNeed[10][10];

    for (int i = 0; i < m; i++)
        tempAvail[i] = avail[i] - request[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tempAlloc[i][j] = alloc[i][j];
            tempNeed[i][j] = need[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        tempAlloc[process][i] += request[i];
        tempNeed[process][i] -= request[i];
    }

    int safeSeq[10];
    if (checkSafety(n, m, tempAlloc, tempNeed, tempAvail, safeSeq)) {
        for (int i = 0; i < m; i++) {
            avail[i] = tempAvail[i];
            alloc[process][i] = tempAlloc[process][i];
            need[process][i] = tempNeed[process][i];
        }

        cout << "Request granted!\n";
        return true;
    } else {
        cout << "Request denied (unsafe state)!\n";
        return false;
    }
}

int main() {
    int n, m, choice;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[10][10], maxm[10][10], need[10][10], avail[10];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxm[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    calculateNeed(n, m, alloc, maxm, need);

    do {
        cout << "\n===== BANKER'S ALGORITHM MENU =====\n";
        cout << "1. Display System State\n";
        cout << "2. Check Safety\n";
        cout << "3. Request Resources\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMatrices(n, m, alloc, maxm, need, avail);
                break;

            case 2: {
                int safeSeq[10];
                checkSafety(n, m, alloc, need, avail, safeSeq);
                break;
            }

            case 3: {
                int process, request[10];

                cout << "Enter process number: ";
                cin >> process;

                cout << "Enter request:\n";
                for (int i = 0; i < m; i++)
                    cin >> request[i];

                requestResources(n, m, alloc, need, avail, process, request);
                break;
            }

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}