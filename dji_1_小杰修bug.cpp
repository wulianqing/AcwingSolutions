#include<iostream>
using namespace std;
int main(){
    int n, a, x;
    cin>>n>>a>>x;
    int sum = 0;
    int cur;
    for(int i = 0;i<n;i++){ 
        cin>>cur;
        sum += cur;
    }
    int efficient_work = 60 * a * x;
    //全部都是高效时间内
    if(efficient_work >=  sum)
        cout<< (sum + a - 1) / a << endl;
    else{
        int temp_time = 60 * x + sum - (60 * a * x);
        if(temp_time > 480)
             cout<<480;
        else 
            cout<<temp_time<<endl;
    }
    return 0;
} 