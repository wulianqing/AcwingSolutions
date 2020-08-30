#include<iostream>
#include<vector>
using namespace std;

int main(){
    int sum, days;
    cin >> sum >> days;
    vector<int> add_water(days);
    for (int i = 0; i < days;i++)
        cin >> add_water[i];
    for (int i = 0; i < days;i++){
        sum += add_water[i];
        sum /= 2;
    }
    cout << sum << endl;
    return 0;
}