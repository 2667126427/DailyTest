/*************************************************************************
	> File Name: getTime.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: Fri 30 Jun 2017 09:06:01 CST
 ************************************************************************/

#include<stdio.h>
#include<time.h>

int main(void) {
    time_t biggest = 0x7FFFFFFF;
    printf("The biggest is %s \n", asctime(gmtime(&biggest)));
    return 0;
}
