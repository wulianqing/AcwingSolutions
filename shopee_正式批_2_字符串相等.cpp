#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
    bool isStrsEqu(string str1, string str2) {
        // write code here
        if(str1.size() != str2.size())
            return false;
        else{
            if(str1 == str2)
                return true;
            else if(str1.size() % 2 == 1)
                return false;
            else{
                string substr1_1 = str1.substr(0,str1.size() / 2);
                string substr1_2 = str1.substr(str1.size() / 2, str1.size());
                string substr2_1 = str2.substr(0,str2.size() / 2);
                string substr2_2 = str2.substr(str2.size() / 2, str2.size());

                return (isStrsEqu(substr1_1, substr2_1) && isStrsEqu(substr2_1, substr2_2)) || (isStrsEqu(substr1_1, substr2_2) && isStrsEqu(substr1_2, substr2_1));
            }
        }
    }
};

int main(){
    string a = "";
    string b = "";

    Solution solu;
    cout << solu.isStrsEqu(a, b) << endl;
}