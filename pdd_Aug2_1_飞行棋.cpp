#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
int main()
{
    int distance, n;
    cin >> distance >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int back = 0;
    for (int i = 0; i < n;i++){
        distance = distance - v[i];
        if(distance < 0){
            back++;
            distance = abs(distance);
        }
        else if(distance == 0){
            if(i != n-1){
                cout << "paradox" << endl;
                return 0;
            }
            else
                break;
        }
        //distance > 0 continue
    }
    cout << distance << ' ' << back << endl;
    return 0;
}