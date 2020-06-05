#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
using namespace std;

class Solution
{
public:
    string reverseWords(string s) {
        stringstream input(s);
        string temp;
        stack<string> data;
        while(input >> temp)
            data.push(temp);
        string ans;
        int rounds = data.size()-1;
        for (int i = 0; i < rounds; i++)
        {
            ans += data.top();
            data.pop();
            ans += ' ';
        }
        ans += data.top();
        return ans;
    }
};

int main(){
    Solution solu;
    cout<<solu.reverseWords("the sky is so blue")<<endl;
    return 0;
}
