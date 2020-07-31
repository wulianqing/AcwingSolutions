#include<iostream>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    
    int sum = 0;
    int cur = 1;
    for (int divider = 2; divider < a;divider++){
        if(a % divider == 0){
            a = a / divider;
            b = b * divider;
            continue;
        }
        else
            divider++;
    }
    for (int i = 0; i <= b; i++, cur = cur * a)
    {
        sum += cur;
        if(sum >= 9901)
            sum %= 9901;
    }
    cout<< sum % 9901 <<endl;
    return 0;
}