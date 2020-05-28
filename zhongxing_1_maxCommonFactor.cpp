// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED
#include<iostream>
using std::min;

int maxCommonFactor(int num1, int num2, int common_factor)
{
    int min_num = min(num1,num2);
    for(int i = 2;i <= min_num;i++){
        if(num1 % i ==0 && num2 % i == 0){
            common_factor = maxCommonFactor(num1/i,num2/i,common_factor * i);
            break;
        }
    }
    return common_factor;
}
int groupID(int jerseyNum1, int jerseyNum2)
{
    // WRITE YOUR CODE HERE 
    if(jerseyNum1 == 0 || jerseyNum2 == 0)return 0;
    return maxCommonFactor(jerseyNum1,jerseyNum2,1);
    
}
// FUNCTION SIGNATURE ENDS