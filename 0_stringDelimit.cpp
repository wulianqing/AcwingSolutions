#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
int main()
{
    string s = "1,2,3,4,10";
    //stringstream headFile: <sstream>
    stringstream input(s);
    string temp;
    vector<int> data;
    while(getline(input,temp,',')){
        data.push_back(stoi(temp));
    }
    for (int i = 0;i<data.size();i++)
        cout << data[i] << endl;
    return 0;
}