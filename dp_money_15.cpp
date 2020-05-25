#include<iostream>
using namespace std;

int main(){
    int money;
    cout << "输入要凑多少钱" << endl;
    cin >> money;
    int dp_table[money + 1];
    dp_table[0] = 0;

    for (int i = 1; i < money + 1;i++){
        int min = 99999;
        if (i >= 1)
        {
            if(dp_table[i-1]+1 < min){
                min = dp_table[i - 1] + 1;
            }
        }
        if(i>=5){
            if(dp_table[i-5]+1 < min){
                min = dp_table[i - 5] + 1;
            }
        }
        if(i>=11){
            if(dp_table[i-11]+ 1 < min){
                min = dp_table[i - 5] + 1;
            }
        }
        dp_table[i] = min;
    }
    for (int i = 0; i < money + 1;i++)
            cout << dp_table[i] << " ";

    cout << "\n需要至少" << dp_table[money] << "次操作" << endl;

    return 0;
}