#include <iostream>
using namespace std;

int main() {

    int pages[500];
    int n, f;

cout << "Enter length of page reference string: ";
    cin >> n;

    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> f;

    // ================= FIFO =================

    int fifo[10];
    int front = 0;
    int faults = 0;

    for (int i = 0; i < f; i++) {
        fifo[i] = -1;
    }

    for (int i = 0; i < n; i++) {

        bool found = false;

        // Check page hit
        for (int j = 0; j < f; j++) {
            if (fifo[j] == pages[i]) {
                found = true;
                break;
            }
        }

        // Page fault
        if (!found) {
            fifo[front] = pages[i];
            front = (front + 1) % f;
            faults++;
        }
    }

    cout << "FIFO Page Faults = " << faults << endl;

    // ================= LRU =================

    int lru[10], time[10];
    int count = 0;

    faults = 0;

    for (int i = 0; i < f; i++) {
        lru[i] = -1;
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {

        bool found = false;

        // Check page hit
        for (int j = 0; j < f; j++) {
            if (lru[j] == pages[i]) {
                found = true;
                time[j] = count++;
                break;
            }
        }

        // Page fault
        if (!found) {

            int pos = -1;

            // Find empty frame first
            for (int j = 0; j < f; j++) {
                if (lru[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find LRU page
            if (pos == -1) {
                  
                pos = 0;

                for (int j = 1; j < f; j++) {
                    if (time[j] < time[pos]) {
                        pos = j;
                    }
                }
            }

            lru[pos] = pages[i];
            time[pos] = count++;
            faults++;
        }
    }

    cout << "LRU Page Faults = " << faults << endl;

    // ================= OPTIMAL =================

    int opt[10];

    faults = 0;

    for (int i = 0; i < f; i++) {
        opt[i] = -1;
    }

    for (int i = 0; i < n; i++) {

        bool found = false;

        // Check page hit
        for (int j = 0; j < f; j++) {
            if (opt[j] == pages[i]) {
                found = true;
                break;
            }
        }

        // Page fault
        if (!found) {

            int pos = -1;
            int farthest = -1;

            // Check for empty frame first
            for (int j = 0; j < f; j++) {
                if (opt[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, apply Optimal logic
            if (pos == -1) {

                for (int j = 0; j < f; j++) {

                    int k;

                    for (k = i + 1; k < n; k++) {
                        if (opt[j] == pages[k]) {
                            break;
                        }
                    }

                    // Page not used again
                    if (k == n) {
                        pos = j;
                        break;
                    }

                    // Find farthest used page
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            opt[pos] = pages[i];
            faults++;
        }
    }

    cout << "Optimal Page Faults = " << faults << endl;

    return 0;
}