#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
struct staff{
    int line;
    int value;
    int from;
};
void dfs(int cur_line, int & cur_value, int & max_single, int &max_all, vector<staff> & v, unordered_map<int, vector<int>> & hm)
{
    cur_value += v[cur_line].value % 1000000003;
    cur_value %= 1000000003;
    if (cur_value > max_single)
        max_single = cur_value;
    if(max_single > max_all)
        max_all = max_single;
    //{3,4}: size == 2
    if(hm.find(cur_line) == hm.end())
        return;
    for (int i = 0; i < hm[cur_line].size(); i++)
    {
        dfs(hm[cur_line][i], cur_value, max_single, max_all, v, hm);
        //cur_value -= v[hm[cur_line][i]].value;
    }
}
int main()
{
    int n;
    cin >> n;
    vector<staff> v(n+2);
    unordered_map<int,vector<int>> hm;
    for (int i = 2; i <= n+1;i++){
        v[i].line = i;
        cin >> v[i].value >> v[i].from;
        hm[v[i].from].push_back(v[i].line);
    }
    //travel
    int max_all = 0;
    for (int i = 2; i <= n + 1; i++){
        int cur_value = 0;
        int max_single = 0;
        dfs(i, cur_value, max_single, max_all, v, hm);
    }
        
    cout << max_all << endl;
    return 0;
}