// 精确到小数点6位
#include<iostream>
#include<iomanip>
#include<math.h>
using namespace std;
int main(){
    double n;
    cin >> n;
    double left = 0, right = n;
    while(left < right){
        double mid = left + (right - left) / 2;
        if(fabs(pow(mid,3) - n) < 0.0000001){
            cout << fixed << setprecision(6) << mid << endl;
            return 0;
        }
        //mid偏右
        else if (pow(mid,3) - n > 0.0000001)
            right = mid;
        //mid偏左
        else if(n - pow(mid,3) > 0.0000001)
            left = mid;
    }
    return 0;
}