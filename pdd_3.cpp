#include<iostream>
#include<set>
#include<cmath>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    int max = 0;
    int min = 1000000000;
    multiset<int> coin;
    for (int i = 0; i < n;i++){
        int input;
        cin >> input;
        coin.insert(input);
        if (input > max)
            max = input;
        if(input < min)
            min = input;
    }
    while(m--){
        if(max == min)
            continue;
        coin.erase(coin.find(max));
        coin.insert(max - 1);
        if(coin.count(max) == 0)
            max--;
        coin.erase(coin.find(min));
        coin.insert(min + 1);
        if(coin.count(min) == 0)
            min++;
    }
    cout << max - min << endl;
    return 0;
}