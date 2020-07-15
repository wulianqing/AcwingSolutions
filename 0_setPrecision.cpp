#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    double num = 10.0 / 3;
    cout << fixed << setprecision(3) << num << endl;
    return 0;
}