#include<iostream>
#include<vector>
using namespace std;

struct materials{
    int weight;
    int value;
    int quantity;
};

int main(){
    //实际是背包问题
    int n, capa;
    cin>>n>>capa;
    vector<materials> goods(n+1);
    for(int i = 1;i<=n ;i++)
        cin>>goods[i].weight>>goods[i].value>>goods[i].quantity;
    //dp
    vector<vector<int>> dp(n+1,vector<int>(capa + 1,0));
    /*
    //init dp row 0 
    for(int i = 0;i <= capa;i++)
        if(goods[0].weight <= i)
            dp[0][i] = goods[0].value;
    */
    //calculate dp
    int max_value = 0;
    for(int i = 1;i <= n;i++){
        //对于当前物品可选择拿/不拿
        for(int j = 1;j <= capa;j++){
            /*
            //当前物品数量不够，只能不拿
            if(goods[i].quantity == 0 || j-goods[i].weight < 0)
                dp[i][j] = dp[i-1][j];
            
            else{
            */
                for(int k = 0;k * goods[i].weight  <= j;k++)
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j - k * goods[i].weight] + k * goods[i].value);
                //说明拿了
                //if(dp[i][j] > dp[i-1][j])
                //   goods[i].quantity--;
                if(dp[i][j] > max_value)
                    max_value = dp[i][j];
            //}   
          }
    }
    cout<<max_value<<endl;
    return 0;
}    