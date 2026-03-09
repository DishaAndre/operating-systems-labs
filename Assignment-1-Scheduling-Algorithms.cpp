#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 10
#define INF 9999

class Process{
public:
    string name;
    int at, bt, priority;
    int rt, ct, wt, tat;
};

class Scheduler{
    Process p[MAX], temp[MAX];
    int n;
    struct Gantt{
        string pname;
        int start;
        int end;
    };

    Gantt gantt[200];
    int gcount;

public:

    void input(){
        cout << "Enter number of processes: ";
        cin >> n;
        for (int i = 0; i < n; i++){
            cout << "\nProcess " << i + 1 << endl;
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

    void reset(){
        gcount = 0;

        for (int i = 0; i < n; i++){
            temp[i] = p[i];
            temp[i].rt = temp[i].bt;
        }
    }

    void calculateTimes(int idx, int time){
        temp[idx].ct = time;
        temp[idx].tat = temp[idx].ct - temp[idx].at;
        temp[idx].wt = temp[idx].tat - temp[idx].bt;
    }

    void printReadyQueue(int time, bool show=true){
        if (!show) return;
        cout << "\nReady Queue at time " << time << ": ";
        for (int i = 0; i < n; i++) {
            if (temp[i].at <= time && temp[i].rt > 0)
                cout << temp[i].name << " ";
        }
        cout << endl;
    }

    void printGantt(){
        cout << "\nGantt Chart\n";

        cout << "|";
        for(int i = 0; i < gcount; i++){
            cout << setw(6) << gantt[i].pname << " |";
        }
        cout << endl;
        cout << setw(1) << gantt[0].start;
        for(int i = 0; i < gcount; i++){
            cout << setw(8) << gantt[i].end;
        }
        cout << endl;
    }
    float getAvgWT(){
        float sum = 0;
        for (int i = 0; i < n; i++)
            sum += temp[i].wt;
        return sum / n;
    }

    float getAvgTAT(){
        float sum = 0;
        for (int i = 0; i < n; i++)
            sum += temp[i].tat;
        return sum / n;
    }

    void printTable(string title){
        cout << "\n" << title << " Scheduling Algorithm: \n";
        cout << left << setw(8) << "PID"
             << setw(6) << "AT"
             << setw(6) << "BT"
             << setw(6) << "PR"
             << setw(6) << "CT"
             << setw(6) << "WT"
             << setw(6) << "TAT" << endl;
        for (int i = 0; i < n; i++){
            cout << left << setw(8) << temp[i].name
                 << setw(6) << temp[i].at
                 << setw(6) << temp[i].bt
                 << setw(6) << temp[i].priority
                 << setw(6) << temp[i].ct
                 << setw(6) << temp[i].wt
                 << setw(6) << temp[i].tat << endl;
        }
        cout << "\nAverage Waiting Time: " << getAvgWT();
        cout << "\nAverage Turnaround Time: " << getAvgTAT() << endl;
    }

    float FCFS(bool show=true){
        reset();
        sort(temp, temp+n, [](Process a, Process b){
            return a.at < b.at;
        });

        int time = 0;
        for (int i = 0; i < n; i++){
            if (time < temp[i].at)
                time = temp[i].at;
            printReadyQueue(time, show);

            gantt[gcount].pname = temp[i].name;
            gantt[gcount].start = time;
            time += temp[i].bt;
            gantt[gcount].end = time;
            gcount++;
            calculateTimes(i, time);
        }

        if (show) {
            printGantt();
            printTable("FCFS");
        }
        return getAvgWT();
    }

    float SJF_NP(bool show=true){
        reset();
        int time = 0, done = 0;
        while (done < n) {
            int idx = -1, minBT = INF;
            for (int i = 0; i < n; i++) {
                if (temp[i].at <= time && temp[i].rt > 0){
                    if (temp[i].bt < minBT) {
                        minBT = temp[i].bt;
                        idx = i;
                    }
                }
            }
            if (idx == -1){
                time++;
                continue;
            }

            printReadyQueue(time, show);

            gantt[gcount].pname = temp[idx].name;
            gantt[gcount].start = time;
            time += temp[idx].bt;
            gantt[gcount].end = time;
            gcount++;
            temp[idx].rt = 0;

            calculateTimes(idx, time);
            done++;
        }

        if (show) {
            printGantt();
            printTable("SJF Non Preemptive");
        }
        return getAvgWT();
    }

    float SJF_P(bool show=true){
        reset();
        int time = 0, done = 0;
        while (done < n) {
            int idx = -1, minRT = INF;
            for (int i = 0; i < n; i++){
                if (temp[i].at <= time && temp[i].rt > 0){
                    if (temp[i].rt < minRT) {
                        minRT = temp[i].rt;
                        idx = i;
                    }
                }
            }
            if (idx == -1){
                time++;
                continue;
            }
            printReadyQueue(time, show);

            gantt[gcount].pname = temp[idx].name;
            gantt[gcount].start = time;

            temp[idx].rt--;
            time++;

            gantt[gcount].end = time;
            gcount++;

            if (temp[idx].rt == 0){
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show){
            printGantt();
            printTable("SJF Preemptive");
        }

        return getAvgWT();
    }

    float Priority_NP(bool show=true){
        reset();
        int time = 0, done = 0;
        while (done < n){
            int idx = -1, minP = INF;
            for (int i = 0; i < n; i++){
                if (temp[i].at <= time && temp[i].rt > 0){
                    if (temp[i].priority < minP){
                        minP = temp[i].priority;
                        idx = i;
                    }
                }
            }

            if (idx == -1){
                time++;
                continue;
            }
            printReadyQueue(time, show);

            gantt[gcount].pname = temp[idx].name;
            gantt[gcount].start = time;
            time += temp[idx].bt;
            gantt[gcount].end = time;
            gcount++;
            temp[idx].rt = 0;

            calculateTimes(idx, time);

            done++;
        }

        if (show){
            printGantt();
            printTable("Priority Non Preemptive");
        }
        return getAvgWT();
    }

    float Priority_P(bool show=true){
        reset();
        int time = 0, done = 0;
        while (done < n){
            int idx = -1, minP = INF;
            for (int i = 0; i < n; i++){
                if (temp[i].at <= time && temp[i].rt > 0){
                    if (temp[i].priority < minP){
                        minP = temp[i].priority;
                        idx = i;
                    }
                }
            }

            if (idx == -1){
                time++;
                continue;
            }

            printReadyQueue(time, show);

            gantt[gcount].pname = temp[idx].name;
            gantt[gcount].start = time;

            temp[idx].rt--;
            time++;

            gantt[gcount].end = time;
            gcount++;

            if (temp[idx].rt == 0){
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show){
            printGantt();
            printTable("Priority Preemptive");
        }
        return getAvgWT();
    }

    float RoundRobin(bool show=true){
        reset();
        int tq = 2;
        int time = 0, done = 0;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (temp[i].at == 0)
                q.push(i);
        while (done < n) {
            if (q.empty()){
                time++;
                continue;
            }

            int idx = q.front();
            q.pop();
            printReadyQueue(time, show);

            int exec = min(tq, temp[idx].rt);

            gantt[gcount].pname = temp[idx].name;
            gantt[gcount].start = time;

            temp[idx].rt -= exec;
            time += exec;

            gantt[gcount].end = time;
            gcount++;

            for (int i = 0; i < n; i++)
                if (temp[i].at > time-exec && temp[i].at <= time)
                    q.push(i);

            if (temp[idx].rt > 0)
                q.push(idx);
            else {
                calculateTimes(idx, time);
                done++;
            }
        }

        if (show){
            printGantt();
            printTable("Round Robin (TQ=2)");
        }
        return getAvgWT();
    }

    void CompareAll(){
        float wt[6], tat[6];

        wt[0] = FCFS(false); tat[0] = getAvgTAT();
        wt[1] = SJF_NP(false); tat[1] = getAvgTAT();
        wt[2] = SJF_P(false); tat[2] = getAvgTAT();
        wt[3] = Priority_NP(false); tat[3] = getAvgTAT();
        wt[4] = Priority_P(false); tat[4] = getAvgTAT();
        wt[5] = RoundRobin(false); tat[5] = getAvgTAT();

        string names[6] = {"FCFS","SJF NP","SJF P","Priority NP","Priority P","RR"};

        cout << "\nComparative Analysis\n";
        cout << left << setw(15) << "Algorithm"
             << setw(20) << "Avg Waiting Time"
             << setw(20) << "Avg Turnaround Time\n";

        for (int i = 0; i < 6; i++){

            cout << left << setw(15) << names[i]
                 << setw(20) << wt[i]
                 << setw(20) << tat[i] << endl;
        }

        float minWT = wt[0];
        int best = 0;
        for (int i = 1; i < 6; i++){
            if (wt[i] < minWT){
                minWT = wt[i];
                best = i;
            }
        }
        cout << "\nMost Optimal Algorithm (Lowest Avg Waiting Time): "
             << names[best] << endl;
    }
};

int main(){
    Scheduler s;
    s.input();
    int ch;
    do{
        cout << "\n1.FCFS\n2.SJF NonPreemptive\n3.SJF Preemprive\n4.Priority NonPreemptive\n5.Priority Preemptive\n6.Round Robin\n7.Compare All\n0.Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch){
        case 1: s.FCFS(); break;
        case 2: s.SJF_NP(); break;
        case 3: s.SJF_P(); break;
        case 4: s.Priority_NP(); break;
        case 5: s.Priority_P(); break;
        case 6: s.RoundRobin(); break;
        case 7: s.CompareAll(); break;
        }

    }while (ch != 0);

    return 0;
}
