#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
int main(){
    vector<double> v(8);
    for (int i = 0; i < 8;i++)
        cin >> v[i];
    double center_a_x = (v[0] + v[2]) / 2;
    double center_a_y = (v[1] + v[3]) / 2;
    double center_b_x = (v[4] + v[6]) / 2;
    double center_b_y = (v[5] + v[7]) / 2;
    double distance_a_b_pow = pow(center_b_x - center_a_x, 2) + pow(center_b_y - center_a_y, 2);
    /*
    double distance_vert_a_b = center_b_y - center_a_y;
    double distance_heriz_a_b = center_b_x - center_a_x;
    */
    double a_x = v[2] - v[0];
    double a_y = v[3] - v[1];
    double b_x = v[6] - v[4];
    double b_y = v[7] - v[5];
    double half_x = (a_x + b_x) / 2;
    double half_y = (a_y + b_y) / 2;

    //当顶点重叠时为临界位置: a,b中心距离^2 = half_x^2 + half_y^2
    if(distance_a_b_pow <= pow(half_x,2) + pow(half_y,2))
        cout << 1 << endl;
    else
        cout << 0 << endl;
    return 0;
}