#include<iostream>
using namespace std;
int main(){
    int totalmemory;
    int processize;
    cout<<"\nenter total memory (in power of 2):";
    cin>>totalmemory;
    cout<<"\nenter processsize:";
    cin>>processize;

    int block=1;
    while(block<processize){
        block=block*2;

    }

    if(block>totalmemory){
        cout<<"\nmemory is not sufficient\n";
     return 0;
    }

    int current =totalmemory;
    while(current>block){
        current /=2;
        cout<<"\n"<<current*2<<" spliting into  "<<current<<" "<<current;

    }

    cout<<"\nprocees (given) allocated with block -->"<<block<<" kb"<<endl;
    cout<<"\nfragmantation:"<<block-processize<<endl;
    cout<<endl;
}