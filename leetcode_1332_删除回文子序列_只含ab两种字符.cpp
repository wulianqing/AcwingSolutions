#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    int removePalindromeSub(string s) {
        if(s.size() == 0)
            return 0;
        int left = 0, right = s.size() - 1;
        while(left < right && s[left] == s[right])
            left++, right--;
        if(left >= right)
            return 1;
        else
            return 2;
    }
};
int main(){
    string s = "ababa";
    Solution solu;
    cout << solu.removePalindromeSub(s) << endl;
    return 0;
}