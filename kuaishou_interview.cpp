#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;
int main(){
    //解法二
    string s;
    cin>>s;
    reverse(s.begin(),s.end());
    //特判
    //
    for(int left = 0,right = left + 1;right < s.size();){
        if(s[right] == '.'){
            reverse(s.begin()+left,s.begin() + right - 1);
            left = right + 1;
            right = left + 1;
        }
        else 
            right++;
    }
    cout<<s<<endl;
    return 0;
}