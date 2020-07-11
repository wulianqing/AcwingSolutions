#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool myCompare(int a,int b){
    return a < b;
}
int main(){
    vector<int> v1 = {3, 4, 2, 1, 7};
    int *v2 =new int [5]{3, 4, 2, 1, 7};
    sort(v1.begin(), v1.begin()+v1.size(), myCompare);
    for (int i = 0; i < v1.size();i++)
        cout << v1[i] << ' ';
    cout << endl;
}
