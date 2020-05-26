#include<iostream>
#include<cmath>
using std::cin;
using std::cout;
using std::endl;

int main(){
    //input
    double base_num;
    long exp_num;
    double ans = 1;
    cin >> base_num >> exp_num;

    //exception
    if(exp_num == 0 || base_num == 1){
        cout << "product: " << 1 << endl;
        return 0;
    }
        
    //special case
    else if(exp_num < 0){
        base_num = 1 / base_num;
        exp_num = -exp_num;
    }

    //quick product
    while(exp_num != 1){
        if((exp_num & 1) == 1)
            ans *= base_num;
        base_num *= base_num;
        exp_num /= 2;
    }
    ans *= base_num;

    //check out
    cout << "product: " << ans << endl;
    return 0;
}