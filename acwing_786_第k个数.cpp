#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main(){
    int n,k;
    cout << "输入n表示数组元素个数,k表示输出第k小的数" << endl;
    cin >> n >> k;
    vector<int> v(n);
    priority_queue<int,vector<int>,less<int>> s;
    cout << "输入n个元素" << endl;
    for (int i = 0; i < n; i++)
    {
        cin>>v[i];
        if(s.size() < k)
            s.push(v[i]);
        else if(v[i] < s.top() && s.size() == k){
            s.pop();
            s.push(v[i]);
        }
    }
    cout<<s.top()<<endl;
    return 0;
}