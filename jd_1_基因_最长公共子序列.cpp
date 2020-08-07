#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s1, s2;
    for (int i = 0; i < n;i++){
        string temp;
        cin >> temp;
        s1 = s1 + temp;
    }
    for (int i = 0; i < n;i++){
        string temp;
        cin >> temp;
        s2 = s2 + temp;
    }
    int max_dp = 0;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = max(dp[i - 1][j - 1] + 1,max(dp[i - 1][j], dp[i][j - 1]));
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if(dp[i][j] > max_dp)
                max_dp = dp[i][j];
        }
    }
    double value = (double)max_dp / n;
    if (value == 0.5)
        cout << fixed << setprecision(2) << value << " "<< "No" << endl;
    else 
        cout << fixed << setprecision(2) << value << " "<< "Yes" << endl;
    return 0;
}