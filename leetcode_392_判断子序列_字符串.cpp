#include<iostream>
#include<string>
using namespace std;

class Solution
{
public:
    bool isSubsequence(string s, string t) {
        int p1 = 0, p2 = 0;
        for (; p2 < t.size();p2++){
            if(s[p1] == t[p2])
                p1++;
            if(p1 == s.size())
                break;
        }
        if(p1 == s.size())
            return true;
        else
            return false;
    }
};
int main(){
    string s = "acf";
    string t = "agfdbefc";
    Solution solu;
    cout << solu.isSubsequence(s, t) << endl;
    return 0;
}