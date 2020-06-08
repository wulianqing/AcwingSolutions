#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class MedianFinder
{
public:
    priority_queue<double> left;
    priority_queue<double, vector<double>, greater<double>> right;

public:
    /** initialize your data structure here. */
    MedianFinder() {
    }
    
    void addNum(int num) {
        if(left.size() == 0 && right.size() == 0)
            left.push(num);
        else if(left.size() == right.size()){
            //num <= left.top() put into left
            if(num < right.top())
                left.push(num);
            //num > left: put right.top() into left, put num into right
            else{
                left.push(right.top());
                right.pop();
                right.push(num);
            }
        }    
        //left.size() == right.size() + 1
        else{
            //num >= left.front(): put into right
            if(num >= left.top())
                right.push(num);
            //num < left.front():  put left.front() into right, put num into left
            else{
                right.push(left.top());
                left.pop();
                left.push(num);
            }
        }   
    }

    double findMedian() {
        //if odd ? left.front() : (left.front() + right.front()) / 2
        if(left.size() != right.size())
            return left.top();
        else
            return (left.top() + right.top()) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */