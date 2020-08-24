#include<string>
#include<iostream>
#include<vector>

int main() {
    std::string ls = "hellohhhworldhhh!!!";
    std::string ss = "hhh";
    std::vector<std::string> v;
    int tail = 0;
    while(ls.find(ss) >= 0 && ls.find(ss) < ls.size())
    {
        tail = ls.find(ss);
        v.push_back(ls.substr(0, tail));
        ls = ls.substr(tail + ss.size());
    }

    for (int i = 0; i < v.size();i++)
        std::cout << v[i] << std::endl;

}