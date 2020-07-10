#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size();
        int l2 = text2.size();
        vector<vector<int>> dp(l1+1, vector<int>(l2+1,0));
        for (int i = 1; i <= l1;i++){
            for (int j = 1; j <= l2;j++){
                if(text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[l1][l2];
    }
};
int main(){
    Solution solu;
    string text1 = "abcde";
    string text2 = "ace";
    cout<<solu.longestCommonSubsequence(text1, text2) << endl;
    return 0;
}