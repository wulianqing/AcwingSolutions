#include<iostream>
#include<cmath>
using std::cin;
using std::cout;
using std::endl;

double myPowPositive(double base_num,long exp_num){
    //base case
    //double res;
    if (exp_num == 0)
        return 1;
    else if(base_num == 1)
        return 1;
    else if(exp_num == 2)
        return base_num * base_num;
    else if(exp_num == 3)
        return  base_num * base_num * base_num;
    else
    {
        if(exp_num % 2 == 1)
            return myPowPositive(base_num * 2, exp_num / 2) * base_num;
        else{
            return myPowPositive(base_num * 2, exp_num / 2);
        }
    }
}

double myPow(double base_num,long exp_num){
    int positive = 1;
    if(exp_num < 0){
        positive = 0;
        exp_num =  -exp_num;
    }
        
    double ans = myPowPositive(base_num, exp_num);
    if(positive == 0)
        return 1 / ans;
    else
        return ans;
}

int main(){
    double base_num;
    long exp_num;
    cin >> base_num >> exp_num;
    //use lib 
    cout <<"use lib: " << pow(base_num, exp_num)<<endl;
    //use myPow()
    cout <<"use myPow():" << myPow(base_num, exp_num) << endl;
    
    return 0;
}