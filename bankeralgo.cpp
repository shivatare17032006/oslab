// #include <iostream>
// #include <vector>

// using namespace std;

// void calculateNeed(int n, int m,
//                    vector<vector<int>>& alloc,
//                    vector<vector<int>>& maxm,
//                    vector<vector<int>>& need) {

//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             need[i][j] = maxm[i][j] - alloc[i][j];
// }

// void displayMatrices(int n, int m,
//                      vector<vector<int>>& alloc,
//                      vector<vector<int>>& maxm,
//                      vector<vector<int>>& need,
//                      vector<int>& avail) {

//     cout << "\n--- Current System State ---\n";

//     cout << "\nAllocation Matrix:\n";
//     for (int i = 0; i < n; i++) {
//         cout << "P" << i << ": ";
//         for (int j = 0; j < m; j++)
//             cout << alloc[i][j] << " ";
//         cout << endl;
//     }

//     cout << "\nMax Matrix:\n";
//     for (int i = 0; i < n; i++) {
//         cout << "P" << i << ": ";
//         for (int j = 0; j < m; j++)
//             cout << maxm[i][j] << " ";
//         cout << endl;
//     }

//     cout << "\nNeed Matrix:\n";

//     for (int i = 0; i < n; i++) {
//         cout << "P" << i << ": ";
//         for (int j = 0; j < m; j++)
//             cout << need[i][j] << " ";
//         cout << endl;
//     }

//     cout << "\nAvailable Resources:\n";
//     for (int i = 0; i < m; i++)
//         cout << avail[i] << " ";

//     cout << endl;
// }

// bool checkSafety(int n, int m,
//                  vector<vector<int>>& alloc,
//                  vector<vector<int>>& need,
//                  vector<int>& avail,
//                  vector<int>& safeSeq) {

//     vector<int> work = avail;
//     vector<int> finish(n, 0);

//     int count = 0;

//     while (count < n) {

//         bool found = false;

//         for (int i = 0; i < n; i++) {

//             if (!finish[i]) {

//                 bool canAllocate = true;

//                 for (int j = 0; j < m; j++) {

//                     if (need[i][j] > work[j]) {
//                         canAllocate = false;
//                         break;
//                     }
//                 }

//                 if (canAllocate) {

//                     for (int j = 0; j < m; j++)
//                         work[j] += alloc[i][j];

//                     safeSeq.push_back(i);

//                     finish[i] = 1;
//                     found = true;
//                     count++;
//                 }
//             }
//         }

//         if (!found) {
//             cout << "\nSystem is NOT in safe state!\n";
//             return false;
//         }
//     }

//     cout << "\nSystem is in SAFE state!\n";

//     cout << "Safe Sequence: ";

//     for (int i = 0; i < n; i++)
//         cout << "P" << safeSeq[i] << " ";

//     cout << endl;

//     return true;
// }

// bool requestResources(int n, int m,
//                       vector<vector<int>>& alloc,
//                       vector<vector<int>>& need,
//                       vector<int>& avail,
//                       int process,
//                       vector<int>& request) {

//     for (int i = 0; i < m; i++) {

//         if (request[i] > need[process][i]) {
//             cout << "Error: Request exceeds maximum claim!\n";
//             return false;
//         }

//         if (request[i] > avail[i]) {
//             cout << "Resources not available. Process must wait!\n";
//             return false;
//         }
//     }

//     vector<int> tempAvail = avail;
//     vector<vector<int>> tempAlloc = alloc;
//     vector<vector<int>> tempNeed = need;

//     for (int i = 0; i < m; i++) {

//         tempAvail[i] -= request[i];
//         tempAlloc[process][i] += request[i];
//         tempNeed[process][i] -= request[i];
//     }

//     vector<int> safeSeq;

//     if (checkSafety(n, m, tempAlloc, tempNeed, tempAvail, safeSeq)) {

//         avail = tempAvail;
//         alloc = tempAlloc;
//         need = tempNeed;

//         cout << "Request Granted!\n";
//         return true;
//     }

//     else {

//         cout << "Request Denied (Unsafe State)\n";
//         return false;
//     }
// }

// int main() {

//     int n, m, choice;

//     cout << "Enter number of processes: ";
//     cin >> n;

//     cout << "Enter number of resources: ";
//     cin >> m;

//     vector<vector<int>> alloc(n, vector<int>(m));
//     vector<vector<int>> maxm(n, vector<int>(m));
//     vector<vector<int>> need(n, vector<int>(m));

//     vector<int> avail(m);

//     cout << "Enter Allocation Matrix:\n";

//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             cin >> alloc[i][j];

//     cout << "Enter Max Matrix:\n";

//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             cin >> maxm[i][j];

//     cout << "Enter Available Resources:\n";

//     for (int i = 0; i < m; i++)
//         cin >> avail[i];

//     calculateNeed(n, m, alloc, maxm, need);

//     do {

//         cout << "\n===== BANKER'S ALGORITHM MENU =====\n";

//         cout << "1. Display System State\n";
//         cout << "2. Check Safety\n";
//         cout << "3. Request Resources\n";
//         cout << "4. Exit\n";

//         cout << "Enter choice: ";
//         cin >> choice;

//         switch (choice) {

//             case 1:
//                 displayMatrices(n, m, alloc, maxm, need, avail);
//                 break;

//             case 2: {

//                 vector<int> safeSeq;

