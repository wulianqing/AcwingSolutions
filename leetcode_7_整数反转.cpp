#include<iostream>
#include<limits.h>
using namespace std;

class Solution
{
public:
    int reverse(int x) {
        if(x == INT_MIN)
            return 0;
        int negative = 0;
        if(x < 0){
            negative = 1;
            x = abs(x);
        }
        int ans = 0;
        while(x){
            if(negative == 0){
                if(ans > (INT_MAX - x % 10)/10)
                    return 0; 
            }
            else{
                if(ans - 1 > (INT_MAX - x % 10)/10)
                    return 0;
            }
            ans = ans * 10 + x % 10;
            x /= 10;
        }
        if(negative == 1)ans = -ans;
        return ans;
    }
};
int main(){
    int x = -2147483648;
    Solution solu;
    cout << solu.reverse(x) << endl;
    return 0;
}