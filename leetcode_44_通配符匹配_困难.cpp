#include<iostream>
#include<string>
using namespace std;

class Solution {
private:
    bool ans = false;
public:
    bool isMatch(string s, string p) {
        //stop condition: null && char: false; length 
        if(s.size() == 0 && p.size() == 0){
            ans = true;
            return ans;
        }
        else if(p.size() == 0){
            ans = false;
            return ans;
        }
        else if(s.size() == 0){
            if(p[0] == '*')
                ans = isMatch(s, p.substr(1));
            else{
                ans = false;
                return ans;
            }
        }
        //if is letter
        if(p[p.size()-1] >= 'a' && p[p.size()-1] <= 'z'){
            if(s[s.size()-1] != p[p.size()-1]){
                ans = false;
                return ans;
            }
        }
        if(p[0] >= 'a' && p[0]<= 'z'){
            if(s[0] != p[0]){
                ans = false;
                return ans;
            }
            else
                ans = isMatch(s.substr(1),p.substr(1));
        }              
        //if is ?
        else if(p[0] == '?'){
            ans = isMatch(s.substr(1),p.substr(1));
        }
        /*
        if is *: 
            if current char == * next char: try isMatch; 
            if(ans) delete current char
        */
        else if(p[0] == '*'){
            if(p.size() == 1){
                ans = true;
                return true;
            }
            else if (p[1] == s[0] || p[1] == '?' || p[1] == '*')
            {
                if(isMatch(s,p.substr(1))){
                    ans = true;
                    return ans;
                }
                else 
                    ans = isMatch(s.substr(1), p);
            }
            else if(p[1] != s[0])
                ans = isMatch(s.substr(1), p);
        }
        return ans;
    }
};

int main(){
    string s = "acdcb";
    string p = "a*c?b";
    Solution solu;
    cout<< solu.isMatch(s, p)<<endl;
    return 0;
}