//                 checkSafety(n, m, alloc, need, avail, safeSeq);

//                 break;
//             }

//             case 3: {

//                 int process;

//                 cout << "Enter process number: ";
//                 cin >> process;

//                 vector<int> request(m);

//                 cout << "Enter request:\n";

//                 for (int i = 0; i < m; i++)
//                     cin >> request[i];

//                 requestResources(n, m, alloc, need,
//                                  avail, process, request);

//                 break;
//             }

//             case 4:
//                 cout << "Exiting...\n";
//                 break;

//             default:
//                 cout << "Invalid choice!\n";
//         }

//     } while (choice != 4);

//     return 0;
// }



#include<iostream>
#include<vector>
using namespace std;

void needmatrix(vector<vector<int>> &alloc,vector<vector<int>> &max,vector<vector<int>> &need,int n,int m){

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

}

void dispaly(vector<vector<int>> &alloc,vector<vector<int>> &max,vector<vector<int>> &need,vector<int> avilable,int n,int m){

    // allocation
    cout<<"allocation matrix:\n";
    cout<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<alloc[i][j]<<" ";

        }
        cout<<endl;
    }
     cout<<"\nmax matrix:\n";
     cout<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<max[i][j]<<" ";

        }
        cout<<endl;
    }


    cout<<"\nneed matrix:\n";
     cout<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<need[i][j]<<" ";

        }
        cout<<endl;
    }


    cout<<"\navilable resorcese\n";
     cout<<endl;
        for(int j=0;j<m;j++){
            cout<<avilable[j]<<" ";

        }
        cout<<endl;
    


}


bool checksafty(vector<vector<int>> &alloc,vector<vector<int>> &max,vector<vector<int>> &need,vector<int> avilable,int n,int m){
vector<int> work=avilable;
vector<int> iscomplete(n,0);
vector<int> safe(m,0);
int c=0;
while(c<n){
      bool found=false;
    for(int i=0;i<n;i++){

        bool canallo=true;
    if(iscomplete[i]!=1){
       for(int j=0;j<m;j++){
        if(work[j]<need[i][j] ){
             canallo=false;
             break;
        }

        
       }

       if(canallo){
        for(int j=0;j<m;j++){
            work[j]=work[j]+alloc[i][j];
        }
        iscomplete[i]=1;
           found=true;
           c++;
           safe.push_back(i);


       }

      


    }

}


if(!found){
    cout<<"\nnot safe\n";
    return false;

}
}


cout<<"\n safe \nsafe sequence is:";
for(int i=0;i<m;i++){
    cout<<" p"<<safe[i];
}

return true;
}


bool resourcereq(vector<vector<int>> &alloc,vector<vector<int>> &max,vector<vector<int>> &need,vector<int> avilable,int n,int m,vector<int> &res,int p){
   for(int i=0;i<m;i++){
    if(avilable[i]<res[i]){
        cout<<"\n wait resorces not avilable\n";
        return false;
    }
    if(need[p][i]<res[i]){
        cout<<"\n error exiceed max claims";
        return false;
    }

   }

   vector<int> tempAvail = avilable;
    vector<vector<int>> tempAlloc = alloc;
    vector<vector<int>> tempNeed = need;

    for (int i = 0; i < m; i++) {

        tempAvail[i] -= res[i];
        tempAlloc[p][i] += res[i];
        tempNeed[p][i] -= res[i];
    }

   

    if (checksafty(tempAlloc,max,tempNeed ,tempAvail,n,m)) {

        avilable = tempAvail;
        alloc = tempAlloc;
        need = tempNeed;

        cout << "Request Granted!\n";
        return true;
    }

    else {

        cout << "Request Denied (Unsafe State)\n";
        return false;
    }


}


int main(){
int n,m;
cout<<"\n enter number of processes:";
cin>>n;
cout<<"\nenetr number of resorcese:";
cin>>m;

vector<vector<int>> alloc(n,vector<int>(m));
vector<vector<int>> max(n,vector<int>(m));
vector<vector<int>> need(n,vector<int>(m));
vector<int> avilable(m);

cout<<"\n give allocation matrix:\n";

for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        cin>>alloc[i][j];

    }
}

cout<<"\n give max matrix\n";
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        cin>>max[i][j];
    }
}

cout<<"\n give avilable resorcese\n";

for(int i=0;i<m;i++){
    cin>>avilable[i];
}



needmatrix(alloc,max,need,n,m);
int c;

do{
    cout<<"\nmenu\n";
    cout<<"1)dispaly ";
    cout<<"\n2)cheack system is safe or not (bankers algorithm)\n";
    cout<<"3)resources request\n";
    cout<<"4)exit program";

    cout<<"\nenter choice:";
    cin>>c;

    switch(c){

      case 1:
          dispaly(alloc,need,max,avilable,n,m);
          break;


    case 2:
        checksafty(alloc,max,need,avilable,n,m);
        break;

    case 3:{
    cout<<"\n enter process which you want to give resoreces:";
    int p;
    cin>>p;
    vector<int> res(m,0);
       cout<<"\nenter resorces:";
       for(int i=0;i<m;i++){
        cin>>res[i];
       }
          resourcereq(alloc,max,need ,avilable,n,m,res,p);
          break;
    }
    case 4:
      cout<<"\nexiting...";
      return 0;
       







    }







}while(c!=4);








}