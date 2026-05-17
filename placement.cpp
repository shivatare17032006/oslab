#include <iostream>
#include <vector>
using namespace std;


// ---------------- FIRST FIT ----------------
void firstFit(vector<int> block, const vector<int> &process) {
    cout << "\nFirst Fit:\n";

    for (int i = 0; i < process.size(); i++) {
        bool allocated = false;

        for (int j = 0; j < block.size(); j++) {
            if (block[j] >= process[i]) {
                cout << "Process P" << i << " -> Block B" << j << "\n";
                block[j] -= process[i];
                allocated = true;
                break;
            }
        }

        if (!allocated)
            cout << "Process P" << i << " -> Not Allocated\n";
    }
}

// ---------------- BEST FIT ----------------
void bestFit(vector<int> block, const vector<int> &process) {
    cout << "\nBest Fit:\n";

    for (int i = 0; i < process.size(); i++) {
        int best = -1;

        for (int j = 0; j < block.size(); j++) {
            if (block[j] >= process[i]) {
                if (best == -1 || block[j] < block[best])
                    best = j;
            }
        }

        if (best != -1) {
            cout << "Process P" << i << " -> Block B" << best << "\n";
            block[best] -= process[i];
        } else {
            cout << "Process P" << i << " -> Not Allocated\n";
        }
    }
}

// ---------------- WORST FIT ----------------
void worstFit(vector<int> block, const vector<int> &process) {
    cout << "\nWorst Fit:\n";

    for (int i = 0; i < process.size(); i++) {
        int worst = -1;

        for (int j = 0; j < block.size(); j++) {
            if (block[j] >= process[i]) {
                if (worst == -1 || block[j] > block[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            cout << "Process P" << i << " -> Block B" << worst << "\n";
            block[worst] -= process[i];
        } else {
            cout << "Process P" << i << " -> Not Allocated\n";
        }
    }
}

// ---------------- NEXT FIT ----------------
void nextFit(vector<int> block, const vector<int> &process) {
    cout << "\nNext Fit:\n";

    int last = 0;

    for (int i = 0; i < process.size(); i++) {

        int count = 0;
        bool allocated = false;

        while (count < block.size()) {

            if (block[last] >= process[i]) {

                cout << "Process P" << i
                     << " -> Block B" << last << "\n";

                block[last] -= process[i];

                allocated = true;

                // next search starts from next block
                last = (last + 1) % block.size();

                break;
            }

            last = (last + 1) % block.size();
            count++;
        }

        if (!allocated)
            cout << "Process P" << i
                 << " -> Not Allocated\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    int nb, np;

    cout << "Enter number of memory blocks: ";
    cin >> nb;

    cout << "Enter number of processes: ";
    cin >> np;

    vector<int> block(nb), original(nb), process(np);

    cout << "Enter block sizes:\n";
    for (int i = 0; i < nb; i++) {
        cin >> block[i];
        original[i] = block[i];
    }

    cout << "Enter process sizes:\n";
    for (int i = 0; i < np; i++)
        cin >> process[i];

    int choice;

    do {
        cout << "\n--- Memory Allocation Menu ---\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                firstFit(original, process);
                break;
            case 2:
                bestFit(original, process);
                break;
            case 3:
                worstFit(original, process);
                break;
            case 4:
                nextFit(original, process);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}