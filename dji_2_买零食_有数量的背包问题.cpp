#include<iostream>
#include<vector>
using namespace std;

struct materials{
    int weight;
    int value;
    int quantity;
};

//代码错误，正确解法应该每个i，j去记录当前物品数量

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
            //没有拿当前物品
            dp[i][j] = dp[i-1][j];
            //假设拿1～k个，判断是否更优
            for(int k = 1;j - k * goods[i].weight >= 0 && k <= goods[i].quantity;k++){
                int cur_max = dp[i-1][j - k *  goods[i].weight] + k * goods[i].value;
                if(cur_max > dp[i][j])
                    dp[i][j] = cur_max; 
            }
            if(dp[i][j] > max_value)
                max_value = dp[i][j];
               
        }
    }
    cout<<max_value<<endl;
    return 0;
}    