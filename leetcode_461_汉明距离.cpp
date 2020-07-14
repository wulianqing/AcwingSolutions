#include<iostream>
using namespace std;
class Solution
{
public:
    int hammingDistance(int x, int y) {
        int counter = 0;
        while (x || y)
        {
            if( (x & 1) != (y & 1))
                counter++;
            x >>= 1;
            y >>= 1;
        }
        return counter;
    }
};
int main(){
    int x = 1;
    int y = 4;
    Solution solu;
    cout << solu.hammingDistance(x, y) << endl;
    return 0;
}
