#include<iostream>
#include<string>
using namespace std;
int main(){
    string s = "0123456";
    reverse(s.begin() + 1, s.begin() + 4); //123翻转,左闭右开
    cout << s << endl;
    return 0;
}