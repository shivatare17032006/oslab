#include <iostream>
using namespace std;

int main() {

    int choice;

    do {
        cout << "\n===== MEMORY MANAGEMENT =====\n";
        cout << "1. Paging\n";
        cout << "2. Segmentation\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {

        // ---------------- PAGING ----------------
        case 1: {

            int pageSize, logicalAddress;
            int pageNumber, offset;
            int frameNumber;

            cout << "\n--- PAGING ---\n";

            cout << "Enter Page Size: ";
            cin >> pageSize;

            cout << "Enter Logical Address: ";
            cin >> logicalAddress;

            // Calculate page number and offset
            pageNumber = logicalAddress / pageSize;
            offset = logicalAddress % pageSize;

            cout << "Page Number = "
                 << pageNumber << endl;

            cout << "Offset = "
                 << offset << endl;

            cout << "Enter Frame Number for Page "
                 << pageNumber << ": ";

            cin >> frameNumber;

            int physicalAddress =
                (frameNumber * pageSize) + offset;

            cout << "Physical Address = "
                 << physicalAddress << endl;

            break;
        }

        // ---------------- SEGMENTATION ----------------
        case 2: {

            int n;

            cout << "\n--- SEGMENTATION ---\n";

            cout << "Enter Number of Segments: ";
            cin >> n;

            // Dynamic memory allocation
            int *base = new int[n];
            int *limit = new int[n];

            cout << "\nEnter Base Address and Limit "
                 << "for each segment:\n";

            for(int i = 0; i < n; i++) {

                cout << "\nSegment " << i << endl;

                cout << "Base Address: ";
                cin >> base[i];

                cout << "Limit: ";
                cin >> limit[i];
            }

            int segment, offset;

            cout << "\nEnter Segment Number: ";
            cin >> segment;

            cout << "Enter Offset: ";
            cin >> offset;

            if(segment >= 0 && segment < n) {

                if(offset < limit[segment]) {

                    int physicalAddress =
                        base[segment] + offset;

                    cout << "Physical Address = "
                         << physicalAddress << endl;
                }
                else {
                    cout << "Segmentation Fault!"
                         << endl;
                }

            }
            else {
                cout << "Invalid Segment Number!"
                     << endl;
            }

            // Free dynamic memory
            delete[] base;
            delete[] limit;

            break;
        }

        case 3:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while(choice != 3);

    return 0;
}