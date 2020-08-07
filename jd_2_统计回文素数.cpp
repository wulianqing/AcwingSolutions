#include<iostream>
#include<string>
using namespace std;
bool isPrimerNumber(int n){
    for (int i = 2; i <= (n + 1)/2;i++){
        if(n % i == 0)
            return false;
    }
    return true;
}
bool isPanlindrome(int n){
    string s = to_string(n);
    int l = 0, r = s.size() - 1;
    while(l < r){
        if(s[l] == s[r])
            l++, r--;
        else
            return false;
    }
    return true;
}
int dropLetter(int n,int k){
    string s = to_string(n);
    s = s.erase(k, 1);
    if(s.empty())
        return 0;
    return stoi(s);
}
int main(){
    
    int left, right;
    cin >> left >> right;
    int counter = 0;
    for (int i = left; i <= right;i++)
        for (int j = 0; j < to_string(i).size();j++){
            int temp = dropLetter(i, j);
            if(temp == 0)
                continue;
            if (isPrimerNumber(temp) && isPanlindrome(temp))
            {
                counter++;
                break;
            }
        }    
    cout << counter << endl;
    return 0;

}