#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = a;
    for (int i = 0; i < b.size();i++)
        cout << b[i] << ' ';
    cout << endl;
    vector<string> s1 = {"1", "2", "3", "null", "null", "4", "5"};
    vector<string> s2 = s1;
    for (int i = 0; i < s2.size();i++)
        cout << s2[i] << ' ';
    cout << endl;
    return 0;
}