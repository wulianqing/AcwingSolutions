#include<iostream>
#include<string>
using namespace std;

class Solution
{
public:
    int strToInt(string str) {
        int pos_first_not_blank = 0;
        int pos_first_num = 0;
        int pos_last_num = 0;
        for(;pos_first_not_blank < str.size();){
            if(str[pos_first_not_blank] == ' ')pos_first_not_blank++;
            else break;
        }
        bool negative = 0;
        if(!(str[pos_first_not_blank] == '+' || str[pos_first_not_blank] == '-' || str[pos_first_not_blank] <= '9' && str[pos_first_not_blank] >= '0' ))
            return 0;
        if(str[pos_first_not_blank] == '-' || str[pos_first_not_blank] == '+'){
            if(str[pos_first_not_blank] == '-')negative = 1;
            pos_first_not_blank++;
            if(!(str[pos_first_not_blank] <= '9' && str[pos_first_not_blank] >= '0'))
                return 0;
        }
        //第一个非0开头
        pos_first_num = pos_first_not_blank;
        while(str[pos_first_num] == '0')pos_first_num++;
        //最后一个有效数字
        pos_last_num = pos_first_num;
        while(str[pos_last_num] <= '9' && str[pos_last_num] >= '0')
            pos_last_num++;
        pos_last_num -= 1;
        //10位判断溢出
        if(pos_last_num - pos_first_num + 1 > 10 && negative == 0)return INT_MAX;
        if(pos_last_num - pos_first_num + 1 > 10 && negative == 1)return INT_MIN;
        if(pos_last_num - pos_first_num + 1 == 10 && negative == false)
            if(str.substr(pos_first_num,pos_last_num - pos_first_num + 1) >= "2147483647")
                return INT_MAX;
        if(((pos_last_num - pos_first_num + 1) == 10) && negative == true)
            if (str.substr(pos_first_num, pos_last_num - pos_first_num + 1) >= "2147483648")
                return INT_MIN;
        int ans = 0;
        long bit = 1;
        for(int i = pos_last_num;i>=pos_first_num;i--){
            ans += (str[i]-'0') * bit;
            bit *= 10;
        }
        if(negative)
            return -ans;
        else 
            return ans;
    }
};

int main(){
    Solution solu;
    cout << solu.strToInt("-2147483648") << endl;
    return 0;
}