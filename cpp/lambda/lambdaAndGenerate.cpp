/*************************************************************************
	> File Name: lambdaAndGenerate.cpp
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年07月21日 星期五 21时32分02秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(void) {
    vector<int>numbers(10);
    generate(begin(numbers), end(numbers),[]()->int
             {
                 return random() % 100; 
             });
    for(auto& t : numbers) {
        cout << t << " ";
    } 
    cout << endl;
    return 0;
}
