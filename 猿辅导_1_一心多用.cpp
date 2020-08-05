#include<iostream>
#include<vector>
using namespace std;
#define MAX = 1000000007;
struct course{
    int s;
    int e;
};
int main()
{
    int n;
    cin >> n;
    vector<course> v(n);
    vector<int> tbl(n,0);
    int max = 0;
    for (int i = 0; i < n; i++)
        cin >> v[i].s >> v[i].e;
    for (int i = 0; i < n;i++){
        for (int j = v[i].s; j < v[i].e;j++){
            tbl[j]++;
            if(tbl[j] > max)
                max = tbl[j];
        }
    }
    cout << max << endl;
    return 0; 
}