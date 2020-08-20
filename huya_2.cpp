#include<iostream>
#include<vector>
using namespace std;
int main() {

    int k;
    cin >> k;
    vector<int> v1 = {5, 3, 2};
    vector<int> v2 = {8, 7, 4, 1};
    int p1 = 0, p2 = 0;
    while(p1 + p2 < k && p1 < v1.size() && p2 < v2.size())
    {
        if(p1 + p2 == k-1 )
        {
            cout << max(v1[p1], v2[p2])<<endl;
            break;
        }
        if(v1[p1] > v2[p2])
        {
            cout << v1[p1] << endl;
            p1++;
        }   
        else
        {
            cout << v2[p2] << endl;
            p2++;
        }
    }
    return 0;
}