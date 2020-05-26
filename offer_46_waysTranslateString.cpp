#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
int main()
{
    //input
    string str;
    cin >> str;
    vector<int> dp_memo;

    //base case
    if(str.size() == 0){
        cout << 0 << endl;
        return 0;
    }
    else if(str.size() == 1){
        cout << 1 << endl;
        return 0;
    }

    //dp
    //str.size() >= 2
    //dp_memo[0]:means nothing; dp_memo[1]: the 1st number
    dp_memo.push_back(1);
    dp_memo.push_back(1);
    for (int i = 2; i < str.size()+1; i++)
    {
        string cur_number = str.substr(i - 2, 2);
        if (cur_number >= "10" && cur_number <= "25")
        {
            dp_memo.push_back(dp_memo[i - 1] + dp_memo[i - 2]);
        }
        else{
            dp_memo.push_back(dp_memo[i - 1]);
        }
    }

    //check out
    cout << dp_memo[str.size()] << endl;
    return 0;
}