#include<iostream>
#include<string>
using namespace std;

class Solution
{
public:
    bool isMatched(string str){
        int counter_a = 0, counter_b = 0, counter_c = 0, counter_d = 0, counter_e = 0;
        for (int i = 0; i < str.size();i++){
            if(str[i] == 'a')
                counter_a++;
            else if(str[i] == 'b')
                counter_b++;
            else if(str[i] == 'c')
                counter_c++;    
            else if(str[i] == 'd')
                counter_d++;
            else if(str[i] == 'e')
                counter_e++;    
        }
        if(counter_a % 2 == 1 || counter_b % 2 == 1 || counter_c % 2 == 1 || counter_d % 2 == 1 || counter_e % 2 == 1)
            return false;
        else
            return true;
    }

    int getMaxSubstringLen(string str) {
        // write code here
        int left = 0;
        int n = str.size();
        int max_length = 0;
        for (; left < n - 1; left++)
        {
            for (int right = n - 1; right > left;right--){
                //剪枝
                if(right - left + 1 <= max_length)
                    break;
                else{
                    string temp_str = str.substr(left, right + 1);
                    if(isMatched(temp_str))
                        if(temp_str.size() > max_length)
                            max_length = temp_str.size();
                }
            }
        }
        return max_length;
    }
};

int main(){
    Solution solu;
    string s = "asdfajskfbb";
    cout << solu.getMaxSubstringLen(s) << endl;
    return 0;
}
