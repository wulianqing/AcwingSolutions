#include<iostream>
using namespace std;

int binaryOneCounter(int number){
    int counter=0;
    while (number != 0){
        if(number &1)counter++;
        number >>= 1;
    }
    return counter;
}

int main(){
    int rounds;
    cin >> rounds;
    while(rounds--){
        int number;
        cin >> number;
        cout << binaryOneCounter(number) << ' ';
    }
    return 0;
}