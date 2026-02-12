#include<iostream>
using namespace std;

struct Process {
    string pid;      
    int at;          
    int bt;       
    int ct;          
    int tat;        
    int wt;          
};

void input(Process p[], int &n) {
    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID: ";
        cin >> p[i].pid;
        cout << "Enter Arrival Time: ";
        cin >> p[i].at;
        cout << "Enter Burst Time: ";
        cin >> p[i].bt;
    }
}

void sort(Process p[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at) {
                swap(p[j], p[j+1]);
            }
        }
    }
}

void display(Process p[], int n, float avgTAT, float avgWT) {
    cout << "\nPID\tArrival\tBurst\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
    cout << endl;
    cout << "Avg TAT: " << avgTAT << "\n";
    cout << "Avg WT: " << avgWT << "\n";
}

void calculate(Process p[], int n) {
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {

        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }

        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    float avgTAT = totalTAT / n;
    float avgWT = totalWT / n;

    display(p, n, avgTAT, avgWT);

    cout << "\nGantt Chart:" << endl;

    cout << "P_ID :      ";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid;
        if (i != n - 1)
            cout << " -> ";
    }

    cout << "\nCT   : 0";
    for (int i = 0; i < n; i++) {
        cout << " -> " << p[i].ct;
    }

}


int main() {
    Process p[100];
    int n;
    input(p, n);
    sort(p, n);
    calculate(p, n);
    return 0;
}
