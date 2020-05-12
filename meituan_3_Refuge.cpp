#include<iostream>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    bool refuge[n+1];
    for (int i = 0; i < n+1;i++){
        refuge[i] = true;
    }
    while (m--){
        int op, pos;
        cin >> op >> pos;            
        if(op==1){
            refuge[pos] = false;
        }
        else if(op==2){
            //while(refuge[pos]==false && pos <= n)
            if(refuge[pos]==false)
                pos++;
            if(refuge[pos]==true)
                cout << pos << endl;                
            else
                cout << -1 << endl;
            
            
        }
    }
    return 0;
}
