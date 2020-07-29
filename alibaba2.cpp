/*  Alibaba 2020-7-29 */
#include<iostream>
#include<vector>
using namespace std;
void dfs(vector<int> & station,int pos,int cur_value,int & max_value){
    //left
    if(pos >= 1 && station[pos] > 0){
        station[pos]--;
        pos--;
        cur_value++;
        if(cur_value > max_value)
            max_value = cur_value;
        dfs(station, pos, cur_value, max_value);
    }
    //right
    if(pos <= station.size()-3 && station[pos+1] > 0){
        station[pos+1]--;
        pos++;
        cur_value++;
        if(cur_value > max_value)
            max_value = cur_value;
        dfs(station, pos, cur_value, max_value);
    }
    //return
}
int main(){
    int n;
    cin >> n;
    vector<int> station_init(n+1,0);
    for (int i = 1; i < n;i++)
        cin >> station_init[i];
    int max_value = 0;
    for (int i = 0; i <= n; i++){
        vector<int> station(n + 1,0);
        for (int j = 1; j < n;j++)
            station[j] = station_init[j];
        dfs(station, i, 0, max_value);
    }
    cout<<max_value<<endl;
    return 0;
}