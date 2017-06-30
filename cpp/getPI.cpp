/*************************************************************************
	> File Name: getPI.cpp
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: Fri 30 Jun 2017 12:09:25 CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main(void) {
    int sum = 1e5;
    int inside = 0;
    double x = 0;
    double y = 0;
    for (int i = 0; i < sum; ++i) {
        x = random() % 10000 * 0.0001;
        y = random() % 10000 * 0.0001;
        if (x * x + y * y <= 1.0) {
            inside++;
        }
    }
    const double PI = 3.1415926;
    double pi = 4.0 * inside / sum;
    cout << "pi is " << pi << endl;
    cout << "the diff: " << (PI - pi) / PI * 100 << "%" << endl;
    return 0;
}
