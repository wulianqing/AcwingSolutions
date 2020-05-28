#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::vector;

int main(){
    string s = "1,2,3,4,10";
    //stringstream headFile: <sstream>
    stringstream input(s);
    string temp;
    vector<string> data;

    while(getline(input,temp,',')){
        data.push_back(temp);
    }

    for (int i = 0;i<data.size();i++)
        cout << stoi(data[i]) << endl;
    return 0;
}