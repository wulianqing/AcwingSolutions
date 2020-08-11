#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;
int main(){
    int rounds;
    cin>>rounds;
    while (rounds--) {
        int height, width;
        cin>>height>>width;
        int min_divisor = INT_MAX;
        if (height == 1 && width == 1) {
            cout<<1<<endl;
            continue;
        }
        else if (height == 1 || width == 1) {
            int not_one;
            if (height == 1)
                not_one = width;
            else
                not_one = height;
            for (int i = 2;i <= not_one;i++) {
                if (not_one % i == 0) {
                    cout<<i<<endl;
                    break;
                }
            }
        }
        else
            for (int i = 2;i <= min(height, width);i++)
                if (height % i == 0 || width % i == 0){
                    cout<<i<<endl;
                    break;
                }
    }
    return 0;
}