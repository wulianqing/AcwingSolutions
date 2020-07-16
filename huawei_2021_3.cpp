#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<unordered_map>
using namespace std;
//redefine comparer
bool cmp(vector<int> & a, vector<int> & b){
    if(a.size() != b.size())
        return false;
    for (int i = 0; i < a.size();i++)
        if(a[i] != b[i])
            return false;
    return true;
}
int main(){
    //receive input
    int m;
    cin >> m;
    vector<int> c;
    c.push_back(0);
    string s;
    getline(cin,s);
    s = s.substr(1);
    stringstream input(s);
    string temp;
    while(getline(input,temp,' ')){
        c.push_back(stoi(temp));
    }
    int n = c.size() - 1;
    //dp
    vector<unordered_map<vector<int>,int>> dp(m + 1);
    for (int i = 1; i <= m;i++){
        for (int j = 1; j <= n;j++){
            if(i - c[j] >= 0){
                for (unordered_map<vector<int>,int>::iterator it = dp[j].begin(); it != dp[j].end();it++){
                    vector<int> temp(it->first);
                    temp.push_back(c[j]);
                    if(dp[i].find(temp) == dp[i].end())
                        dp[i][temp]++;
                }
            }
        }
    }
    
    cout << dp[m].size() << endl;
    return 0;
}