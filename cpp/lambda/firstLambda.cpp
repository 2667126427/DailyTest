/*************************************************************************
	> File Name: firstLambda.cpp
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年07月21日 星期五 21时16分49秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(void) {
    auto lamb = []()->void{ cout << "Hello lambda!" << endl; };
    // 这样就是一个函数了?
    lamb();
    int t = 10;
    // 在lambda表达式中值传递为只读变量
    auto nonRefe = [t](){ cout << "in nonRefe t = " << t << endl; /* t += 10;*/};
    auto refe = [&t]() { cout << "in refe t = " << t << endl; t += 10; };
    refe();
    nonRefe();
    cout << "in main t = " << t << endl;
    refe();

    return 0;
}
