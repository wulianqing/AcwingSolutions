#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> a;
    a.resize(10);
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << ' ';
    cout << endl;
    cout << "capacity: " << a.capacity() << endl;
    cout << "size: " << a.size() << endl;
    cout << "max size: " << a.max_size() << endl;

    cout << "push 1 element..." << endl;
    a.push_back(1);
    cout << "capacity: " << a.capacity() << endl;
    cout << "size: " << a.size() << endl;
    cout << "max size: " << a.max_size() << endl;
    //vector<string> s1 = {"1", "2", "3", "null", "null", "4", "5"};
    //vector<string> s2 = s1;
    /*
    for (int i = 0; i < s2.size();i++)
        cout << s2[i] << ' ';
    cout << endl;
    */
    return 0;
}