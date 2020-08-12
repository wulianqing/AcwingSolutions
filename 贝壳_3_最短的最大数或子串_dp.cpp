#include<iostream>
#include<vector>
using namespace std;
int calculate_or(vector<int> v,int left,int right){
    int counter = 0;
    int mixed = 0;
    for (int i = left;i<=right;i++) 
        mixed |= v[i];
    while(mixed != 0){ 
        if (mixed & 1 == 1)
            counter++;
        mixed>>=1;
    }
    return counter;
}

//测试用例： 4个数 4，2，1，6 正确输出-> 3（3个1），2（长度）
//这个代码还不对，没有缩短
int main(){
    int n;
    cin>>n;
    vector<int> v(n);
    int min_length = 1;
    int max_bit_1 = 0;
    for (int i = 0;i<n;i++)
        cin>>v[i];
    vector<int> dp(n);
    for(int i = 0;i<n;i++){ 
        if (i == 0)
            dp[0] = calculate_or(v, 0, 0);
        else{ 
            int temp_all = calculate_or(v, 0, i);
            int temp_single = calculate_or(v, i, i);
            if(temp_all > temp_single){ 
                dp[i] = temp_all;
                min_length++;
            }
            else{ 
                dp[i] = temp_single;
                min_length = 1;
            }
            if (dp[i] > max_bit_1)
                max_bit_1 = dp[i];
        }
    }
    cout<<max_bit_1<<" "<<min_length<<endl;
    return 0;
}