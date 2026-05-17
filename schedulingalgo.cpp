#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

struct Process{
    int id,at,bt,pr;
    int wt=0,tat=0,ct=0,rt;
};

void printTable(Process p[],int n){
    float avgwt=0,avgtat=0;

    cout<<"\nPID\tAT\tBT\tWT\tTAT\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<"\n";
        avgwt+=p[i].wt;
        avgtat+=p[i].tat;
    }

    cout<<"\nAverage WT = "<<avgwt/n;
    cout<<"\nAverage TAT = "<<avgtat/n<<"\n";
}

void FCFS(Process p[],int n){

    int time=0;

    cout<<"\nGantt Chart\n|";

    for(int i=0;i<n;i++){

        if(time<p[i].at)
            time=p[i].at;

       

        cout<<" P"<<p[i].id<<" |";

        time+=p[i].bt;

        p[i].ct=time;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
    }

    cout<<"\n";

    printTable(p,n);
}

void SJF(Process p[],int n){

    int complete=0,time=0,vis[20]={0};

    cout<<"\nGantt Chart\n|";

    while(complete<n){

        int idx=-1;
        int mn=INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && !vis[i] && p[i].bt<mn){
                mn=p[i].bt;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        cout<<" P"<<p[idx].id<<" |";

        p[idx].wt=time-p[idx].at;

        time+=p[idx].bt;

        p[idx].ct=time;
        p[idx].tat=p[idx].ct-p[idx].at;

        vis[idx]=1;
        complete++;
    }

    cout<<"\n";

    printTable(p,n);
}

void SRTF(Process p[],int n){

    int complete=0,time=0;
    int rt[20];

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    cout<<"\nGantt Chart\n|";

    while(complete<n){

        int idx=-1;
        int mn=INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0 && rt[i]<mn){
                mn=rt[i];
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        cout<<" P"<<p[idx].id<<" |";

        rt[idx]--;
        time++;

        if(rt[idx]==0){
            complete++;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
        }
    }

    cout<<"\n";

    printTable(p,n);
}

void PriorityNP(Process p[],int n){

    int complete=0,time=0,vis[20]={0};

    cout<<"\nGantt Chart\n|";

    while(complete<n){

        int idx=-1;
        int best=INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && !vis[i] && p[i].pr<best){
                best=p[i].pr;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        cout<<" P"<<p[idx].id<<" |";

        p[idx].wt=time-p[idx].at;

        time+=p[idx].bt;

        p[idx].ct=time;
        p[idx].tat=p[idx].ct-p[idx].at;

        vis[idx]=1;
        complete++;
    }

    cout<<"\n";

    printTable(p,n);
}

void PriorityP(Process p[],int n){

    int complete=0,time=0;
    int rt[20];

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    cout<<"\nGantt Chart\n|";

    while(complete<n){

        int idx=-1;
        int best=INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0 && p[i].pr<best){
                best=p[i].pr;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        cout<<" P"<<p[idx].id<<" |";

        rt[idx]--;
        time++;

        if(rt[idx]==0){
            complete++;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
        }
    }

    cout<<"\n";

    printTable(p,n);
}

void RoundRobin(Process p[],int n,int q){

    int time=0,done;
    int rt[20];

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    cout<<"\nGantt Chart\n|";

    while(true){

        done=1;

        for(int i=0;i<n;i++){

            if(rt[i]>0){

                done=0;

                cout<<" P"<<p[i].id<<" |";

                if(rt[i]>q){
                    time+=q;
                    rt[i]-=q;
                }
                else{
                    time+=rt[i];
                    p[i].ct=time;
                    rt[i]=0;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                }
            }
        }

        if(done) break;
    }

    cout<<"\n";

    printTable(p,n);
}

int main(){

    int n,ch,q;

    cout<<"Enter number of processes: ";
    cin>>n;

    Process p[20],temp[20];

    for(int i=0;i<n;i++){

        p[i].id=i+1;

        cout<<"\nProcess P"<<i+1<<"\n";

        cout<<"Arrival Time: ";
        cin>>p[i].at;

        cout<<"Burst Time: ";
        cin>>p[i].bt;

        cout<<"Priority: ";
        cin>>p[i].pr;
    }

    while(true){

        for(int i=0;i<n;i++)
            temp[i]=p[i];

        cout<<"\n===== CPU Scheduling Menu =====\n";
        cout<<"1. FCFS\n";
        cout<<"2. SJF\n";
        cout<<"3. SRTF\n";
        cout<<"4. Priority Non Preemptive\n";
        cout<<"5. Priority Preemptive\n";
        cout<<"6. Round Robin\n";
        cout<<"7. Exit\n";

        cout<<"Enter choice: ";
        cin>>ch;

        switch(ch){

        case 1:
            cout<<"\n===== FCFS =====\n";
            FCFS(temp,n);
            break;

        case 2:
            cout<<"\n===== SJF =====\n";
            SJF(temp,n);
            break;

        case 3:
            cout<<"\n===== SRTF =====\n";
            SRTF(temp,n);
            break;

        case 4:
            cout<<"\n===== Priority Non Preemptive =====\n";
            PriorityNP(temp,n);
            break;

        case 5:
            cout<<"\n===== Priority Preemptive =====\n";
            PriorityP(temp,n);
            break;

        case 6:
            cout<<"Enter Time Quantum: ";
            cin>>q;
            cout<<"\n===== Round Robin =====\n";
            RoundRobin(temp,n,q);
            break;

        case 7:
            return 0;

        default:
            cout<<"Invalid choice\n";
        }
    }
}