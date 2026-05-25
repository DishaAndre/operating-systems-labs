#include <iostream>
#include <iomanip>
using namespace std;

// Function Declarations
int FCFS(int ref[], int n, int f);
int LRU(int ref[], int n, int f);
int Optimal(int ref[], int n, int f);

// Print Frames
void printFrames(int frames[], int f, int page, bool fault) {
    cout << "Page " << page << " -> ";
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            cout << "_ ";
        else
            cout << frames[i] << " ";
    }
    if (fault) cout << " F";
    cout << endl;
}

// FCFS (FIFO)
int FCFS(int ref[], int n, int f) {
    int frames[10], front = 0;
    int faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;

        for (int j = 0; j < f; j++)
            if (frames[j] == page)
                found = 1;

        if (!found) {
            frames[front] = page;
            front = (front + 1) % f;
            faults++;
            printFrames(frames, f, page, true);
        } else {
            printFrames(frames, f, page, false);
        }
    }
    return faults;
}

// LRU
int LRU(int ref[], int n, int f) {
    int frames[10], recent[10];
    int faults = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                recent[j] = i;
            }
        }

        if (!found) {
            int pos = -1;

            // Empty frame
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Find LRU
            if (pos == -1) {
                int min = recent[0];
                pos = 0;
                for (int j = 1; j < f; j++) {
                    if (recent[j] < min) {
                        min = recent[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
            recent[pos] = i;
            faults++;

            printFrames(frames, f, page, true);
        } else {
            printFrames(frames, f, page, false);
        }
    }
    return faults;
}

// Optimal
int Optimal(int ref[], int n, int f) {
    int frames[10];
    int faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;

        for (int j = 0; j < f; j++)
            if (frames[j] == page)
                found = 1;

        if (!found) {
            int pos = -1;

            // Empty frame
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Find Optimal
            if (pos == -1) {
                int farthest = -1;

                for (int j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == ref[k])
                            break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
            faults++;

            printFrames(frames, f, page, true);
        } else {
            printFrames(frames, f, page, false);
        }
    }
    return faults;
}

// MAIN (Menu Driven)
int main() {
    int n, f;

    cout << "Enter size of reference string: ";
    cin >> n;

    int ref[50];
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++)
        cin >> ref[i];

    cout << "Enter number of frames: ";
    cin >> f;

    int choice;

    while (true) {
        cout << "\n1. FCFS\n2. LRU\n3. Optimal\n4. Compare All\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- FCFS ---\n";
                int faults = FCFS(ref, n, f);
                cout << "\nTotal FCFS Page Faults = " << faults << endl;
                break;
            }

            case 2: {
                cout << "\n--- LRU ---\n";
                int faults = LRU(ref, n, f);
                cout << "\nTotal LRU Page Faults = " << faults << endl;
                break;
            }

            case 3: {
                cout << "\n--- Optimal ---\n";
                int faults = Optimal(ref, n, f);
                cout << "\nTotal Optimal Page Faults = " << faults << endl;
                break;
            }

            case 4: {
                cout << "\n----- FCFS -----\n";
                int a = FCFS(ref, n, f);

                cout << "\n----- LRU -----\n";
                int b = LRU(ref, n, f);

                cout << "\n----- Optimal -----\n";
                int c = Optimal(ref, n, f);

                // Proper Table Format
                cout << "\nComparison Table:\n\n";
                cout << left << setw(15) << "Algorithm" << setw(20) << "Page Faults" << endl;
                cout << "-----------------------------\n";
                cout << left << setw(15) << "FCFS" << setw(20) << a << endl;
                cout << left << setw(15) << "LRU" << setw(20) << b << endl;
                cout << left << setw(15) << "Optimal" << setw(20) << c << endl;

                // Best Algorithm
                int min_faults = a;
                if (b < min_faults) min_faults = b;
                if (c < min_faults) min_faults = c;

                cout << "\nBest Algorithm: ";
                if (a == min_faults) cout << "FCFS ";
                if (b == min_faults) cout << "LRU ";
                if (c == min_faults) cout << "Optimal ";
                cout << "with " << min_faults << " page faults.\n";

                break;
            }

            case 5:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
