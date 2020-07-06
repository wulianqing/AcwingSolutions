#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    string findPalindrome(string s, int a, int b){
        string temp;
        if (a == b)
            temp = s[a];
        else
            temp = s.substr(a,2);
        int left = a - 1, right = b + 1;
        while (left>=0 && right<s.size() && s[left] == s[right])
            temp = s[left--] + temp + s[right++];
        return temp;
    }

    string longestPalindrome(string s) {
        //exception
        string cur_ans;
        if(s.size() == 0)
            return cur_ans;
        else if(s.size() == 1)
            return s;
        //s.size() >= 2
        cur_ans = s[0];
        int max_length = 1;
        //travel: 0~n-2 single & double
        for (int i = 0; i < s.size() - 1;i++){
            //single
            string temp_str = findPalindrome(s, i, i);
            if(temp_str.size() > max_length){
                cur_ans = temp_str;
                max_length = temp_str.size();
            }
            //double
            if(s[i] == s[i+1]){
                string temp_str = findPalindrome(s, i, i+1);
                if(temp_str.size() > max_length){
                    cur_ans = temp_str;
                    max_length = temp_str.size();
                }
            }
        }
        return cur_ans;
    }
};

int main(){
    Solution solu;
    string a;
    cin >> a;
    cout << solu.longestPalindrome(a) << endl;
    return 0;
}