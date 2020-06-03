#include<iostream>
using namespace std;
int main(){
    int rounds;
    cin >> rounds;
    while(rounds--){
        long n, k;
        cin >> n >> k;
        cout << (n*k-1)/(n-1) << endl;
    }
    return 0;
}