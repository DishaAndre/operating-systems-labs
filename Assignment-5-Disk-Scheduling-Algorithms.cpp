#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

// Function Declarations
int FCFS(int req[], int n, int head);
int SSTF(int req[], int n, int head);
int SCAN_Left(int req[], int n, int head, int disk_size);
int SCAN_Right(int req[], int n, int head, int disk_size);
int CSCAN_Left(int req[], int n, int head, int disk_size);
int CSCAN_Right(int req[], int n, int head, int disk_size);

// ---------------- FCFS ----------------
int FCFS(int req[], int n, int head) {
    int total = 0;
    cout << "Head Movement: " << head;

    for (int i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        cout << " -> " << head;
    }
    cout << endl;
    return total;
}

// ---------------- SSTF ----------------
int SSTF(int req[], int n, int head) {
    bool visited[50] = {false};
    int total = 0;

    cout << "Head Movement: " << head;

    for (int count = 0; count < n; count++) {
        int minDist = INT_MAX, index = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(head - req[i]);
                if (dist < minDist) {
                    minDist = dist;
                    index = i;
                }
            }
        }

        visited[index] = true;
        total += minDist;
        head = req[index];
        cout << " -> " << head;
    }
    cout << endl;
    return total;
}

// ---------------- SCAN LEFT ----------------
int SCAN_Left(int req[], int n, int head, int disk_size) {
    int total = 0, left[50], right[50], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, left + l);
    sort(right, right + r);

    cout << "Head Movement: " << head;

    for (int i = l - 1; i >= 0; i--) {
        total += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }

    total += abs(head - 0);
    head = 0;
    cout << " -> " << head;

    for (int i = 0; i < r; i++) {
        total += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }

    cout << endl;
    return total;
}

// ---------------- SCAN RIGHT ----------------
int SCAN_Right(int req[], int n, int head, int disk_size) {
    int total = 0, left[50], right[50], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, left + l);
    sort(right, right + r);

    cout << "Head Movement: " << head;

    for (int i = 0; i < r; i++) {
        total += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }

    total += abs(head - (disk_size - 1));
    head = disk_size - 1;
    cout << " -> " << head;

    for (int i = l - 1; i >= 0; i--) {
        total += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }

    cout << endl;
    return total;
}

// ---------------- C-SCAN LEFT ----------------
int CSCAN_Left(int req[], int n, int head, int disk_size) {
    int total = 0, left[50], right[50], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, left + l);
    sort(right, right + r);

    cout << "Head Movement: " << head;

    for (int i = l - 1; i >= 0; i--) {
        total += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }

    total += abs(head - 0);
    head = 0;
    cout << " -> " << head;

    total += abs(head - (disk_size - 1));
    head = disk_size - 1;
    cout << " -> " << head;

    for (int i = r - 1; i >= 0; i--) {
        total += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }

    cout << endl;
    return total;
}

// ---------------- C-SCAN RIGHT ----------------
int CSCAN_Right(int req[], int n, int head, int disk_size) {
    int total = 0, left[50], right[50], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, left + l);
    sort(right, right + r);

    cout << "Head Movement: " << head;

    for (int i = 0; i < r; i++) {
        total += abs(head - right[i]);
        head = right[i];
        cout << " -> " << head;
    }

    total += abs(head - (disk_size - 1));
    head = disk_size - 1;
    cout << " -> " << head;

    total += abs(head - 0);
    head = 0;
    cout << " -> " << head;

    for (int i = 0; i < l; i++) {
        total += abs(head - left[i]);
        head = left[i];
        cout << " -> " << head;
    }

    cout << endl;
    return total;
}

// ---------------- MAIN ----------------
int main() {
    int n, head, disk_size;

    cout << "Enter number of requests: ";
    cin >> n;

    int req[50];
    cout << "Enter request queue: ";
    for (int i = 0; i < n; i++)
        cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size: ";
    cin >> disk_size;

    int choice;

    while (true) {
        cout << "\n1.FCFS \n2.SSTF \n3.SCAN-Left \n4.SCAN-Right\n";
        cout << "5.CSCAN-Left \n6.CSCAN-Right \n7.Compare All \n8.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "\n--- FCFS ---\n";
            int total = FCFS(req, n, head);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 2: {
            cout << "\n--- SSTF ---\n";
            int total = SSTF(req, n, head);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 3: {
            cout << "\n--- SCAN LEFT ---\n";
            int total = SCAN_Left(req, n, head, disk_size);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 4: {
            cout << "\n--- SCAN RIGHT ---\n";
            int total = SCAN_Right(req, n, head, disk_size);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 5: {
            cout << "\n--- C-SCAN LEFT ---\n";
            int total = CSCAN_Left(req, n, head, disk_size);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 6: {
            cout << "\n--- C-SCAN RIGHT ---\n";
            int total = CSCAN_Right(req, n, head, disk_size);
            cout << "Total Head Movement = " << total << endl;
            break;
        }

        case 7: {
    		cout << "\n--- Comparison ---\n";

			cout << "\nFCFS:\n";
			int a = FCFS(req, n, head);

			cout << "\nSSTF:\n";
			int b = SSTF(req, n, head);

			cout << "\nSCAN-Left:\n";
			int c = SCAN_Left(req, n, head, disk_size);

			cout << "\nSCAN-Right:\n";
			int d = SCAN_Right(req, n, head, disk_size);

			cout << "\nC-SCAN-Left:\n";
			int e = CSCAN_Left(req, n, head, disk_size);

			cout << "\nC-SCAN-Right:\n";
			int f = CSCAN_Right(req, n, head, disk_size);

			cout << "\n\nComparison Table:\n";
			cout << left << setw(20) << "Algorithm" << "Movement\n";
			cout << "--------------------------------\n";
			cout << setw(20) << "FCFS" << a << endl;
			cout << setw(20) << "SSTF" << b << endl;
			cout << setw(20) << "SCAN-Left" << c << endl;
			cout << setw(20) << "SCAN-Right" << d << endl;
			cout << setw(20) << "CSCAN-Left" << e << endl;
			cout << setw(20) << "CSCAN-Right" << f << endl;

			break;
		}

        case 8:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}
