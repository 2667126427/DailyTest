#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main(void){
    int N = 0;
    int prbs = 0;
    int prb[100];
    scanf("%d", &N);
    int i = 0, j = 0, k = 0;
    int can = 1;
    for (i = 0; i < N; ++i){
        scanf("%d", &prbs);
        can = 1;
        for (j = 0; j < prbs; ++j)scanf("%d", &prb[j]);
        if (prbs < 10 || prbs > 13)can = 0;
        if (can){
            sort(prb, prb + prbs);
            if ((prb[0] != 1 || prb[1] != 1) && can)can = 0;
            for (k = 0; k < prbs - 2 && can; ++k){
                if (prb[k + 1] - prb[k] > 2)can = 0;
            }
        }
        if (can)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
/*
8
9
1 2 3 4 5 6 7 8 9
10
1 2 3 4 5 6 7 8 9 10
11
999 1 1 2 3 4 5 6 7 8 9
11
999 1 3 5 7 9 11 13 17 19 21
10
15 1 13 17 1 7 9 5 3 11
13
1 1 1 1 1 1 1 1 1 1 1 1 2
10
2 3 4 5 6 7 8 9 10 11
10
15 1 13 3 6 5 4 7 1 14
*/
