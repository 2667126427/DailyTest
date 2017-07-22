/*************************************************************************
	> File Name: testFind.cpp
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年07月21日 星期五 21时39分38秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;
int main(void) {
    vector<int>numbers(200);
    srand(clock());
    cout << "clock: " << clock() << endl;
    generate(begin(numbers), end(numbers), []()->int{
        return rand() % 400;
    });
    for (int i = 0; i < 20; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    auto small = find_if(cbegin(numbers), cend(numbers), [](int t)->bool{
        return t < 100;
    });
    auto big = find_if(cbegin(numbers), cend(numbers), [](int t)->bool{
        return t >= 100;
    });
    if (small != end(numbers)) {
        cout << "small " << *small << endl;
    }
    if (big != end(numbers)) {
        cout << "big " << *big << endl;
    }
    return 0;
}
