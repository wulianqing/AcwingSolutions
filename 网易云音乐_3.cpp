#include<iostream>
#include<vector>
using namespace std;
int main(){
    int rounds;
    cin>>rounds;
    while(rounds--){ 
        int n;
        cin>>n;
        vector<int> single(n);
        vector<int> team(n);
        for (int i = 0;i<n;i++)
            cin>>single[i];
        for (int i = 1;i<n;i++)
            cin>>team[i];
        
        //dp
        vector<int> dp(n, 0);
        for(int i = 0;i<n;i++){ 
            //exception
            if (i == 0)
                dp[i] = single[0];
            else if (i == 1)
                dp[i] = min(dp[0] + single[1], team[1]);
            else
                dp[i] = min(dp[i-1] + single[i], dp[i-2] + team[i]);            
        }
        cout<<dp[n-1]<<endl;
    }
    return 0;
}