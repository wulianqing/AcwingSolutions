#include<iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){
    //表示febonacci[n],febonacci[0] = 0,febonacci[1] = 1
    int n;
    cin >> n;
    //exception
    if(n == 0 || n == 1)return n;
    //n >= 2
    int a = 0, b = 1;
    for (int i = 2; i <= 2;i++){
        a = a + b;
        b = a + b;
    }
    cout << b << endl;
    return 0;
}

