#include<iostream>
#include<deque>
#include<vector>
using namespace std;
int main(){
    deque<int> q;
    vector<deque<int>::iterator> v;
    for (int i = 1; i <= 5;i++)
        q.push_back(i);
    for (deque<int>::iterator it = q.begin(); it != q.end();it++)
        v.push_back(it);
    //before     
    cout << "before v: ";
    for (int i = 0; i < v.size();i++)
        cout << *v[i] << ' ';
    cout << endl;
    cout << "before q: ";
    for (deque<int>::iterator it = q.begin(); it != q.end();it++)
        cout << *it << ' ';
    cout << endl<<endl;
    deque<int>::iterator itr = q.begin() + 3;
    int temp_value = *itr;
    q.erase(itr);
    q.insert(q.begin(), temp_value);
    v[3] = q.begin();
    //after   
    cout << "after v: ";
    for (int i = 0; i < v.size();i++)
        cout << *v[i] << ' ';
    cout << endl;
    cout << "after q: ";
    for (deque<int>::iterator it = q.begin(); it != q.end();it++)
        cout << *it << ' ';
    cout << endl<<endl;
    return 0;
}