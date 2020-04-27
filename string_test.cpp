#include<iostream>
#include<string>
using namespace std;

int main(){
    string s("hello");
    s.append(" world");
    s.insert(5, " my beautiful", 0, 3);
    
    string a = "1234";
    int b = atoi(a.c_str());
    cout << b << endl;

    int c = 123;
    string d = to_string(c);
    cout << d << endl;

    return 0;
}