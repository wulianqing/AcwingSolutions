/*
输入:
多组（不超过 5 组）数据。
每组输入数据分为三行，第一行有两个数字 n,m(0＜n,m10000)，分别表示集合 A 和集合 B 的元素个数
后两行分别表示集合 A 和集合 B。每个元素为不超出 int 范围的整数，每个元素之间有一个空格隔开。

输出:
针对每组数据输出一行数据，表示合并后的集合，要求从小到大输出，每个元素之间有一个空格隔开。

思路:
查找(哈希) -> 插入 ->快排
*/

#include<iostream>
#include<unordered_map>
#include<algorithm>

int main()
{
    int rounds = 5;
    while(rounds--)
    {
        int n, m;
        std::cin >> n >> m;
        int a[n], b[m];
        int count = n;
        std::unordered_map<int, int> map_a;
        for (int i = 0; i < n;i++)
        {
            std::cin >> a[i];
            map_a.insert(std::make_pair(a[i], 1));
        }
        for (int i = 0; i < m;i++)
        {
            std::cin >> b[i];
            if(map_a.find(b[i])==map_a.end())
            {
                map_a.insert(std::make_pair(b[i],1));
                count++;
            }
        }
        std::unordered_map<int, int>::iterator it = map_a.begin();
        int my_set[count];
        for (int i=0; it != map_a.end(); it++,i++)
        {
            my_set[i] = it->first;
        }
            //sort
        std::sort(my_set, my_set + count);
        for (int i = 0; i < count;i++)
            std::cout << my_set[i] << " ";
    }
    return 0;
}