#include<iostream>
using namespace std;


class FCFS{
public:
    string pid[100]; 
    int at[100];  
    int n; 

    void input(){
    cout << "Enter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "Enter Process ID for process " << i+1 << ": ";
        cin >> pid[i];
        cout << "Enter Arrival Time for process " << pid[i] << ": ";
        cin >> at[i];
        }
    }

    void sort(){
        for (int i = 0; i < n-1; i++){
            for (int j = 0; j < n-i-1; j++){
                if (at[j] > at[j+1] || (at[j] == at[j+1] && pid[j] > pid[j+1])){

                    int tempAt = at[j];
                    at[j] = at[j+1];
                    at[j+1] = tempAt;
                    
                    string tempPid = pid[j];
                    pid[j] = pid[j+1];
                    pid[j+1] = tempPid;
                }
            }
        }
    }

    void display(){
        cout << "\nPID\tAT\n";
        for (int i = 0; i < n; i++){
            cout << pid[i] << "\t" << at[i] << "\n";
        }
    }
};

int main() {
    FCFS p;
    p.input();
    p.sort();
    p.display();
    return 0;
}
