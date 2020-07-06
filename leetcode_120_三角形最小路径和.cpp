#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> dp;
        int n = triangle.size();
        if(n == 1)
            return triangle[0][0];
        //init
        dp.push_back({triangle[0][0]});
        for (int i = 1; i < n; i++)
        {
            vector<int> temp(i+1);
            temp[0] = dp[i - 1][0] + triangle[i][0];
            temp[i] = dp[i - 1][i - 1] + triangle[i][i];
            dp.push_back(temp);
        }
        //claculate dp
        for (int i = 2; i < n;i++){
            for (int j = 1; j < n - 1;j++){
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }
        //choose the min
        int min = dp[n-1][0];
        for (int i = 0; i < n;i++){
            if(dp[n-1][i] < min)
                min = dp[n - 1][i];
        }
        return min;
    }
};
int main(){
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    Solution solu;
    cout << solu.minimumTotal(triangle)<<endl;
    return 0;
}