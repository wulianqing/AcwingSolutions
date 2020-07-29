/*  Alibaba 2020-7-29 */
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> egg(n);
    for (int i = 0; i < n;i++)
        cin >> egg[i];
    sort(egg.begin(), egg.begin() + n, greater<int>());
    int min = INT_MAX;
    for (int i = 0; i < n - 1;i++){
        if(egg[i] - egg[i+1] < min)
            min = egg[i] - egg[i + 1];
    }
    cout << min << endl;
    return 0;
}
