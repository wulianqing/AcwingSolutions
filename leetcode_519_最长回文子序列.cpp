#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        if (n == 0)
            return 0;
        if(n == 1)
            return 1;
        //dp[i][j]
        vector<vector<int>> dp(n,vector<int>(n,1));
        //calculate dp
        //i: 间隔 第一轮(0,0+1)(1,1+1)... 到最后一轮(0,4)
        for (int diff = 1;diff < n;diff++){
            for (int i = 0; i + diff < n;i++){
                if(diff == 1)
                    if(s[i] == s[i + diff]){
                        dp[i][i + diff] = 2;
                        continue;
                    }
                if (s[i] == s[i + diff])
                    dp[i][i + diff] = dp[i + 1][i + diff - 1] + 2;
                else
                    dp[i][i + diff] = max(dp[i + 1][i + diff], dp[i][i + diff - 1]);
            }
        }
        return dp[0][n - 1];
    }
};
int main(){
    string s = "aaa";
    Solution solu;
    cout << solu.longestPalindromeSubseq(s) << endl;
    return 0;
}