#include<iostream>
#include<vector>
using namespace std;

int main(){
    int groups;
    cin>>groups;
    while(groups--){
        int length, thoughts;
        cin >> length >> thoughts;
        vector<int> v(length + 1);
        for (int i = 0; i < thoughts;i++){
            int start, end;
            cin >> start >> end;
            for (int i = start; i <= end;i++)
                v[i]++;
        }
        for (int i = 1; i <= length;i++)
            cout << v[i] << ' ';
            cout << endl;
    }
    return 0;
}