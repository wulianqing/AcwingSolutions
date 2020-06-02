#include<iostream>
#include<cmath>
using namespace std;
class Solution {
public:
    int findNthDigit(int n) {
        //exception
        if(n >= 0 && n <= 9)return n;
        //find range
        int range = 1;
        int cur_num = n;
        while(cur_num - range * 9 * pow(10,range-1)>0){
            cur_num -= range* 9 * pow(10,range-1);
            range++;
        }
        //pos in range
        int pos_in_range = (cur_num - 1) / range ;
        //pos in num
        int pos_in_num = (cur_num - 1) % range;
        int pos = pow(10,range-1) + pos_in_range;
        int rounds = (range - 1) - pos_in_num;
        while (rounds--)
            pos /= 10;
        return pos % 10;
    }
};

int main(){
    Solution solu;
    int n = 11;
    cout << "number on position "<<n<<":"<<solu.findNthDigit(n) << endl;
    return 0;
}