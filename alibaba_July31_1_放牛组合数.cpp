#include<iostream>
#include<math.h>
using namespace std;
#define t 1000000007;
long long  C_a_b(long long  a, long long  b)
{
    long long  ret = 1;
    if(a-b < b)
        b = a - b;
    for (int i = 0; i < b;i++,a--)
        ret *= a;
    for (int i = 1; i <= b;i++)
        ret /= i;
    ret %= t;
    return ret;
}
long long  my_pow(long long  a,long long  b){
    long long  ret = 1;
    for (int i = 0; i < b; i++)
        ret = ret * a % t;
    return ret;
}
int main(){
    int m, n;
    cin >> m >> n;
    long long   sum = 0;
    for (int i = 0; i <= m;i++){
        sum += C_a_b(m, i) * my_pow(n, i);
        sum %= t;
    }
    cout << sum << endl;
    return 0;
}