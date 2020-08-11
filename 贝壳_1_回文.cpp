#include<iostream>
#include<string>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int left = 0, right = n-1;
    int counter = 0;
    while(left < right){ 
        if (s[left++] != s[right--])
            counter++;
    }
    cout<<counter<<endl;
    return 0;
}