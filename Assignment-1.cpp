#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define MAX 10
#define INF 9999

class Process {
public:
    string name;
    int at, bt, priority;
    int rt, ct, wt, tat;
};

class Scheduler {

    Process p[MAX], temp[MAX];
    int n;

public:

    void input() {
        cout << "\nEnter number of processes: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "\nProcess " << i + 1 << "\n";
            cout << "Name: ";
            cin >> p[i].name;
            cout << "Arrival Time: ";
            cin >> p[i].at;
            cout << "Burst Time: ";
            cin >> p[i].bt;
            cout << "Priority (Lower number = Higher priority): ";
            cin >> p[i].priority;

            p[i].rt = p[i].bt;
        }
    }

    void reset() {
        for (int i = 0; i < n; i++) {
            temp[i] = p[i];
            temp[i].rt = temp[i].bt;
        }
    }

    void calculateTimes(int idx, int time) {
        temp[idx].ct = time;
        temp[idx].tat = temp[idx].ct - temp[idx].at;
        temp[idx].wt = temp[idx].tat - temp[idx].bt;
    }

    float getAvgWT() {
        float sum = 0;
        for (int i = 0; i < n; i++)
            sum += temp[i].wt;
        return sum / n;
    }

    float getAvgTAT() {
        float sum = 0;
        for (int i = 0; i < n; i++)
            sum += temp[i].tat;
        return sum / n;
    }

    void printTable(string title) {
        cout << "\n===== " << title << " Result =====\n";
        cout << left << setw(8) << "P"
             << setw(6) << "AT"
             << setw(6) << "BT"
             << setw(6) << "PR"
             << setw(6) << "CT"
             << setw(6) << "WT"
             << setw(6) << "TAT" << endl;

        for (int i = 0; i < n; i++) {
            cout << left << setw(8) << temp[i].name
                 << setw(6) << temp[i].at
                 << setw(6) << temp[i].bt
                 << setw(6) << temp[i].priority
                 << setw(6) << temp[i].ct
                 << setw(6) << temp[i].wt
                 << setw(6) << temp[i].tat << endl;
        }

        cout << "\nAverage Waiting Time: " << getAvgWT();
        cout << "\nAverage Turnaround Time: " << getAvgTAT() << "\n";
    }

    // FCFS
    float FCFS(bool show = true) {
        reset();
        sort(temp, temp + n, [](Process a, Process b) {
            return a.at < b.at;
        });

        int time = 0;

        for (int i = 0; i < n; i++) {
            if (time < temp[i].at)
                time = temp[i].at;

            time += temp[i].bt;
            calculateTimes(i, time);
        }

        if (show) printTable("FCFS");

        return getAvgWT();
    }

    // SJF NON-PREEMPTIVE
    float SJF_NP(bool show = true) {
        reset();
        int time = 0, done = 0;

        while (done < n) {
            int idx = -1, minBT = INF;

            for (int i = 0; i < n; i++) {
                if (temp[i].at <= time && temp[i].rt > 0) {
                    if (temp[i].bt < minBT) {
                        minBT = temp[i].bt;
                        idx = i;
                    }
                }
            }

            if (idx == -1) { time++; continue; }

            time += temp[idx].bt;
            temp[idx].rt = 0;
            calculateTimes(idx, time);
            done++;
        }

        if (show) printTable("SJF Non-Preemptive");

        return getAvgWT();
    }

    // SJF PREEMPTIVE
    float SJF_P(bool show = true) {
        reset();
        int time = 0, done = 0;

        while (done < n) {
            int idx = -1, minRT = INF;

            for (int i = 0; i < n; i++) {
                if (temp[i].at <= time && temp[i].rt > 0) {
                    if (temp[i].rt < minRT) {
                        minRT = temp[i].rt;
                        idx = i;
                    }
                }
            }

            if (idx == -1) { time++; continue; }

            temp[idx].rt--;
            time++;

            if (temp[idx].rt == 0) {
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show) printTable("SJF Preemptive");

        return getAvgWT();
    }

    // Priority NON-PREEMPTIVE
    float Priority_NP(bool show = true) {
        reset();
        int time = 0, done = 0;

        while (done < n) {
            int idx = -1, minP = INF;

            for (int i = 0; i < n; i++) {
                if (temp[i].at <= time && temp[i].rt > 0) {
                    if (temp[i].priority < minP) {
                        minP = temp[i].priority;
                        idx = i;
                    }
                }
            }

            if (idx == -1) { time++; continue; }

            time += temp[idx].bt;
            temp[idx].rt = 0;
            calculateTimes(idx, time);
            done++;
        }

        if (show) printTable("Priority Non-Preemptive");

        return getAvgWT();
    }

    // Priority PREEMPTIVE
    float Priority_P(bool show = true) {
        reset();
        int time = 0, done = 0;

        while (done < n) {
            int idx = -1, minP = INF;

            for (int i = 0; i < n; i++) {
                if (temp[i].at <= time && temp[i].rt > 0) {
                    if (temp[i].priority < minP) {
                        minP = temp[i].priority;
                        idx = i;
                    }
                }
            }

            if (idx == -1) { time++; continue; }

            temp[idx].rt--;
            time++;

            if (temp[idx].rt == 0) {
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show) printTable("Priority Preemptive");

        return getAvgWT();
    }

    // Round Robin
    float RoundRobin(bool show = true) {
        reset();
        int tq = 2;

        int time = 0, done = 0;
        int q[100], front = 0, rear = 0;

        for (int i = 0; i < n; i++)
            if (temp[i].at == 0)
                q[rear++] = i;

        while (done < n) {

            if (front == rear) { time++; continue; }

            int idx = q[front++];
            int exec = min(tq, temp[idx].rt);

            temp[idx].rt -= exec;
            time += exec;

            for (int i = 0; i < n; i++)
                if (temp[i].at > time - exec && temp[i].at <= time)
                    q[rear++] = i;

            if (temp[idx].rt > 0)
                q[rear++] = idx;
            else {
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show) printTable("Round Robin (TQ=2)");

        return getAvgWT();
    }

    // Comparision
    void CompareAll() {

        float wt[6], tat[6];

        wt[0] = FCFS(false); tat[0] = getAvgTAT();
        wt[1] = SJF_NP(false); tat[1] = getAvgTAT();
        wt[2] = SJF_P(false); tat[2] = getAvgTAT();
        wt[3] = Priority_NP(false); tat[3] = getAvgTAT();
        wt[4] = Priority_P(false); tat[4] = getAvgTAT();
        wt[5] = RoundRobin(false); tat[5] = getAvgTAT();

        string names[6] = {
            "FCFS","SJF NP","SJF P",
            "Priority NP","Priority P","RR (TQ=2)"
        };

        cout << "\nComparative Analysis\n";
        cout << left << setw(15) << "Algorithm"
             << setw(20) << "Avg Waiting Time"
             << setw(20) << "Avg Turnaround Time\n";

        for (int i = 0; i < 6; i++) {
            cout << left << setw(15) << names[i]
                 << setw(20) << wt[i]
                 << setw(20) << tat[i] << endl;
        }
    }
};

int main() {
    Scheduler s;
    s.input();

    int ch;
    do {
        cout << "\n1.FCFS\n2.SJF NP\n3.SJF P\n4.Priority NP\n5.Priority P\n6.Round Robin\n7.Compare All\n0.Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: s.FCFS(); break;
            case 2: s.SJF_NP(); break;
            case 3: s.SJF_P(); break;
            case 4: s.Priority_NP(); break;
            case 5: s.Priority_P(); break;
            case 6: s.RoundRobin(); break;
            case 7: s.CompareAll(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }

    } while (ch != 0);

    return 0;
}
