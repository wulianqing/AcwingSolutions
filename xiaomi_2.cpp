#include<iostream>
#include<string>
#include<stack>
using namespace std;

class Solution
{
public:
    bool isValid(string s) {
        stack<char> stk;
        for(int i = 0;i < s.size();i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
                stk.push(s[i]);
            else{
                if(s[i] == ')'){
                    if(stk.top() == '(')
                        stk.pop();
                    else 
                        return false;
                }
                else if(s[i] == ']'){
                    if(stk.top() == '[')
                        stk.pop();
                    else 
                        return false;
                }
                else if(s[i] == '}'){
                    if(stk.top() == '{')
                        stk.pop();
                    else 
                        return false;
                }
            }
        }
        return true;
    }
};

int main(){
    string s = "[(){()}]";
    Solution solu;
    cout << solu.isValid(s) << endl;
    
}