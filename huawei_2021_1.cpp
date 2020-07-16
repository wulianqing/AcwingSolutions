#include<iostream>
#include<string>
using namespace std;
int main(){
    string a, b;
    cin >> a >> b;
    int i_a = 0, i_b = 0;
    for (int i = 0; i < a.size();i++)
        i_a += (int)(a[i] - '0');
    for (int i = 0; i < b.size();i++)
        i_b += (int)(b[i] - '0');
    cout << i_a % i_b << endl;
    return 0;
}