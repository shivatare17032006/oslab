#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class DiskScheduling {
    vector<int> req;
    int n, head, size;

public:
    void input() {
        cout << "Enter number of requests: ";
        cin >> n;

        req.resize(n);

        cout << "Enter request queue:\n";
        for (int i = 0; i < n; i++) {
            cin >> req[i];
        }

        cout << "Enter initial head position: ";
        cin >> head;

        cout << "Enter disk size: ";
        cin >> size;
    }

    void fcfs() {
        int total = 0;
        int pos = head;

        cout << "\nFCFS Order: " << pos;

        for (int i = 0; i < n; i++) {
            total += abs(req[i] - pos);
            pos = req[i];

            cout << " -> " << pos;
        }

        cout << "\nFCFS Total Seek Time = " << total << endl;
    }

    void sstf() {
        vector<int> visited(n, 0);

        int total = 0;
        int pos = head;

        cout << "\nSSTF Order: " << pos;

        for (int i = 0; i < n; i++) {
            int mn = 100000;
            int idx = -1;

            for (int j = 0; j < n; j++) {
                if (!visited[j]) {
                    int dist = abs(req[j] - pos);

                    if (dist < mn) {
                        mn = dist;
                        idx = j;
                    }
                }
            }

            visited[idx] = 1;
            total += mn;
            pos = req[idx];

            cout << " -> " << pos;
        }

        cout << "\nSSTF Total Seek Time = " << total << endl;
    }

    void scan() {
        vector<int> temp = req;

        sort(temp.begin(), temp.end());

        int total = 0;
        int pos = head;

        int idx;

        for (idx = 0; idx < n; idx++) {
            if (temp[idx] >= head)
                break;
        }

        cout << "\nSCAN Order: " << pos;

        // Move right
        for (int i = idx; i < n; i++) {
            total += abs(temp[i] - pos);
            pos = temp[i];

            cout << " -> " << pos;
        }

        // Move to end
        total += abs((size - 1) - pos);
        pos = size - 1;

        cout << " -> " << pos;

        // Move left
        for (int i = idx - 1; i >= 0; i--) {
            total += abs(temp[i] - pos);
            pos = temp[i];

            cout << " -> " << pos;
        }

        cout << "\nSCAN Total Seek Time = " << total << endl;
    }

    void cscan() {
        vector<int> temp = req;

        sort(temp.begin(), temp.end());

        int total = 0;
        int pos = head;

        int idx;

        for (idx = 0; idx < n; idx++) {
            if (temp[idx] >= head)
                break;
        }

        cout << "\nC-SCAN Order: " << pos;

        // Move right
        for (int i = idx; i < n; i++) {
            total += abs(temp[i] - pos);
            pos = temp[i];

            cout << " -> " << pos;
        }

        // Move to end
        total += abs((size - 1) - pos);
        pos = size - 1;

        cout << " -> " << pos;

        // Jump to beginning
        total += (size - 1);
        pos = 0;

        cout << " -> " << pos;

        // Continue from start
        for (int i = 0; i < idx; i++) {
            total += abs(temp[i] - pos);
            pos = temp[i];

            cout << " -> " << pos;
        }

        cout << "\nC-SCAN Total Seek Time = " << total << endl;
    }

    void menu() {
        int choice;

        do {
            cout << "\n\n===== Disk Scheduling Menu =====";
            cout << "\n1. FCFS";
            cout << "\n2. SSTF";
            cout << "\n3. SCAN";
            cout << "\n4. C-SCAN";
            cout << "\n5. Run All";
            cout << "\n0. Exit";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    fcfs();
                    break;

                case 2:
                    sstf();
                    break;

                case 3:
                    scan();
                    break;

                case 4:
                    cscan();
                    break;

                case 5:
                    fcfs();
                    sstf();
                    scan();
                    cscan();
                    break;

                case 0:
                    cout << "\nProgram Ended.\n";
                    break;

                default:
                    cout << "\nInvalid Choice!\n";
            }

        } while (choice != 0);
    }
};

int main() {
    DiskScheduling d;

    d.input();
    d.menu();

    return 0;
}