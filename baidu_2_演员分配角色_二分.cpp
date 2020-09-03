#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

struct role{
    int number;
    int score;
};

bool cmp(role a,role b){
    return a.score < b.score;
}

int binSearch(int num, vector<role> &roles)
{
    if(num > roles[roles.size() - 1].score)
        return -1;
    int left = 0, right = roles.size() - 1;
    while(left < right){
        int mid = left + (right - left) / 2;
        int ret;
        while(mid != 0 && roles[mid].score == roles[mid - 1].score)
            mid--;
        if ((roles[mid].score >= num && mid - 1 >= 0 && roles[mid - 1].score < num)|| mid == 0 && roles[mid].score >= num)
        {
            ret = roles[mid].number;
            roles.erase(roles.begin() + mid);
            //roles[mid].score = INT_MAX;
            //sort(roles.begin(), roles.end(),cmp);
            return ret;
        }
        else if(roles[mid].score > num)
            right = mid;
        else if(roles[mid].score < num)
            left = mid + 1;
    }
    if(roles[left].score >= num)
        return roles[left].number;
    else
        return -1;

}



int main(){
    int groups;
    cin >> groups;
    while(groups--){
        int n, m;
        cin >> n >> m;
        vector<int> friends(n);
        vector<role> roles(m);
        for (int i = 0; i < n;i++)
            cin >> friends[i];
        for (int i = 0; i < m;i++){
            roles[i].number = i + 1;
            cin >> roles[i].score;
        }
            
        sort(roles.begin(), roles.end(),cmp);

        vector<int> v(n);
        for (int i = 0; i < n; i++){
            v[i] = binSearch(friends[i], roles);
        }

        for (int i = 0; i < n;i++)
            cout << v[i] << ' ';
        cout << endl;
    }
    return 0;
}