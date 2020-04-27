#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    string a, b;
    vector<int> ans;
    int carry_bit = 0; //进位符
    int small_size, big_size;
    cin >> a >> b;
    small_size = min(a.size(),b.size());
    big_size = max(a.size(),b.size());
    //翻转,让低位第0位为a[0],b[0]
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    //int rounds = small_size;
    int i = 0;
    for (; i < small_size; i++){
        ans.push_back((a[i]-'0' + b[i]-'0') % 10 + carry_bit);
        carry_bit = (a[i]-'0' + b[i]-'0') / 10;
    }
    //把长的数后面多出来的填上,注意多出来的第一位要看一下进位
    if(a.size()<b.size()){
        ans.push_back(b[i]-'0' + carry_bit);
        i++;
        for (; i < b.size();i++){
            ans.push_back(b[i]-'0');
        }
    }
    else if(a.size() > b.size()){
        ans.push_back(a[i]-'0' + carry_bit);
        i++;
        for (; i < a.size();i++){
            ans.push_back(a[i]-'0');
        }
    }
    //长度相等的话直接看进位符号
    else
        if(carry_bit != 0)
            ans.push_back(carry_bit);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size();i++){
        cout << ans[i];
    }
    return 0;
}