
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
struct to_visited{
    int to;
    bool visited;
    to_visited(int a){
        to = a;
        visited = false;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    unordered_multimap<int, to_visited> hm;

    //input relations
    for (int i = 0; i < m;i++){
        int temp_from, temp_to;
        cin >> temp_from >> temp_to;
        hm[temp_from] = new to_visited(temp_to);
    }

    //relation table
    vector<vector<bool>> table(n, vetor<bool>(n, false));


    for (int i = 0; i < m;i++){
        //find key == i, travel all of them
        unordered_multimap<int, to_visited>::iterator it = hm.find(i);
        //j: 第j个 i
        for (int j = 0; j < hm.count(i);j++){
            //判断是否已访问过
            //把table[i][it->second->to] = ture(认可); it->second->visited = true(已访问);
            dfs(table, i, from);
        }
    }
}