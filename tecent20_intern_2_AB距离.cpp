#include<iostream>
#include<math.h>
#include<limits>
#include<iomanip>
using namespace std;

typedef struct point{
    double x;
    double y;
} point;

double diff(double ax,double ay,double bx,double by){
    return sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by)));
}
int main(){
    int groups;
    cin >> groups;
    while(groups--){
        int n;
        cin >> n;
        point a[n];
        point b[n];
        for (int i = 0; i < n;i++){
            cin >> a[i].x>>a[i].y;
        }
        for (int i = 0; i < n;i++){
            cin >> b[i].x>>b[i].y;
        }
        double min = INT_MAX;
        for (int i = 0; i < n;i++){
            for (int j = 0; j < n;j++){
                double curr_diff = diff(a[i].x, a[i].y, b[j].x, b[j].y);
                if(curr_diff < min){
                    min = curr_diff;
                    //cout << min << endl;
                }
            }
        }
        cout << fixed << setprecision(3) << min << endl;
    }
    return 0;
}