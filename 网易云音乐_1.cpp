#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int calculateEnd(vector<vector<int>> & dp,string s,int i,int j){
    if(s[i] != s[j]){
        dp[i][j] = 0;
        return 0;
    }
    else{
        if(i-1 < j+1){
            dp[i][j] = 1;
            return 1;
        }
        else{
            dp[i][j] = calculateEnd(dp, s, i - 1, j + 1);
            return dp[i][j];
        }
    }
}
int main(){
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    //init
    for (int i = n - 1; i >= n / 2;i--)
        dp[i][i] = 1;
    //calculate
    for (int j = 0;j<n;j++)
        calculateEnd(dp, s, n-1, j);
    int counter = 0;
    for (; counter < n;counter++){
        if(dp[n-1][counter] == 1)
            break;
    }
    string temp = s.substr(0, counter);
    reverse(temp.begin(), temp.end());
    s = s + temp;
    cout << counter << endl;
    cout << s << endl;
    return 0;
}